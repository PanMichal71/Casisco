#include "server/requestHandler/RegisterUser.hpp"
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include "casisco_mock.grpc.pb.h"

namespace casisco
{
namespace server
{
namespace requestHandler
{

struct test : public testing::Test
{
    virtual void SetUp() override
    {

    }

    std::shared_ptr<RegisterUser> sut_;
};

} // requestHandler
} // server
} // casisco
