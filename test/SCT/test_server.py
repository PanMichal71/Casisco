import pytest
import ServerStub

import grpc
import casisco_pb2_grpc
import casisco_pb2


@pytest.mark.usefixtures("srv")
class TestDatabaseInteraction:
    def test_server_replies_ok_for_register(self, srv):
        expected_status = casisco_pb2.UserRegisterStatus()
        expected_status.status = 0
        result = srv.registerUser(casisco_pb2.UserRegisterInfo(
            name="test", password="password", email="test@mail.com"))
        assert(expected_status == result)


    def test_server_replies_nok_for_register_login_taken(self, srv):
        expected_status = casisco_pb2.UserRegisterStatus()
        expected_status.status = 0
        result = srv.registerUser(casisco_pb2.UserRegisterInfo(
            name="test", password="password", email="test@mail.com"))
        assert(expected_status == result)

        expected_status.status = 1
        result = srv.registerUser(casisco_pb2.UserRegisterInfo(
            name="test", password="password", email="test@mail.com"))
        assert(expected_status == result)
