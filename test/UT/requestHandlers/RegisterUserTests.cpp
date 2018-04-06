#include "server/requestHandler/RegisterUser.hpp"
#include "mocks/server/IDatabaseMock.hpp"
#include "casisco_mock.grpc.pb.h"
#include <gmock/gmock.h>
#include <gtest/gtest.h>

using ::testing::_;

namespace casisco
{
namespace server
{
namespace requestHandler
{

class MockService : public Casisco::AsyncService
{
public:
    MockService()  = default;
    ~MockService() = default;

    MOCK_METHOD6(RequestregisterUser, void((::grpc::ServerContext* context, ::casisco::UserRegisterInfo* request,
                                            ::grpc::ServerAsyncResponseWriter< ::casisco::UserRegisterStatus>* response,
                                            ::grpc::CompletionQueue* new_call_cq, ::grpc::ServerCompletionQueue* notification_cq, void *tag)));

    MOCK_METHOD6(RequestloginUser, void((::grpc::ServerContext* context, ::casisco::UserLoginInfo* request,
                                         ::grpc::ServerAsyncResponseWriter< ::casisco::UserLoginStatus>* response,
                                         ::grpc::CompletionQueue* new_call_cq, ::grpc::ServerCompletionQueue* notification_cq, void *tag)));
};

struct RegisterUserTests : ::testing::Test
{
    virtual void SetUp () override
    {
        EXPECT_CALL(service_, RequestregisterUser(_, _, _, _, _, _)).Times(1).WillOnce(::testing::SaveArg<1>(&request_));
        sut_ = std::make_shared<RegisterUser>(&service_, nullptr, db_);
    }

    std::shared_ptr<RegisterUser> sut_;
    MockService service_;
    IDatabaseMock db_;
    ::casisco::UserRegisterInfo* request_;
};


TEST_F(RegisterUserTests, Test)
{
    EXPECT_TRUE(true);
}

} // requestHandler
} // server
} // casisco
