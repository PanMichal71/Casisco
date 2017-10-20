#pragma once
#include <grpc++/grpc++.h>
#include <grpc/support/log.h>
#include "casisco.grpc.pb.h"

#include <string>

namespace casisco
{
namespace server
{

class Server final
{
public:
    Server(const std::string& serverAddress);
	~Server();
private:
//    class CallData
//    {
//    public:
//        CallData(Greeter::AsyncService* service, ServerCompletionQueue* cq)
//            : service_(service)
//            , cq_(cq), responder_(&ctx_)
//            , status_(CREATE)
//        {
//            Proceed();
//        }

//        void Proceed()
//        {
//            if(status_ == CREATE)
//            {
//                status_ = PROCESS;
//                service_->RequestregisterUser(&ctx_, &request_, &responder_, cq_, cq_, this);
//            }
//            else if(status_ == PROCESS)
//            {
//                new CallData(service_, cq_);
//                std::string prefix("Hello ");
//                reply_.set_message(prefix + request_.name());
//                status_ = FINISH;
//                responder_.Finish(reply_, Status::OK, this);
//            }
//            else
//            {
//                GPR_ASSERT(status_ == FINISH);
//                delete this;
//            }
//        }

//    private:
//        Casisco::AsyncService* service_;
//        grpc::ServerCompletionQueue* cq_;
//        grpc::ServerContext ctx_;

//        ServerAsyncResponseWriter<HelloReply> responder_;
//        enum CallStatus
//        {
//            CREATE,
//            PROCESS,
//            FINISH
//        };
//        CallStatus status_;
//    };

private:
    const std::string address_;
    Casisco::AsyncService service_;
    std::unique_ptr<grpc::Server> server_;
    std::unique_ptr<grpc::ServerCompletionQueue> completionQueue_;
};

} // server
} // casisco
