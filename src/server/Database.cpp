#include "Database.hpp"
#include "leveldb/db.h"

namespace casisco
{
namespace server
{

Database::Database()
    :log_("Database")
{   
}

Database::~Database()
{
}

bool Database::init()
{
    leveldb::DB* db;
    leveldb::Options options;
    options.create_if_missing = true;

    leveldb::Status status = leveldb::DB::Open(options, "./database", &db);
    if(not status.ok())
    {
        log_<< ERROR << "Failed to open!!";
        return false;
    }

    db_ = std::unique_ptr<leveldb::DB>(db);
    return true;
}

IDatabase::Result Database::registerUser(const UserInfo &info)
{
    log_ << DEBUG << __func__;
    if(not db_)
    {
        log_ << ERROR << "uninitialized";
        return Result::error;
    }

    if(userExists(info.name))
    {
        log_ << DEBUG << "user: " << info.name << " already exists";
        return Result::loginTaken;
    }

    log_ << DEBUG << "user: " << info.name << " successfully registed";
    auto res = db_->Put({}, info.name, info.password);
    return res.ok() ? Result::ok : Result::loginTaken;
}

IDatabase::Result Database::loginUser(const UserInfo &info)
{
    std::string password;
    const auto res = db_->Get({}, info.name, &password);
    return res.ok() && password == info.password ? Result::ok : Result::failedToLogin;
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
    const auto s = db_->Get({}, name, &valueFound);
    return s.ok();
}


} // server
} // casisco
