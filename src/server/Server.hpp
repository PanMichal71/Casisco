#pragma once
#include "common/Logger.hpp"
#include "casisco.grpc.pb.h"
#include <string>

namespace grpc
{
class Server;
class ServerCompletionQueue;
}


namespace casisco
{
namespace server
{

class Server final
{
public:
    Server(const std::string& serverAddress);
	~Server();

    void run();

private:
    common::Logger log_;
    const std::string address_;
    Casisco::AsyncService service_;
    std::unique_ptr<grpc::Server> server_;
    std::unique_ptr<grpc::ServerCompletionQueue> completionQueue_;
};

} // server
} // casisco
