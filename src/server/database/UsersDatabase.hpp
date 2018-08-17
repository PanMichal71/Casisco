#pragma once
#include "IUsersDatabase.hpp"
#include "common/Logger.hpp"

#include <memory>

namespace leveldb
{
class DB;
} // leveldb

namespace casisco
{
namespace server
{
namespace db
{

class UsersDatabase final : public IUsersDatabase
{
public:
    bool init() override;
    EResult registerUser(const UserInfo&) override;
    EResult loginUser(const UserInfo&) override;
    EResult updateUser(const UserInfo&) override;
    EResult removeUser(const UserInfo&) override;
    bool userExists(const UserInfo& name) const override;

private:

    std::unique_ptr<leveldb::DB> usersDb_;
    std::unique_ptr<leveldb::DB> emailsDb_;
};

} // db
} // server
} // casisco
