#pragma once

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
    UserLoginStatus process(IDatabase& db, casisco::UserLoginInfo& request );
};

} // loginUser
} // requestHandler
} // server
} // casisco
