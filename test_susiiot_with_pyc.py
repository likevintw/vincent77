
import unittest
import os
import platform
import logging
import time
import datetime
import importlib.util
import shutil
import compileall


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
print(f"test_susiiot_with_pyc.py")
try:
    print(f"container: {os.popen('cat /etc/hostname').read().strip()}")
except:
    print(f"container: None")
print()


pyc_path = "susiiot.cpython-38.pyc"
spec = importlib.util.spec_from_file_location("susiiot", pyc_path)
SUSIIOT = importlib.util.module_from_spec(spec)
spec.loader.exec_module(SUSIIOT)


class TestCases(unittest.TestCase):

    def test_get_susi_information_string(self):
        handler = SUSIIOT.SusiIot()
        print(handler.get_susi_information_string())

    def test_susi_information(self):
        handler = SUSIIOT.SusiIot()
        print()
        print("test_susi_information")
        print(handler.susi_iot_information)

    def test_susi_id_name_table(self):
        handler = SUSIIOT.SusiIot()
        print()
        print("test_susi_id_name_table")
        for name in handler.susi_id_name_table.keys():
            print(name, handler.susi_id_name_table[name])

    def test_get_data_by_id(self):
        handler = SUSIIOT.SusiIot()
        print()
        print("test_get_data_by_id")
        for item_name in handler.susi_id_name_table.keys():
            result = handler.get_data_by_id(
                handler.susi_id_name_table[item_name])
            print(f"{item_name} result is {result}")
            print()


if __name__ == '__main__':
    unittest.main()
