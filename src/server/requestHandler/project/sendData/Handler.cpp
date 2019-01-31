#include "Handler.hpp"
#include "Processor.hpp"
#include <fstream>

namespace casisco
{

namespace server
{
namespace requestHandler
{
namespace sendData
{

class StreamFinishedHandler: public IHandler
{
public:
    StreamFinishedHandler(std::function<void()> finishedCallback)
        : finishedCallback_(finishedCallback)
    {}

    bool process() override
    {
        common::Logger log ("StreamFinishedHandler");
        log << INFO << __FUNCTION__;
        finishedCallback_();
        return true;
    }

private:
    std::function<void()> finishedCallback_;
};

Handler::Handler(Casisco::AsyncService *service, grpc::ServerCompletionQueue *cq)
    : log_("server::requestHandler::sendData::Handler")
    , service_(service)
    , cq_(cq)
    , reader_(&ctx_)
    , streamFinishedHandler_(std::make_unique<StreamFinishedHandler>([this](){
         status_ = Status::done;
        }))
    , status_(Status::idle)
{
    log_ << INFO << __FUNCTION__;


    service_->RequestsendData(&ctx_, &reader_, cq_, cq_, this);
}

bool Handler::process()
{
    log_ << INFO << __FUNCTION__ << " " << (int)status_;
    if(status_ == Status::idle)
    {
        ctx_.AsyncNotifyWhenDone(streamFinishedHandler_.get()); // to trzeba sprawdzic czemu nie wywolalo sie
        status_ = Status::processing;
    }

    if(status_ == Status::done)
    {
        log_ << DEBUG << "Destroying " << this;
        std::fstream file("OUTPUT_FILE.txt");
        if(file)
        {
            log_ << DEBUG << "Saving data of size: " << request_.data().size();
            file << request_.data();
        }

        std::fstream file2("BINARY_FILE.txt");
        if(file2)
        {
            log_ << DEBUG << "Saving binary file of size: " << request_.binaryfile().size();
            file2 << request_.binaryfile();
        }
        ReplyStatus replyStatus;
        replyStatus.set_status(ReplyStatus_Status::ReplyStatus_Status_ok);
        reader_.Finish(replyStatus, grpc::Status::OK, this);

        new Handler (service_, cq_);
        delete this;
        return true;
    }

    log_ << DEBUG << "Processing " << this;
    reader_.Read(&request_, this);
    log_ << WARNING << "current data  size: " << request_.data().size();
    log_ << WARNING << "current binary file size: " << request_.binaryfile().size();
    return true;
}


} // sendData
} // requestHandler
} // server
} // casisco
    
