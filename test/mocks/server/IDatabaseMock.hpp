#pragma once
#include "server/IDatabase.hpp"
#include <gmock/gmock.h>
namespace casisco
{
namespace server
{

class IDatabaseMock : public IDatabase
{
public:
    MOCK_METHOD1(registerUser, Result (const UserInfo&));
    MOCK_METHOD1(loginUser, Result (const UserInfo&));
    MOCK_METHOD1(updateUser, Result (const UserInfo&));
    MOCK_METHOD1(removeUser, Result (const UserInfo&));
};

} // server
} // casisco
