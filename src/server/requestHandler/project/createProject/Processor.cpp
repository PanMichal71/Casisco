#include "Processor.hpp"
#include "casisco.pb.h"

namespace casisco
{
namespace server
{
namespace requestHandler
{
namespace createProject
{

Processor::Processor()
    : log_("requestHandler::createProject::Processor")
{

}

ReplyStatus Processor::process(ProjectInfo &request)
{
    return {};
}


} // createProject
} // requestHandler
} // server
} // casisco
