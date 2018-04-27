#pragma once
#include "IDatabase.hpp"
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

class Database : public IDatabase
{
public:
    explicit Database();
    ~Database();
    virtual bool init() override;
    virtual Result registerUser(const UserInfo&) override;
    virtual Result loginUser(const UserInfo&) override;
    virtual Result updateUser(const UserInfo&) override;
    virtual Result removeUser(const UserInfo&) override;

private:
    bool userExists(const std::string& name) const;

private:
    common::Logger log_;
    std::unique_ptr<leveldb::DB> db_;
};

} // server
} // casisco
