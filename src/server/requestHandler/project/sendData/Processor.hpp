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
namespace sendData
{

class Processor
{
public:
    ReplyStatus process(db::IProjectsDatabase& db, casisco::ProjectInfo& request);
};

} // sendData
} // requestHandler
} // server
} // casisco
