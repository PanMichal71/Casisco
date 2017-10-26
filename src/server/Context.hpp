#pragma once
#include <grpc++/grpc++.h>
#include "casisco.grpc.pb.h"
namespace casisco
{
namespace server
{

struct Context
{
    Casisco::AsyncService* service;
    grpc::ServerCompletionQueue* completionQueue;
};

} // server
} // casisco

