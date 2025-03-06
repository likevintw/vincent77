#!/usr/bin/env python3.5

from subprocess import Popen, PIPE
import select
import fcntl
import os
import time
import sys 
import ctypes
import threading

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

nameUPS = 'UPS_FIFO'

def pipeListener():
  if os.access(nameUPS, os.F_OK) == False:
    os.mkfifo(nameUPS)
  readFd = os.open(nameUPS, os.O_RDONLY)
  loopFlag = True
  while loopFlag:
    time.sleep(1)
    upsMsg = os.read(readFd, 512)
    upsInfo = upsMsg.decode().split("\n")
    for i in range(len(upsInfo)):
      print(upsInfo[i])
  os.close(readFd)

print("Usage: %s \"[COM_PATH]\"" %(sys.argv[0]))
print("  [COM_PATH] - /dev/ttyXR* \n")
serialPort = sys.argv[1]

thread1 = threading.Thread(target=pipeListener, args=())

if __name__ == "__main__":
  thread1.setDaemon(True)
  thread1.start()
  ServerArgs = ['./testdl_ipsae', serialPort]
  server = Server(ServerArgs)
  time.sleep(1)
  while (input("\nEnter 'q' to quit:") != 'q'):
    time.sleep(1)
    x=''
    server.send(x.encode())
  print("Bye ~")

