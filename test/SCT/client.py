from __future__ import print_function

import grpc

from casisco_grpc import casisco_pb2_grpc, casisco_pb2
# import casisco_grpc.

class ClientStub:
  def run(self):
    channel = grpc.insecure_channel('localhost:50051')
    stub = casisco_pb2_grpc.CasiscoStub(channel)
    
    response = stub.registerUser(casisco_pb2.UserRegisterInfo(
        name="test", password="password", email="test@mail.com"))
    print("Greeter client received: {}".format(response.status))

    response = stub.loginUser(casisco_pb2.UserLoginInfo(
        name="test", password="password"))
    print("Greeter client received: {}".format(response.status))
