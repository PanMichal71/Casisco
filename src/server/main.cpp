#include "server/Server.hpp"
#include "common/Logger.hpp"

int main (int argc, char** argv)
{
    if(argc < 2)
    {
        casisco::common::Logger logger("");
        logger << casisco::ERROR << "Please pass ip address and port in format ip:port";
        return 1;
    }
    casisco::server::Server server("127.0.0.1:50051");
    server.run();
    return 0;
}
