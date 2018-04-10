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
    enum class Result
    {
        ok,
        wrongEmail,
        wrongLogin,
        wrongPassword
    };

    virtual ~IDatabase() = default;

    virtual Result registerUser(const UserInfo&) = 0;
    virtual Result loginUser(const UserInfo&)    = 0;
    virtual Result updateUser(const UserInfo&)   = 0;
    virtual Result removeUser(const UserInfo&)   = 0;
};

} // server
} // casisco
