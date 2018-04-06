#include "RegisterUser.hpp"
#include "server/IDatabase.hpp"
#include <iostream>

namespace casisco
{
namespace server
{
namespace requestHandler
{

RegisterUser::RegisterUser(Casisco::AsyncService *service, grpc::ServerCompletionQueue *cq, IDatabase &db)
    : service_(service)
    , cq_(cq)
    , responder_(&ctx_)
    , db_(db)
    , status_(Status::processing)
{
    service_->RequestregisterUser(&ctx_, &request_, &responder_, cq_, cq_, this);
}

bool RegisterUser::process()
{
    if(status_ == Status::processing)
    {
        std::cout << "Processing " << this << std::endl;
        std::cout << "Received name: " << request_.name() << " password: "
                  << request_.password() << " email: " << request_.email() << std::endl;

        UserInfo ui;
        ui.email = request_.email();
        ui.name = request_.name();
        ui.password = request_.password();

        const UserRegisterStatus status = [&]() -> UserRegisterStatus
        {
            UserRegisterStatus status;
            switch(db_.registerUser(ui) )
            {
            case IDatabase::Result::ok:
                status.set_status(UserRegisterStatus::Status::UserRegisterStatus_Status_ok);
                break;
            case IDatabase::Result::wrongEmail:
                status.set_status(UserRegisterStatus::Status::UserRegisterStatus_Status_emailTaken);
                break;
            case IDatabase::Result::wrongLogin:
                status.set_status(UserRegisterStatus::Status::UserRegisterStatus_Status_nameTaken);
                break;
            default:
                std::cerr << __func__ << "unsupported database result" << std::endl;
                status.set_status(UserRegisterStatus::Status::UserRegisterStatus_Status_error);
                break;
            }
            return status;
        }();

        responder_.Finish(status, grpc::Status::OK, this);
        new requestHandler::RegisterUser (service_, cq_, db_);
        status_ = Status::done;
    }
    else
    {
        std::cout << "Destroying " << this << std::endl;
        delete this;
    }
    return true;
}

} // requestHandler
} // server
} // casisco
