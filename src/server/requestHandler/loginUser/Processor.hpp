#pragma once
#include "common/Logger.hpp"

namespace casisco
{
class UserLoginInfo;
class UserLoginStatus;

namespace server
{
class IDatabase;

namespace requestHandler
{
namespace loginUser
{

class Processor
{
public:
    explicit Processor();
    UserLoginStatus process(IDatabase& db, casisco::UserLoginInfo& request );

private:
    common::Logger log_;
};

} // loginUser
} // requestHandler
} // server
} // casisco
