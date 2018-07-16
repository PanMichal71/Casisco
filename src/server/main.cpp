#include "server/Server.hpp"
#include "common/Logger.hpp"

int main (int argc, char** argv)
{
    casisco::common::Logger logger("Server");
    if(argc < 2)
    {
        logger << casisco::ERROR << "Please pass ip address and port in format ip:port";
        return 1;
    }
    const std::string address {argv[1]};

    casisco::server::Server server(address);
    server.run();
    
    return 0;
}
