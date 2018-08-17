#include "ProjectsDatabase.hpp"

namespace casisco
{
namespace server
{
namespace db
{

bool ProjectsDatabase::init()
{
    return true;
}

EResult ProjectsDatabase::createProject(const ProjectInfo &)
{
    return EResult::ok;
}


} // db
} // server
} // casisco
