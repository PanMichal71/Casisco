#pragma once

namespace casisco
{
namespace server
{
namespace requestHandler
{

class IHandler
{
public:
    virtual ~IHandler() = default;

    virtual bool process() = 0;
};

} // requestHandler
} // server
} // casisco
