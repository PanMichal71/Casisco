#pragma once
#include "server/database/IUsersDatabase.hpp"
#include <gmock/gmock.h>
namespace casisco
{
namespace server
{
namespace db
{
class UsersDatabaseMock : public IUsersDatabase
{
public:
    MOCK_METHOD0(init, bool());
    MOCK_METHOD1(registerUser, EResult (const UserInfo&));
    MOCK_METHOD1(loginUser, EResult (const UserInfo&));
    MOCK_METHOD1(updateUser, EResult (const UserInfo&));
    MOCK_METHOD1(removeUser, EResult (const UserInfo&));
    MOCK_CONST_METHOD1(userExists, bool(const UserInfo&));
};

} // db
} // server
} // casisco
