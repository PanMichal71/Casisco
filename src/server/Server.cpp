#include "Server.hpp"

#include <grpc++/grpc++.h>
#include <grpc/support/log.h>

#include "requestHandler/Factory.hpp"
#include "requestHandler/IHandler.hpp"
#include "database/Database.hpp"
#include "Context.hpp"
#include <iostream>
#include <thread>

namespace casisco
{
namespace server
{

Server::Server(const std::string& serverAddress)
    : log_("Server")
    , address_(serverAddress)
{
    grpc::ServerBuilder builder;
    builder.AddListeningPort(address_, grpc::InsecureServerCredentials());
    builder.RegisterService(&service_);
    completionQueue_ = builder.AddCompletionQueue();
    server_ = builder.BuildAndStart();
}

Server::~Server()
{
    server_->Shutdown();
    completionQueue_->Shutdown();
    log_ << casisco::INFO << "Leaving.";
}

void Server::run()
{
    requestHandler::Factory factory;
    db::Database database;
    database.init();
    factory.getLoginUser(Context{&service_, completionQueue_.get()}, database);
    factory.getRegisterUser(Context{&service_, completionQueue_.get()}, database);
    void* tag;
    bool ok;
    log_ << INFO << "Listening on: " << address_;
    while(true)
    {
        GPR_ASSERT(completionQueue_->Next(&tag, &ok));
        GPR_ASSERT(ok);
        static_cast<requestHandler::IHandler*>(tag)->process();
    }
}

} // server
} // casisco
