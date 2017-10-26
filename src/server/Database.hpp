#pragma once
#include "IDatabase.hpp"

namespace casisco
{
namespace server
{

class Database : public IDatabase
{
public:
    virtual bool registerUser(const UserInfo&) override;
    virtual bool loginUser(const UserInfo&) override;
    virtual bool updateUser(const UserInfo&) override;
    virtual bool removeUser(const UserInfo&) override;
};

} // server
} // casisco
