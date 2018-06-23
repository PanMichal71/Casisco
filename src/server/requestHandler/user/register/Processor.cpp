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
namespace register_
{

Processor::Processor()
    : log_("requestHandler::register_::Processor")
{}

UserRegisterStatus Processor::process(IDatabase &db, casisco::UserRegisterInfo &userRegisterInfo)    
{
    const UserInfo ui {
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
        case IDatabase::Result::ok:
            status = StatusType::UserRegisterStatus_Status_ok;
            break;
        case IDatabase::Result::wrongEmail:
            status = StatusType::UserRegisterStatus_Status_emailTaken;
            break;
        case IDatabase::Result::loginTaken:
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
} // requestHandler
} // server
} // casisco
