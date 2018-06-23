#pragma once
#include "Logger.hpp"
#include "server/requestHandler/IHandler.hpp"
#include "casisco.grpc.pb.h"
#include <grpc++/grpc++.h>

namespace casisco
{

namespace server
{
class IDatabase;
namespace requestHandler
{
namespace user
{
namespace login
{

class Handler : public IHandler
{
public:
    Handler(Casisco::AsyncService*, grpc::ServerCompletionQueue*, IDatabase&);
    virtual bool process() override;

private:
    common::Logger log_;
    Casisco::AsyncService* service_;
    grpc::ServerCompletionQueue* cq_;
    grpc::ServerContext ctx_;
    grpc::ServerAsyncResponseWriter<UserLoginStatus> responder_;
    UserLoginInfo request_;
    IDatabase& db_;

    enum class EStatus
    {
        processing,
        done
    };

    EStatus status_;
};

} // login
} // user
} // requestHandler
} // server
} // casisco
