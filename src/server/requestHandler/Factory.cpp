#include "Factory.hpp"
#include "LoginUser.hpp"
#include "registerUser/Handler.hpp"

#include "server/Context.hpp"

namespace casisco
{
namespace server
{
namespace requestHandler
{

IHandler* Factory::getLoginUser(const Context& ct, IDatabase &db)
{
    return new LoginUser(ct.service, ct.completionQueue, db);
}

IHandler* Factory::getRegisterUser(const Context &ct, IDatabase &db)
{
    return new registerUser::Handler(ct.service, ct.completionQueue, db);
}

} // requestHandler
} // server
} // casisco
