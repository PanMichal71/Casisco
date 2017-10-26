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

class RegisterUser : public IHandler
{
public:
    RegisterUser(Casisco::AsyncService*, grpc::ServerCompletionQueue*, IDatabase &);
    virtual bool process() override;

private:
    Casisco::AsyncService* service_;
    grpc::ServerCompletionQueue* cq_;
    grpc::ServerContext ctx_;
    grpc::ServerAsyncResponseWriter<UserRegisterStatus> responder_;
    casisco::UserRegisterInfo request_;
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
