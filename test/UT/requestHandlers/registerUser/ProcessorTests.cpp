#include "server/requestHandler/user/register/Processor.hpp"
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
namespace register_
{
typedef UserRegisterStatus::Status StatusType;
typedef std::pair<IDatabase::Result, UserRegisterStatus_Status> DataType;

struct ProcessorShould : ::testing::TestWithParam<DataType>
{
    Processor sut_;
    IDatabaseMock dbMock_;
};

TEST_P(ProcessorShould, setStatusOkIfSucceded)
{
    EXPECT_CALL(dbMock_, registerUser(_)).WillOnce(Return(GetParam().first));
    UserRegisterInfo request;
    auto result = sut_.process(dbMock_, request);
    UserRegisterStatus expectedStatus;
    expectedStatus.set_status(GetParam().second);
    EXPECT_EQ(expectedStatus.status(), result.status());
}

const std::vector<DataType> data = {
    std::make_pair(IDatabase::Result::ok, StatusType::UserRegisterStatus_Status_ok),
    std::make_pair(IDatabase::Result::wrongEmail, StatusType::UserRegisterStatus_Status_emailTaken),
    std::make_pair(IDatabase::Result::loginTaken, StatusType::UserRegisterStatus_Status_nameTaken),
    std::make_pair(IDatabase::Result::failedToLogin, StatusType::UserRegisterStatus_Status_error)
};

INSTANTIATE_TEST_CASE_P(name, ProcessorShould, testing::ValuesIn(data),);

} // register_
} // user
} // requestHandler
} // server
} // casisco
