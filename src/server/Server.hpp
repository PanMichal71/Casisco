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

    void run();

private:
    const std::string address_;
    Casisco::AsyncService service_;
    std::unique_ptr<grpc::Server> server_;
    std::unique_ptr<grpc::ServerCompletionQueue> completionQueue_;
};

} // server
} // casisco
