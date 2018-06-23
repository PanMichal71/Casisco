#include "Processor.hpp"
#include "server/IDatabase.hpp"
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
} // requestHandler
} // server
} // casisco
