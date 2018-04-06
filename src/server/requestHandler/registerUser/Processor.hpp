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
namespace registerUser
{

class Processor
{
public:
    UserRegisterStatus process(IDatabase& db, casisco::UserRegisterInfo& userRegisterInfo );
};

} // registerUser
} // requestHandler
} // server
} // casisco
