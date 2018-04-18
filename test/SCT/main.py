import client
import signal, os
import subprocess
import sys
import socket
import time

def servertest(host, port):
    args = socket.getaddrinfo(host, port, socket.AF_INET, socket.SOCK_STREAM)
    for family, socktype, proto, canonname, sockaddr in args:
        s = socket.socket(family, socktype, proto)
        try:
            s.connect(sockaddr)
        except socket.error:
            return False
        else:
            s.close()
            return True

def wait_for_server(host, port):
    start = time.time()
    max_time = 10

    while(True):
        if(servertest(host, port) == True):
            print("Server is up and running!")
            return True

        current = time.time()
        if(current - start >= max_time):
            print ("Timeout on waiting for server!")
            return False
        
        time.sleep(0.1)

def run_server(host, port):
    addr = host+":{}".format(port)
    print addr
    process = subprocess.Popen(
        "./build/src/server/server_cli.out \"{}\"".format(addr), stdout=subprocess.PIPE, stderr=subprocess.PIPE,
        shell=True, preexec_fn=os.setsid
    )
    return process

if __name__ == '__main__':
    host = "127.0.0.1"
    port = 50051

    process = run_server(host, port)
    if(wait_for_server(host, port) == True):
        client.ClientStub().run()
    os.killpg(process.pid, signal.SIGTERM)
