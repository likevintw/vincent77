
import unittest
import device
import os


class TestHandler(unittest.TestCase):
    def test_cpu_temperature_in_celsius(self):
        handler = device.Device()
        print(handler.cpu_temperature_in_celsius)


if __name__ == '__main__':
    unittest.main()
