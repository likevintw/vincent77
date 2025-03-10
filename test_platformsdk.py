
import unittest
import platformsdk
import os
import logging

logging.basicConfig(
    level=print,  # 设置日志级别（ DEBUG, INFO, WARNING, ERROR, CRITICAL）
    format='%(asctime)s - %(levelname)s - %(message)s',  # 设置日志输出格式
    handlers=[
        logging.StreamHandler()  # 输出到控制台
    ]
)


class TestHandler(unittest.TestCase):
    def test_get_board_information(self):
        handler = platformsdk.PlatformSDK()
        print("")
        for i in handler.board_information.keys():
            print(i,"\t",handler.board_information[i])

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
        print("")
        for i in handler.board_information_value.keys():
            print(i,handler.board_information_value[i])
        for i in handler.board_information_string.keys():
            print(i,handler.board_information_string[i])

    def test_get_available_memory(self):
        handler = platformsdk.PlatformSDK()
        print("")
        print(handler.get_available_memory)
    
if __name__ == '__main__':
    unittest.main()
