#pragma once
#include "Logger.hpp"
#include "server/requestHandler/IHandler.hpp"
#include "casisco.grpc.pb.h"
#include <grpc++/grpc++.h>

namespace casisco
{

namespace server
{
namespace db
{
class IProjectsDatabase;
} // namespace db

namespace requestHandler
{
namespace sendData
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
    ProjectBinaryData request_;
    grpc::ServerAsyncReader<ReplyStatus, ProjectBinaryData> reader_;
    std::unique_ptr<IHandler> streamFinishedHandler_;

    enum class Status
    {
        idle,
        processing,
        done
    };

    Status status_;
};
} // sendData
} // requestHandler
} // server
} // casisco
