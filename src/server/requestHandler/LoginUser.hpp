#pragma once
#include "IHandler.hpp"
#include "casisco.grpc.pb.h"
#include <grpc++/grpc++.h>

namespace casisco
{

namespace server
{
class IDatabase;
namespace requestHandler
{

class LoginUser : public IHandler
{
public:
    LoginUser(Casisco::AsyncService*, grpc::ServerCompletionQueue*, IDatabase&);
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

} // requestHandler
} // server
} // casisco
