#include "Factory.hpp"
#include "user/login/Handler.hpp"
#include "user/register/Handler.hpp"
#include "project/createProject/Handler.hpp"
#include "project/sendData/Handler.hpp"

#include "server/Context.hpp"

namespace casisco
{
namespace server
{
namespace requestHandler
{

IHandler* Factory::getLoginUser(const Context& ct, db::IUsersDatabase &db)
{
    return new user::login::Handler(ct.service, ct.completionQueue, db);
}

IHandler* Factory::getRegisterUser(const Context &ct, db::IUsersDatabase &db)
{
    return new user::register_::Handler(ct.service, ct.completionQueue, db);
}

IHandler *Factory::getSendData(const Context &ct)
{
    return new requestHandler::sendData::Handler(ct.service, ct.completionQueue);
}

} // requestHandler
} // server
} // casisco
