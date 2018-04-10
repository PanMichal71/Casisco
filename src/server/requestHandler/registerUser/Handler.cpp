#include "Handler.hpp"
#include "Processor.hpp"

#include "server/IDatabase.hpp"

#include <iostream>

namespace casisco
{
namespace server
{
namespace requestHandler
{
namespace registerUser
{

Handler::Handler(Casisco::AsyncService *service, grpc::ServerCompletionQueue *cq, IDatabase &db)
    : service_(service)
    , cq_(cq)
    , responder_(&ctx_)
    , db_(db)
    , status_(Status::processing)
{
    service_->RequestregisterUser(&ctx_, &request_, &responder_, cq_, cq_, this);
}

bool Handler::process()
{
    if(status_ == Status::processing)
    {
        std::cout << "Processing " << this << std::endl;
        std::cout << "Received name: " << request_.name() << " password: "
                  << request_.password() << " email: " << request_.email() << std::endl;

        Processor processor;
        const UserRegisterStatus status = processor.process(db_, request_);

        responder_.Finish(status, grpc::Status::OK, this);
        new Handler (service_, cq_, db_);
        status_ = Status::done;
    }
    else
    {
        std::cout << "Destroying " << this << std::endl;
        delete this;
    }
    return true;
}

} // registerUser
} // requestHandler
} // server
} // casisco