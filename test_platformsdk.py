
import unittest
import platformsdk
import os
import logging

logging.basicConfig(
    level=logging.DEBUG,  # 设置日志级别（ DEBUG, INFO, WARNING, ERROR, CRITICAL）
    format='%(asctime)s - %(levelname)s - %(message)s',  # 设置日志输出格式
    handlers=[
        logging.StreamHandler()  # 输出到控制台
    ]
)


class TestHandler(unittest.TestCase):
    def test_get_board_string_data(self):
        handler = platformsdk.PlatformSDK()
        print()
        for i in range(10):
            status = handler.get_board_string_data(i)
            print(i, status)
        for i in range(16, 19):
            status = handler.get_board_string_data(i)
            print(i, status)
        for i in range(257, 260):
            status = handler.get_board_string_data(i)
            print(i, status)
        for i in range(513, 526):
            status = handler.get_board_string_data(i)
            print(i, status)
        for i in range(327680, 327690):
            status = handler.get_board_string_data(i)
            print(i, status)
        for i in range(330240, 330265):
            status = handler.get_board_string_data(i)
            print(i, status)

    def test_get_board_value_data(self):
        handler = platformsdk.PlatformSDK()
        status = handler.get_board_value_data(handler.EAPI_ID_HWMON_TEMP_CPU)
        print(status)

    def test_initial_EApiLibrary(self):
        handler = platformsdk.PlatformSDK()
        status = handler.initial_EApiLibrary()
        print(status)
        
    def test_check_table(self):
        handler = platformsdk.PlatformSDK()
        print()
        for i in handler.board_information_value.keys():
            print(i,handler.board_information_value[i])
        for i in handler.board_information_string.keys():
            print(i,handler.board_information_string[i])


if __name__ == '__main__':
    unittest.main()
