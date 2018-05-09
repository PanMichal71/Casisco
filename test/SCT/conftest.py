import pytest
import tempfile
import os
import shutil

import ServerStub

import grpc
from casisco_grpc import casisco_pb2_grpc


@pytest.hookimpl(tryfirst=True, hookwrapper=True)
def pytest_runtest_makereport(item, call):
    outcome = yield
    rep = outcome.get_result()
    setattr(item, "rep_" + rep.when, rep)

@pytest.fixture()
def cleandir(request):
    test_dir = os.getcwd()
    test_output_dir = os.path.abspath(os.path.join(test_dir, "../../failed_tests_output"))

    tmp_path = tempfile.mkdtemp()
    stub = ServerStub.ServerStub()
    os.chdir(tmp_path)
    should_save = 0
    def fin():
        if should_save == 1:
            testcase_output_dir = os.path.join(test_output_dir, request.node.name)
            if  os.path.exists(testcase_output_dir):
                shutil.rmtree(testcase_output_dir)

            os.makedirs(testcase_output_dir)

            path = "{}/server.log".format(testcase_output_dir)
            db_archive_path = os.path.join(testcase_output_dir, "database")
            stub.save_stdout(path)
            shutil.make_archive(db_archive_path, 'zip', os.path.join(tmp_path, "database"))
        shutil.rmtree(tmp_path)

    request.addfinalizer(fin)

    stub.run()  
    yield
    
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
        grpc.insecure_channel('localhost:50051'))




