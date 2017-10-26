#include "Factory.hpp"
#include "LoginUser.hpp"
#include "RegisterUser.hpp"

#include "server/Context.hpp"

namespace casisco
{
namespace server
{
namespace requestHandler
{

std::unique_ptr<IHandler> Factory::getLoginUser(const Context& ct, const IDatabase &db)
{
    return new LoginUser(ct.service, ct.completionQueue, db);
}

IHandler* Factory::getRegisterUser(const Context &ct, const IDatabase &db)
{
    return new RegisterUser(ct.service, ct.completionQueue, db);
}

} // requestHandler
} // server
} // casisco
