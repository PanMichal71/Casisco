import pytest
import tempfile
import os
import shutil

import server_process
import socket
import time
from contextlib import closing

import grpc
from casisco_grpc import casisco_pb2_grpc

def find_free_port():
    with closing(socket.socket(socket.AF_INET, socket.SOCK_STREAM)) as s:
        s.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
        s.bind(('', 0))
        return s.getsockname()[1]
        
@pytest.hookimpl(tryfirst=True, hookwrapper=True)
def pytest_runtest_makereport(item, call):
    outcome = yield
    rep = outcome.get_result()
    setattr(item, "rep_" + rep.when, rep)

def zip_database(output_dir, tmp_dir_path, db_path):
    db_archive_path = os.path.join(
        output_dir, db_path)

    tmp_dir_db_path = os.path.join(tmp_dir_path, db_path)
    if not os.path.exists(tmp_dir_db_path):
        print ("{} doesn't exist".format(tmp_dir_db_path))
        return

    print("Zipping {}".format(tmp_dir_db_path))
    shutil.make_archive(db_archive_path, 'zip', tmp_dir_db_path)

@pytest.fixture()
def cleandir(request):
    test_dir = os.getcwd()
    test_output_dir = os.path.abspath(os.path.join(test_dir, "../../failed_tests_output"))

    tmp_path = tempfile.mkdtemp()
    stub = server_process.server_process()
    os.chdir(tmp_path)
    should_save = 0
    def fin():
        if should_save == 1:
            testcase_output_dir = os.path.join(test_output_dir, request.node.name)
            if os.path.exists(testcase_output_dir):
                shutil.rmtree(testcase_output_dir)
            os.makedirs(testcase_output_dir)
            stub.save_stdout("{}/server.log".format(testcase_output_dir))
            zip_database(testcase_output_dir, tmp_path, "databases/users")
            zip_database(testcase_output_dir, tmp_path, "databases/emails")

        shutil.rmtree(tmp_path)

    request.addfinalizer(fin)
    host = "127.0.0.1"
    port = find_free_port()
    address = '{}:{}'.format(host, port)
    stub.run(host, port)  
    yield address
    
    if request.node.rep_setup.failed:
        print ("setting up a test failed!", request.node.nodeid)
    elif request.node.rep_setup.passed:
        if request.node.rep_call.failed:
            should_save = 1
            print ("executing test failed", request.node.nodeid)

    stub.cleanup()
    os.chdir(test_dir)

@pytest.yield_fixture()
def srv(cleandir):
    return casisco_pb2_grpc.CasiscoStub(
        grpc.insecure_channel(cleandir))




