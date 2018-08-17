#include "Processor.hpp"
#include "server/database/IUsersDatabase.hpp"
#include "casisco.grpc.pb.h"
namespace casisco
{
namespace server
{
class IDatabase;

namespace requestHandler
{
namespace user
{
namespace register_
{

Processor::Processor()
    : log_("registerUser::Processor")
{}

UserRegisterStatus Processor::process(db::IUsersDatabase &db, casisco::UserRegisterInfo &userRegisterInfo)
{
    const db::UserInfo ui {
        userRegisterInfo.name(),
        userRegisterInfo.password(),
        userRegisterInfo.email()
    };

    const auto status = [&]() -> UserRegisterStatus_Status
    {
        typedef UserRegisterStatus::Status StatusType;
        UserRegisterStatus_Status status;
        switch(db.registerUser(ui) )
        {
        case db::EResult::ok:
            status = StatusType::UserRegisterStatus_Status_ok;
            break;
        case db::EResult::error:
            status = StatusType::UserRegisterStatus_Status_emailTaken;
            break;
        case db::EResult::alreadyExists:
            status = StatusType::UserRegisterStatus_Status_nameTaken;
            break;
        default:
            log_ << ERROR << __func__ << " unsupported database result";
            status = StatusType::UserRegisterStatus_Status_error;
            break;
        }
        return status;
    }();

    UserRegisterStatus result;
    result.set_status(status);
    return result;
}

} // register_
} // user
} // requestHandler
} // server
} // casisco
