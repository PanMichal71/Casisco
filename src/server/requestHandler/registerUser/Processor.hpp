#pragma once
#include "common/Logger.hpp"

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
    explicit Processor();
    UserRegisterStatus process(IDatabase& db, casisco::UserRegisterInfo& userRegisterInfo );

private:
    common::Logger log_;
};

} // registerUser
} // requestHandler
} // server
} // casisco
