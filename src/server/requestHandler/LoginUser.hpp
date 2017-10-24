#pragma once
#include "IHandler.hpp"
#include <grpc++/grpc++.h>
#include "casisco.grpc.pb.h"
#include <memory>

namespace casisco
{

namespace server
{
namespace requestHandler
{

class LoginUser : public IHandler
{
public:
    LoginUser(Casisco::AsyncService*, grpc::ServerCompletionQueue*);
    virtual bool process();
    int finish();
    int request();

private:
    Casisco::AsyncService* service_;
    grpc::ServerCompletionQueue* cq_;
    grpc::ServerContext ctx_;
    grpc::ServerAsyncResponseWriter<UserRegisterStatus> responder_;
    casisco::UserRegisterInfo request_;
    int tag_;

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
