#include "server/requestHandler/loginUser/Processor.hpp"
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
namespace loginUser
{

typedef UserLoginStatus::Status StatusType;
typedef std::pair<IDatabase::Result, UserLoginStatus_Status> DataType;

struct LoginUserProcessorShould : ::testing::TestWithParam<DataType>
{
    Processor sut_;
    IDatabaseMock dbMock_;
};

TEST_P(LoginUserProcessorShould, setStatusOkIfSucceded)
{
    EXPECT_CALL(dbMock_, registerUser(_)).WillOnce(Return(GetParam().first));
    UserLoginInfo request;
    auto result = sut_.process(dbMock_, request);
    UserLoginStatus expectedStatus;
    expectedStatus.set_status(GetParam().second);
    EXPECT_EQ(expectedStatus.status(), result.status());
}

const std::vector<DataType> data = {
    std::make_pair(IDatabase::Result::ok, StatusType::UserLoginStatus_Status_ok),
    std::make_pair(IDatabase::Result::wrongPassword, StatusType::UserLoginStatus_Status_invalidPassword),
    std::make_pair(IDatabase::Result::wrongLogin, StatusType::UserLoginStatus_Status_noSuchUser),
    std::make_pair(IDatabase::Result::wrongEmail, StatusType::UserLoginStatus_Status_error)
};

INSTANTIATE_TEST_CASE_P(DbResultPattern, LoginUserProcessorShould, testing::ValuesIn(data),);

} // loginUser
} // requestHandler
} // server
} // casisco
