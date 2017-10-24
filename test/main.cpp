#include <gmock/gmock.h>
#include "server/Server.hpp"

int main (int argc, char** argv)
{
//    ::testing::InitGoogleMock(&argc, argv);
//    return RUN_ALL_TESTS();

    casisco::server::Server server("127.0.0.1:50051");
    server.run();
    return 0;
}
