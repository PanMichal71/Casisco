#pragma once
#include <memory>

namespace casisco
{
namespace server
{
class IDatabase;
struct Context;

namespace requestHandler
{
class IHandler;

class Factory
{
public:
    IHandler* getLoginUser(const Context& ct, IDatabase& db);
    IHandler* getRegisterUser(const Context& ct, IDatabase& db);
};


} // requestHandler
} // server
} // casisco
