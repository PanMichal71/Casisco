#include "UsersDatabase.hpp"
#include "leveldb/db.h"
#include <boost/filesystem.hpp>

namespace casisco
{
namespace server
{
namespace db
{

namespace
{
common::Logger log("UsersDatabase");

auto openDb(const std::string& dbName) -> std::unique_ptr<leveldb::DB>
{
    leveldb::DB* db;
    leveldb::Options options;
    options.create_if_missing = true;
    const auto status = leveldb::DB::Open(options, dbName, &db);
    return status.ok() ? std::unique_ptr<leveldb::DB>(db) : nullptr;
}
} //namespace

bool UsersDatabase::init()
{
    boost::filesystem::create_directories("databases");
    usersDb_  = openDb("./databases/users");
    emailsDb_ = openDb("./databases/emails");
    if(usersDb_ == nullptr or emailsDb_ == nullptr)
    {
        log << ERROR << "Failed to open databases";
        return false;
    }

    return true;
}

bool UsersDatabase::userExists(const UserInfo &info) const
{
    std::string valueFound ;
    const auto s = usersDb_->Get({}, info.name, &valueFound);
    return s.ok();
}

EResult UsersDatabase::registerUser(const UserInfo &info)
{
    log << DEBUG << __func__;
    if(not usersDb_)
    {
        log << ERROR << "uninitialized";
        return EResult::error;
    }

    if(userExists(info))
    {
        log << DEBUG << "user: " << info.name << " already exists";
        return EResult::alreadyExists;
    }
    const auto res = usersDb_->Put({}, info.name, info.password);
    const auto mail_res = emailsDb_->Put({}, info.name, info.email);

    if(res.ok() and mail_res.ok())
        log << DEBUG << "user: " << info.name << " successfully registered";

    return res.ok() and mail_res.ok() ? EResult::ok : EResult::alreadyExists;
}

EResult UsersDatabase::loginUser(const UserInfo &info)
{
    std::string password;
    const auto res = usersDb_->Get({}, info.name, &password);
    if(not res.ok())
    {
        log << DEBUG << "couldn't find " << info.name << " in database";
        return EResult::error;
    }
    return  password == info.password ? EResult::ok : EResult::alreadyExists;
}

EResult UsersDatabase::updateUser(const UserInfo &)
{
    return EResult::ok;
}

EResult UsersDatabase::removeUser(const UserInfo &)
{
    return EResult::ok;
}

} // db
} // server
} // casisco
