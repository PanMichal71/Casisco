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
namespace user
{
namespace register_
{

class Processor
{
public:
    explicit Processor();
    UserRegisterStatus process(IDatabase& db, casisco::UserRegisterInfo& userRegisterInfo );

private:
    common::Logger log_;
};

} // register_
} // user
} // requestHandler
} // server
} // casisco
