#pragma once
#include "Logger.hpp"
#include "server/requestHandler/IHandler.hpp"
#include "casisco.grpc.pb.h"
#include <grpc++/grpc++.h>

namespace casisco
{

namespace server
{
namespace requestHandler
{
namespace createProject
{

class Handler : public IHandler
{
public:
    Handler(Casisco::AsyncService*, grpc::ServerCompletionQueue*);
    virtual bool process() override;

private:
    common::Logger log_;
    Casisco::AsyncService* service_;
    grpc::ServerCompletionQueue* cq_;
    grpc::ServerContext ctx_;
    grpc::ServerAsyncResponseWriter<ReplyStatus> responder_;
    ProjectInfo request_;

    enum class Status
    {
        processing,
        done
    };

    Status status_;
};
} // createProject
} // requestHandler
} // server
} // casisco
