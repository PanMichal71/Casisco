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

UserRegisterStatus Processor::process(IDatabase &db, casisco::UserRegisterInfo &userRegisterInfo)
{
    const UserInfo ui {
        userRegisterInfo.email(),
        userRegisterInfo.name(),
        userRegisterInfo.password()
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
        case IDatabase::Result::wrongLogin:
            status = StatusType::UserRegisterStatus_Status_nameTaken;
            break;
        default:
            std::cerr << __func__ << " unsupported database result" << std::endl;
            status = StatusType::UserRegisterStatus_Status_error;
            break;
        }
        return status;
    }();

    UserRegisterStatus result;
    result.set_status(status);
    return result;
}

} // loginUser
} // requestHandler
} // server
} // casisco
