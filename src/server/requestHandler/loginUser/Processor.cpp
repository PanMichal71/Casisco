#include "Processor.hpp"
#include "server/IDatabase.hpp"
#include "casisco.grpc.pb.h"
namespace casisco
{
namespace server
{
class IDatabase;

namespace requestHandler
{
namespace loginUser
{

Processor::Processor()
    : log_("server::requestHandler::loginUser::Processor")
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

} // loginUser
} // requestHandler
} // server
} // casisco
