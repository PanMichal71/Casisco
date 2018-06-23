#include "Database.hpp"
#include "leveldb/db.h"
#include <boost/filesystem.hpp>

namespace casisco
{
namespace server
{
namespace requestHandler
{
namespace user
{
Database::Database()
    :log_("Database")
{   
}

Database::~Database()
{
}

namespace
{
auto openDb(const std::string& dbName) -> std::unique_ptr<leveldb::DB>
{
    leveldb::DB* db;
    leveldb::Options options;
    options.create_if_missing = true;
    const auto status = leveldb::DB::Open(options, dbName, &db);
    return status.ok() ? std::unique_ptr<leveldb::DB>(db) : nullptr;
}
} //namespace

bool Database::init()
{
    boost::filesystem::create_directories("databases");
    usersDb_  = openDb("./databases/users");
    emailsDb_ = openDb("./databases/emails");
    if(usersDb_ == nullptr or emailsDb_ == nullptr)
    {
        log_ << ERROR << "Failed to open databases";
        return false;
    }

    return true;
}

IDatabase::Result Database::registerUser(const UserInfo &info)
{
    log_ << DEBUG << __func__;
    if(not usersDb_)
    {
        log_ << ERROR << "uninitialized";
        return Result::error;
    }

    if(userExists(info.name))
    {
        log_ << DEBUG << "user: " << info.name << " already exists";
        return Result::loginTaken;
    }
    const auto res = usersDb_->Put({}, info.name, info.password);
    const auto mail_res = emailsDb_->Put({}, info.name, info.email);

    if(res.ok() and mail_res.ok())
        log_ << DEBUG << "user: " << info.name << " successfully registered";

    return res.ok() and mail_res.ok() ? Result::ok : Result::loginTaken;
}

IDatabase::Result Database::loginUser(const UserInfo &info)
{
    std::string password;
    const auto res = usersDb_->Get({}, info.name, &password);
    if(not res.ok())
    {
        log_ << DEBUG << "couldn't find " << info.name << " in database";
        return Result::failedToLogin;
    }
    return  password == info.password ? Result::ok : Result::failedToLogin;
}

IDatabase::Result Database::updateUser(const UserInfo &)
{
    return Result::ok;
}

IDatabase::Result Database::removeUser(const UserInfo &)
{
    return Result::ok;
}

bool Database::userExists(const std::string &name) const
{
    std::string valueFound ;
    const auto s = usersDb_->Get({}, name, &valueFound);
    return s.ok();
}

} // user
} // requestHandler
} // server
} // casisco
