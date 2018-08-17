#pragma once
#include "common/Logger.hpp"

namespace casisco
{
class UserLoginInfo;
class UserLoginStatus;

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
namespace login
{

class Processor
{
public:
    explicit Processor();
    UserLoginStatus process(db::IUsersDatabase& db, casisco::UserLoginInfo& request );

private:
    common::Logger log_;
};

} // login
} // user
} // requestHandler
} // server
} // casisco
