#include "Handler.hpp"
#include "Processor.hpp"

#include "server/database/IUsersDatabase.hpp"

namespace casisco
{
namespace server
{
namespace requestHandler
{
namespace user
{
namespace register_
{

Handler::Handler(Casisco::AsyncService *service, grpc::ServerCompletionQueue *cq, db::IUsersDatabase &db)
    : log_("registerUser::Handler")
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
        status_ = EStatus::done;
    }
    else
    {
        log_ << DEBUG << "Destroying " << this;
        new Handler (service_, cq_, db_);
        delete this;
    }
    return true;
}

} // register_
} // user
} // requestHandler
} // server
} // casisco
