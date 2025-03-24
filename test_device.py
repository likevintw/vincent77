
import unittest
import device
import os


class TestHandler(unittest.TestCase):
    def test_os_revision(self):
        handler = device.Device()
        print(handler.os_revision)


if __name__ == '__main__':
    unittest.main()
