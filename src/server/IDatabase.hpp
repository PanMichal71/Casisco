#pragma once
#include <string>

namespace casisco
{
namespace server
{

struct UserInfo
{
    std::string name;
    std::string password;
    std::string email;
};

class IDatabase
{
public:
    virtual ~IDatabase() = default;

    virtual bool registerUser(const UserInfo&) = 0;
    virtual bool loginUser(const UserInfo&)    = 0;
    virtual bool updateUser(const UserInfo&)   = 0;
    virtual bool removeUser(const UserInfo&)   = 0;
};

} // server
} // casisco
