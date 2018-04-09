#include "Factory.hpp"
#include "loginUser/Handler.hpp"
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
    return new loginUser::Handler(ct.service, ct.completionQueue, db);
}

IHandler* Factory::getRegisterUser(const Context &ct, IDatabase &db)
{
    return new registerUser::Handler(ct.service, ct.completionQueue, db);
}

} // requestHandler
} // server
} // casisco
