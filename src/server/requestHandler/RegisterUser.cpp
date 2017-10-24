#include "RegisterUser.hpp"
#include <iostream>

namespace casisco
{
namespace server
{
namespace requestHandler
{

RegisterUser::RegisterUser(Casisco::AsyncService *service, grpc::ServerCompletionQueue *cq)
    : service_(service)
    , cq_(cq)
    , responder_(&ctx_)
    , status_(Status::processing)
{
    service_->RequestregisterUser(&ctx_, &request_, &responder_, cq_, cq_, this);
}

bool RegisterUser::process()
{
    if(status_ == Status::processing)
    {
        std::cout << "Processing " << this << std::endl;
        UserRegisterStatus status;
        status.set_status(UserRegisterStatus::Status::UserRegisterStatus_Status_ok);
        std::cout << "Received name: " << request_.name() << " password: "
                  << request_.password() << " email: " << request_.email() << std::endl;
        responder_.Finish(status, grpc::Status::OK, this);
        new requestHandler::RegisterUser (service_, cq_);
        status_ = Status::done;
        return true;
    }
    else
    {
        std::cout << "Destroying " << this << std::endl;
        delete this;
    }
}

} // requestHandler
} // server
} // casisco
