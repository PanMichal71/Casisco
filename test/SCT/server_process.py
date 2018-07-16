import client
import signal
import os
import subprocess
import sys
import socket
import time


class server_process:
    def __init__(self):
        self.process = None
        self.port = 0
        self.host = "127.0.0.1"

    def save_stdout(self, path):
        with open(path, 'w+') as file:
            for line in self.process.stdout.readlines():
                file.write("%s\n" % line.strip())
                print("{}".format(line.strip()))

    def cleanup(self):
         if(self.process != None):
            print ("Killing server process: {}".format(self.process.pid))
            os.killpg(self.process.pid, signal.SIGTERM)

    def is_running(self, host, port):
        print ("is running")
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
                print ("closing socket")
                s.close()
                return True

    def wait_for_server(self, host, port):
        print("wait_for_server")
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

            time.sleep(0.5)

    def start_process(self, host, port):
        addr = host+":{}".format(port)
        print addr
        self.process = subprocess.Popen(
            "server_cli.out \"{}\"".format(addr), stdout=subprocess.PIPE, stderr=subprocess.PIPE,
            shell=True, preexec_fn=os.setsid
        )

    def run(self, host, port):
        self.host = host
        self.port = port

        self.start_process(self.host, self.port)
        assert(self.wait_for_server(self.host, self.port) == True)
