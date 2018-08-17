#pragma once
#include <string>
#include "IProjectsDatabase.hpp"

namespace casisco
{
namespace server
{
namespace db
{

class ProjectsDatabase : public IProjectsDatabase
{
public:
    bool init() override;
    EResult createProject(const ProjectInfo&) override;
};

} // db
} // server
} // casisco
