import pytest
import ServerStub

import grpc
from casisco_grpc import casisco_pb2_grpc, casisco_pb2

@pytest.mark.usefixtures("srv")
class TestDatabaseInteraction:
    success = 0
    loginTaken = 1
    name = "test"
    password = "testpasswd"
    email = "test@test.com"

    def register_user_and_expect_status(self, srv, name, password, email, status):
        expected_status = casisco_pb2.UserRegisterStatus()
        expected_status.status = status
        result = srv.registerUser(casisco_pb2.UserRegisterInfo(
            name = name, password = password, email = email))
        assert(expected_status == result)

    def login_user_and_expect_status(self, srv, name, password, status):
        expected_login_status = casisco_pb2.UserLoginStatus()
        expected_login_status.status = status
        result = srv.loginUser(casisco_pb2.UserLoginInfo(
            name = name, password = password
        ))

        assert(expected_login_status == result)

    def test_server_replies_ok_for_register(self, srv):
        self.register_user_and_expect_status(
            srv, self.name, self.password, self.email, self.success)

    def test_server_replies_nok_for_register_login_taken(self, srv):
        self.register_user_and_expect_status(
            srv, self.name, self.password, self.email, self.success)
        self.register_user_and_expect_status(
            srv, self.name, self.password, self.email, self.loginTaken)

    def test_should_fail_to_login_unknown_user(self, srv):
        self.login_user_and_expect_status(srv, self.name, self.password, 3)

    def test_successfully_registers_and_login_user(self, srv):
        self.register_user_and_expect_status(
            srv, self.name, self.password, self.email, self.success)
        self.login_user_and_expect_status(
            srv, self.name, self.password, self.success)




