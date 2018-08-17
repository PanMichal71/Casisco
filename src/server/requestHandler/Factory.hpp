#pragma once
#include <memory>

namespace casisco
{
namespace server
{

namespace db
{
class IUsersDatabase;
} // namespace db

struct Context;

namespace requestHandler
{
class IHandler;

class Factory
{
public:
    IHandler* getLoginUser(const Context& ct, db::IUsersDatabase &db);
    IHandler* getRegisterUser(const Context& ct, db::IUsersDatabase &db);
};


} // requestHandler
} // server
} // casisco
