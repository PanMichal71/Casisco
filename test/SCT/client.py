from __future__ import print_function

import grpc

from casisco_grpc import casisco_pb2_grpc, casisco_pb2
# import casisco_grpc.

class ClientStub:
    def make_message(self):
        yield casisco_pb2.ProjectBinaryData(
            binaryFile = "987654321",
            data = "123456789"
        )

        yield casisco_pb2.ProjectBinaryData(
            binaryFile = "9876543210",
            data = "0123456789"
        )

    def test_send_data_and_binary_file(self, srv):
        result = srv.sendData(self.make_message())


    def run(self):
        channel = grpc.insecure_channel('localhost:50051')
        stub = casisco_pb2_grpc.CasiscoStub(channel)

        response = stub.registerUser(casisco_pb2.UserRegisterInfo(
            name="test", password="password", email="test@mail.com"))
        print("Greeter client received: {}".format(response.status))

        response = stub.loginUser(casisco_pb2.UserLoginInfo(
            name="test", password="password"))
        print("Greeter client received: {}".format(response.status))

        self.test_send_data_and_binary_file(stub)

ClientStub().run()