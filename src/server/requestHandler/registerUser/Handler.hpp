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
namespace registerUser
{

class Handler : public IHandler
{
public:
    Handler(Casisco::AsyncService*, grpc::ServerCompletionQueue*, IDatabase &);
    Handler() = delete;
    Handler(const Handler&) = delete;
    Handler(const Handler&&) = delete;
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

} // registerUser
} // requestHandler
} // server
} // casisco
