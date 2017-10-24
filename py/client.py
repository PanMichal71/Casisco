from __future__ import print_function

import grpc

import casisco_pb2_grpc
import casisco_pb2


def run():
  channel = grpc.insecure_channel('localhost:50051')
  stub = casisco_pb2_grpc.CasiscoStub(channel)
  response = stub.registerUser(casisco_pb2.UserRegisterInfo(name="dupa", password="dupa_password", email="dupa@mail.com"))
  print("Greeter client received: {}".format(response.status))


if __name__ == '__main__':
  run()
