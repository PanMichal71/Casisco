#pragma once
#include "common/Logger.hpp"

namespace casisco
{
class UserRegisterInfo;
class UserRegisterStatus;

namespace server
{
namespace db
{
class IUsersDatabase;
} // namespace db

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
    UserRegisterStatus process(db::IUsersDatabase& db, casisco::UserRegisterInfo& userRegisterInfo );

private:
    common::Logger log_;
};

} // register_
} // user
} // requestHandler
} // server
} // casisco
