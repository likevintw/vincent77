#!/usr/bin/env python3.5

from subprocess import Popen, PIPE
import select
import fcntl
import os
import time
import sys 
import ctypes

class Server(object):
  def __init__(self, args, server_env = None):
    if server_env:
      self.process = Popen(args, stdin=PIPE, stdout=PIPE, stderr=PIPE, env=server_env)
    else:
      self.process = Popen(args, stdin=PIPE, stdout=PIPE, stderr=PIPE)
    flags = fcntl.fcntl(self.process.stdout, fcntl.F_GETFL)
    fcntl.fcntl(self.process.stdout, fcntl.F_SETFL, flags | os.O_NONBLOCK)

  def send(self, data, tail='\n'):
    self.process.stdin.write(data + tail.encode())
    self.process.stdin.flush()

  def recv(self, t=.1, stderr=0):
    r = ''
    pr = self.process.stdout
    if stderr:
      pr = self.process.stdout
    while True:
      if not select.select([pr], [], [], 0)[0]:
        time.sleep(t)
        continue
      r = pr.read()
      return r.rstrip()
    return r.rstrip()

print("Usage: %s \"[COM_PATH]\"" %(sys.argv[0]))
print("  [COM_PATH] - /dev/ttyXR* \n")
serialPort = sys.argv[1]

if __name__ == "__main__":
  ServerArgs = ['./testdl_ipsae', serialPort]
  server = Server(ServerArgs)
  time.sleep(1)
  while (input("\nEnter 'q' to quit:") != 'q'):
    x='\n'
    server.send(x.encode())
    recvMsg = server.recv()
    recvInfo = recvMsg.decode().split("\n")
    for i in range(len(recvInfo)):
      print(recvInfo[i])
    time.sleep(1)
  print("Bye ~")

