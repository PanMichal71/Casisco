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

    leveldb::Status status = leveldb::DB::Open(options, "./testdb", &db);
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

    std::string valueFound ;
    const auto s = db_->Get({}, info.name, &valueFound);
    if(not s.IsNotFound())
    {
        log_ << DEBUG << "user: " << info.name << " already exists";
        return Result::wrongLogin;
    }

    log_ << DEBUG << "user: " << info.name << " successfully registed";
    auto res = db_->Put({}, info.name, info.password);
    return res.ok() ? Result::ok : Result::wrongLogin;
    return Result::ok;
}

IDatabase::Result Database::loginUser(const UserInfo &info)
{
    std::string value;
    auto res = db_->Get({}, info.name, &value);
    if(res.ok() && value == info.password)
        return Result::ok;

    return Result::wrongPassword;
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
