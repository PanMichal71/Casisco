#pragma once

namespace casisco
{
class ProjectInfo;
class ReplyStatus;

namespace server
{
namespace db
{
class IProjectsDatabase;
} // namespace db
namespace requestHandler
{
namespace createProject
{

class Processor
{
public:
    ReplyStatus process(db::IProjectsDatabase& db, casisco::ProjectInfo& request);
};

} // createProject
} // requestHandler
} // server
} // casisco
