#include "Processor.hpp"
#include "server/requestHandler/user/IDatabase.hpp"
#include "casisco.grpc.pb.h"

#include "unordered_map"
#include <string>

namespace casisco
{
namespace server
{
class IDatabase;

namespace requestHandler
{
namespace user
{
namespace login
{

Processor::Processor()
    : log_("requestHandler::login::Processor")
{

}

UserLoginStatus Processor::process(IDatabase &db, UserLoginInfo &request)
{
    const UserInfo ui {
        request.name(),
        request.password()
    };

    const auto status = [&]() -> UserLoginStatus_Status
    {
        typedef UserLoginStatus::Status StatusType;
        UserLoginStatus_Status status;
        switch(db.loginUser(ui) )
        {
        case IDatabase::Result::ok:
            status = StatusType::UserLoginStatus_Status_ok;
            break;
        default:
            status = StatusType::UserLoginStatus_Status_error;
            break;
        }
        return status;
    }();

    UserLoginStatus result;
    result.set_status(status);
    return result;
}

} // login
} // user
} // requestHandler
} // server
} // casisco
