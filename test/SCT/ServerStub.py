import client
import signal
import os
import subprocess
import sys
import socket
import time


class ServerStub:
    def __init__(self):
        self.process = None

    def __del__(self):
        if(self.process != None):
            os.killpg(self.process.pid, signal.SIGTERM)

    def is_running(self, host, port):
        args = socket.getaddrinfo(
            host, port, socket.AF_INET, socket.SOCK_STREAM)
        for family, socktype, proto, canonname, sockaddr in args:
            canonname
            s = socket.socket(family, socktype, proto)
            try:
                s.connect(sockaddr)
            except socket.error:
                return False
            else:
                s.close()
                return True

    def wait_for_server(self, host, port):
        start = time.time()
        max_time = 10

        while(True):
            if(self.is_running(host, port) == True):
                print("Server is up and running!")
                return True

            current = time.time()
            if(current - start >= max_time):
                print ("Timeout on waiting for server!")
                return False

            time.sleep(0.1)

    def start_process(self, host, port):
        addr = host+":{}".format(port)
        print addr
        self.process = subprocess.Popen(
            "server_cli.out \"{}\"".format(addr), stdout=subprocess.PIPE, stderr=subprocess.PIPE,
            shell=True, preexec_fn=os.setsid
        )

    def run(self):
        host = "127.0.0.1"
        port = 50051

        self.start_process(host, port)
        assert(self.wait_for_server(host, port) == True)
            
