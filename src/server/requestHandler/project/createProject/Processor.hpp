#pragma once
#include "common/Logger.hpp"

namespace casisco
{
class ProjectInfo;
class ReplyStatus;

namespace server
{
namespace requestHandler
{
namespace createProject
{

class Processor
{
public:
    explicit Processor();
    ReplyStatus process(casisco::ProjectInfo& request );

private:
    common::Logger log_;
};

} // createProject
} // requestHandler
} // server
} // casisco
