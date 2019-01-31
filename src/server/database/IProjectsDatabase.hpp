#pragma once
#include <string>
#include "Result.hpp"

namespace casisco
{
namespace server
{
namespace db
{

struct ProjectInfo
{
    std::string name;
    std::string author;
};

class IProjectsDatabase
{
public:
    virtual ~IProjectsDatabase() = default;
    virtual bool init()  = 0;
    virtual EResult createProject(const ProjectInfo&) = 0;
};

} // db
} // server
} // casisco
