#include "Database.hpp"
namespace casisco
{
namespace server
{

IDatabase::Result Database::registerUser(const UserInfo &)
{
    return Result::ok;
}

IDatabase::Result Database::loginUser(const UserInfo &)
{
    return Result::ok;
}

IDatabase::Result Database::updateUser(const UserInfo &)
{
    return Result::ok;
}

IDatabase::Result Database::removeUser(const UserInfo &)
{
    return Result::ok;
}


} // server
} // casisco
