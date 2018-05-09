#include "Handler.hpp"
#include "Processor.hpp"
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
        Processor processor;
        const auto status = processor.process(db_, request_);
        std::cout << "Received name: " << request_.name() << " password: " << request_.password() << std::endl;

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

} // loginUser
} // requestHandler
} // server
} // casisco
