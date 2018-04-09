#pragma once
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
namespace loginUser
{

class Handler : public IHandler
{
public:
    Handler(Casisco::AsyncService*, grpc::ServerCompletionQueue*, IDatabase&);
    virtual bool process() override;

private:
    Casisco::AsyncService* service_;
    grpc::ServerCompletionQueue* cq_;
    grpc::ServerContext ctx_;
    grpc::ServerAsyncResponseWriter<UserLoginStatus> responder_;
    UserLoginInfo request_;
    IDatabase& db_;

    enum class Status
    {
        processing,
        done
    };

    Status status_;
};

} //loginUser
} // requestHandler
} // server
} // casisco
