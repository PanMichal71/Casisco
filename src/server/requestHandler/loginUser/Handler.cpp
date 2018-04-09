#include "Handler.hpp"
#include <iostream>

namespace casisco
{
namespace server
{
namespace requestHandler
{
namespace loginUser
{
Handler::Handler(Casisco::AsyncService *service, grpc::ServerCompletionQueue *cq, IDatabase &db)
    : service_(service)
    , cq_(cq)
    , responder_(&ctx_)
    , db_(db)
    , status_(Status::processing)
{
    service_->RequestloginUser(&ctx_, &request_, &responder_, cq_, cq_, this);
}

bool Handler::process()
{
    if(status_ == Status::processing)
    {
        std::cout << "Processing " << this << std::endl;
        UserLoginStatus status;
        status.set_status(UserLoginStatus::Status::UserLoginStatus_Status_ok);
        std::cout << "Received name: " << request_.name() << " password: " << request_.password() << std::endl;
        responder_.Finish(status, grpc::Status::OK, this);
        new loginUser::Handler (service_, cq_, db_);
        status_ = Status::done;
    }
    else
    {
        std::cout << "Destroying " << this << std::endl;
        delete this;
    }
    return true;
}

} // loginUser
} // requestHandler
} // server
} // casisco
