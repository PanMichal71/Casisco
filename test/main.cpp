#include <gmock/gmock.h>
#include "server/Server.hpp"

int main (int argc, char** argv)
{
    ::testing::InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
}
