#include "Server.hpp"

namespace casisco
{
namespace server
{

Server::Server(const std::string& serverAddress)
    : address_(serverAddress)
{
    grpc::ServerBuilder builder;
    builder.AddListeningPort(address_,grpc::InsecureServerCredentials());
    builder.RegisterService(&service_);
    completionQueue_ = builder.AddCompletionQueue();
    server_ = builder.BuildAndStart();
}

Server::~Server()
{
    server_->Shutdown();
    completionQueue_->Shutdown();
}


} // server
} // casisco
