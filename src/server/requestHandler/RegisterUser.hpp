#pragma once
#include "IHandler.hpp"

namespace casisco
{
namespace server
{
namespace requestHandler
{

class ReqisterUser : public IHandler
{

    virtual bool process() override;

};

} // requestHandler
} // server
} // casisco
