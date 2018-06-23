#pragma once
#include "server/requestHandler/user/IDatabase.hpp"
#include <gmock/gmock.h>
namespace casisco
{
namespace server
{
namespace requestHandler
{
class IDatabaseMock : public IDatabase
{
public:
    MOCK_METHOD0(init, bool());
    MOCK_METHOD1(registerUser, Result (const UserInfo&));
    MOCK_METHOD1(loginUser, Result (const UserInfo&));
    MOCK_METHOD1(updateUser, Result (const UserInfo&));
    MOCK_METHOD1(removeUser, Result (const UserInfo&));
};

} // requestHandler
} // server
} // casisco
