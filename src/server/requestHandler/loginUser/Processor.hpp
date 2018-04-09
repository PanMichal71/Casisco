#pragma once

namespace casisco
{
class UserRegisterInfo;
class UserRegisterStatus;

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
    UserRegisterStatus process(IDatabase& db, casisco::UserRegisterInfo& userRegisterInfo );
};

} // loginUser
} // requestHandler
} // server
} // casisco
