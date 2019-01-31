#include "Processor.hpp"
#include "common/Logger.hpp"
#include "server/database/IProjectsDatabase.hpp"

#include "casisco.pb.h"
#include "casisco.grpc.pb.h"

namespace casisco
{
namespace server
{
namespace requestHandler
{
namespace sendData
{
namespace
{
common::Logger log("requestHandler::sendData::Processor");
} // namespace

ReplyStatus Processor::process( db::IProjectsDatabase &db, ProjectInfo &request)
{
    const db::ProjectInfo pi{
        request.name(),
        request.author()
    };
    const auto status = [&]() -> ReplyStatus_Status
    {
        typedef ReplyStatus::Status StatusType;
        ReplyStatus_Status status;
        switch(db.createProject(pi))
        {
        case db::EResult::ok:
            status = StatusType::ReplyStatus_Status_ok;
            break;
        default:
            status = StatusType::ReplyStatus_Status_error;
            break;
        }
        return status;
    }();

    ReplyStatus result;
    result.set_status(status);
    return result;
}

} // sendData
} // requestHandler
} // server
} // casisco
