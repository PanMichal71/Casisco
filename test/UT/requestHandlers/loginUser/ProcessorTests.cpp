#include "server/requestHandler/user/login/Processor.hpp"
#include "mocks/server/IDatabaseMock.hpp"
#include "casisco_mock.grpc.pb.h"
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <vector>

using ::testing::_;
using ::testing::Return;

namespace casisco
{
namespace server
{
namespace requestHandler
{
namespace user
{
namespace login
{

typedef UserLoginStatus::Status StatusType;
typedef std::pair<db::EResult, UserLoginStatus_Status> DataType;

struct LoginUserProcessorShould : ::testing::TestWithParam<DataType>
{
    Processor sut_;
    db::UsersDatabaseMock dbMock_;
};

TEST_P(LoginUserProcessorShould, setStatusOkIfSucceded)
{
    EXPECT_CALL(dbMock_, loginUser(_)).WillOnce(Return(GetParam().first));
    UserLoginInfo request;
    auto result = sut_.process(dbMock_, request);
    UserLoginStatus expectedStatus;
    expectedStatus.set_status(GetParam().second);
    EXPECT_EQ(expectedStatus.status(), result.status());
}

const std::vector<DataType> data = {
    std::make_pair(db::EResult::ok, StatusType::UserLoginStatus_Status_ok),
    std::make_pair(db::EResult::error, StatusType::UserLoginStatus_Status_error)
};

INSTANTIATE_TEST_CASE_P(DbResultPattern, LoginUserProcessorShould, testing::ValuesIn(data),);

} // login
} // user
} // requestHandler
} // server
} // casisco
