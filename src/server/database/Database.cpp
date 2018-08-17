#include "Database.hpp"
#include "UsersDatabase.hpp"
#include "ProjectsDatabase.hpp"

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
common::Logger log("server::Database");
} // namespace

Database::Database()
    : usersDb_(std::make_unique<UsersDatabase>())
    , projectsDb_(std::make_unique<ProjectsDatabase>())
{
}

Database::~Database()
{
}

bool Database::init()
{
    bool res = usersDb_->init();
    res &= projectsDb_->init();
    return res;
}

EResult Database::registerUser(const UserInfo &info)
{
    return usersDb_->registerUser(info);
}

EResult Database::loginUser(const UserInfo &info)
{
    return usersDb_->loginUser(info);
}

EResult Database::updateUser(const UserInfo &info)
{
    return usersDb_->updateUser(info);
}

EResult Database::removeUser(const UserInfo &info)
{
    return usersDb_->removeUser(info);
}

EResult Database::createProject(const ProjectInfo &info)
{
    return projectsDb_->createProject(info);
}

bool Database::userExists(const UserInfo &info) const
{
    return usersDb_->userExists(info);
}

} // db
} // server
} // casisco
