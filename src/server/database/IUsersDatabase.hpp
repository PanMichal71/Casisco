#pragma once
#include <string>
#include "Result.hpp"

namespace casisco
{
namespace server
{
namespace db
{

struct UserInfo
{
    std::string name;
    std::string password;
    std::string email;
};

class IUsersDatabase
{
public:
    virtual ~IUsersDatabase() = default;
    virtual bool init()  = 0;
    virtual EResult registerUser(const UserInfo&)  = 0;
    virtual EResult loginUser(const UserInfo&)     = 0;
    virtual EResult updateUser(const UserInfo&)    = 0;
    virtual EResult removeUser(const UserInfo&)    = 0;
    virtual bool userExists(const UserInfo&) const = 0;
};

} // db
} // server
} // casisco
