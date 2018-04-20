import pytest
import ServerStub

import grpc
import casisco_pb2_grpc
import casisco_pb2

@pytest.fixture
def server():
    stub = ServerStub.ServerStub()
    stub.run()

    server = casisco_pb2_grpc.CasiscoStub(grpc.insecure_channel('localhost:50051'))
    return server

def test_server_replies_ok_for_register(server):
    expected_status = casisco_pb2.UserRegisterStatus()
    expected_status.status = 0
    result = server.registerUser(casisco_pb2.UserRegisterInfo(
        name="test", password="password", email="test@mail.com"))
    assert(expected_status == result)


# def test_server_replies_nok_for_register_login_taken(server):
#     expected_status = casisco_pb2.UserRegisterStatus()
#     expected_status.status = 1
#     result = server.registerUser(casisco_pb2.UserRegisterInfo(
#         name="test", password="password", email="test@mail.com"))
#     assert(expected_status == result)
