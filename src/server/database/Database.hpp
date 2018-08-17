#pragma once
#include "IUsersDatabase.hpp"
#include "IProjectsDatabase.hpp"
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

class Database final : public IUsersDatabase, public IProjectsDatabase
{
public:
    explicit Database();
    ~Database();
    bool init() override;
    EResult registerUser(const UserInfo&) override;
    EResult loginUser(const UserInfo&) override;
    EResult updateUser(const UserInfo&) override;
    EResult removeUser(const UserInfo&) override;
    EResult createProject(const ProjectInfo&) override;
    bool userExists(const UserInfo&) const override;

private:

    std::unique_ptr<IUsersDatabase> usersDb_;
    std::unique_ptr<IProjectsDatabase> projectsDb_;
};

} // db
} // server
} // casisco
