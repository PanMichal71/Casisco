#pragma once
#include <memory>
#include "server/Context.hpp"

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
    IHandler* getLoginUser(const Context& ct, const IDatabase& db);
    IHandler* getRegisterUser(const Context& ct, const IDatabase& db);
};


} // requestHandler
} // server
} // casisco
