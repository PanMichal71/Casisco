#include "Server.hpp"
#include "requestHandler/LoginUser.hpp"
#include "requestHandler/RegisterUser.hpp"

#include <iostream>
#include <thread>

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

void Server::run()
{
    new requestHandler::LoginUser (&service_, completionQueue_.get());
    new requestHandler::RegisterUser(&service_, completionQueue_.get());
    void* tag;
    bool ok;
    std::cout << "Listening.."<<std::endl;
    while(true)
    {
        GPR_ASSERT(completionQueue_->Next(&tag, &ok));
        GPR_ASSERT(ok);
        static_cast<requestHandler::IHandler*>(tag)->process();
    }
}

} // server
} // casisco
