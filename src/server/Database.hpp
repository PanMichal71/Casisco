#pragma once
#include "IDatabase.hpp"

namespace casisco
{
namespace server
{

class Database : public IDatabase
{
public:
    virtual Result registerUser(const UserInfo&) override;
    virtual Result loginUser(const UserInfo&) override;
    virtual Result updateUser(const UserInfo&) override;
    virtual Result removeUser(const UserInfo&) override;
};

} // server
} // casisco
