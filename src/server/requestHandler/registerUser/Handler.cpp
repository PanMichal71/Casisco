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
    : log_("requestHandler::registerUser::Handler")
    , service_(service)
    , cq_(cq)
    , responder_(&ctx_)
    , db_(db)
    , status_(EStatus::processing)
{
    service_->RequestregisterUser(&ctx_, &request_, &responder_, cq_, cq_, this);
}

bool Handler::process()
{
    if(status_ == EStatus::processing)
    {
        log_ << DEBUG << "Processing " << this;
        Processor processor;
        const auto status = processor.process(db_, request_);

        responder_.Finish(status, grpc::Status::OK, this);
        new Handler (service_, cq_, db_);
        status_ = EStatus::done;
    }
    else
    {
        log_ << DEBUG << "Destroying " << this;
        delete this;
    }
    return true;
}

} // registerUser
} // requestHandler
} // server
} // casisco
