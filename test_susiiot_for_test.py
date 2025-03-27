
import unittest
import susiiot
import os
import platform
import logging
import time
import datetime


try:
    os.system("git log --oneline -1")
except:
    pass
formatted_time = datetime.datetime.fromtimestamp(
    time.time()).strftime('%Y-%m-%d %H:%M:%S')
print(f"test time: {formatted_time}")
print(f"OS Name: {platform.system()}")
print(f"OS Version: {platform.system()}")
print(f"architecture: {platform.machine()}")
print()



class TestMotherBoardInterface(unittest.TestCase):
    def test_name(self):
        mother_board = susiiot.SusiIot()
        print(mother_board.name)
    # def test_name_2(self):
    #     mother_board = susiiot.SusiIot()
    #     print(mother_board.name)


if __name__ == '__main__':
    unittest.main()
