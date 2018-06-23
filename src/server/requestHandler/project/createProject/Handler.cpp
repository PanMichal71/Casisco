#include "Handler.hpp"
#include "Processor.hpp"

namespace casisco
{

namespace server
{
class IDatabase;
namespace requestHandler
{
namespace createProject
{

Handler::Handler(Casisco::AsyncService *service, grpc::ServerCompletionQueue *cq)
    : log_("server::requestHandler::createProject::Handler")
    , service_(service)
    , cq_(cq)
    , responder_(&ctx_)
    , status_(Status::processing)
{
    service_->RequestcreateProject(&ctx_, &request_, &responder_, cq_, cq_, this);
}


bool Handler::process()
{
    if(status_ == Status::processing)
    {
        log_ << DEBUG << "Processing " << this;
        Processor processor;
        const auto status = processor.process(request_);

        responder_.Finish(status, grpc::Status::OK, this);
        new Handler (service_, cq_);
        status_ = Status::done;
    }
    else
    {
        log_ << DEBUG << "Destroying " << this;
        delete this;
    }
    return true;
}


} // createProject
} // requestHandler
} // server
} // casisco
    
