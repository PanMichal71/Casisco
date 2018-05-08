import pytest
import tempfile
import os

import ServerStub

import grpc
from casisco_grpc import casisco_pb2_grpc


@pytest.yield_fixture()
def cleandir():
    newpath = tempfile.mkdtemp()
    print ("tmppath: {}".format(newpath))
    os.chdir(newpath)
    stub = ServerStub.ServerStub()
    stub.run()
        
    yield 

    stub.cleanup()

@pytest.yield_fixture()
def srv(cleandir):
    return casisco_pb2_grpc.CasiscoStub(
        grpc.insecure_channel('localhost:50051'))




