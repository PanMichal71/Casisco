import client
import signal, os
import subprocess

def run_server():
    process = subprocess.Popen(
        "./build/src/server/server_cli.out \"127.0.0.1: 50051\"", stdout=subprocess.PIPE, stderr=subprocess.PIPE,
        shell=True, preexec_fn=os.setsid
    )
    return process

if __name__ == '__main__':
    process = run_server()
    client.ClientStub().run()

    os.killpg(process.pid, signal.SIGTERM)
