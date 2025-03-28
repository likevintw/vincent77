
import unittest
import platformsdk
import os
import logging


logging.basicConfig(
    level=logging.DEBUG,
    format='%(asctime)s - %(levelname)s - %(message)s',
    handlers=[
        logging.StreamHandler()
    ]
)


class TestHandler(unittest.TestCase):
    def test_get_board_information(self):
        handler = platformsdk.PlatformSDK()
        print("")
        for i in handler.board_information.keys():
            print(i, "\t", handler.board_information[i])

    def test_get_board_value_data(self):
        handler = platformsdk.PlatformSDK()
        status = handler.get_board_value_data(
            handler.board_information_value["EAPI_ID_HWMON_TEMP_CPU"])
        print(status)

    def test_initial_EApiLibrary(self):
        handler = platformsdk.PlatformSDK()
        status = handler.initial_EApiLibrary()

    def test_check_table(self):
        handler = platformsdk.PlatformSDK()
        print("")
        for i in handler.board_information_value.keys():
            print(i, handler.board_information_value[i])
        for i in handler.board_information_string.keys():
            print(i, handler.board_information_string[i])

    def test_get_available_memory(self):
        handler = platformsdk.PlatformSDK()
        print("")
        print(handler.get_available_memory())

    def test_get_disk_information(self):
        handler = platformsdk.PlatformSDK()
        print("")
        disk_info_obj = handler.get_disk_information()

        if disk_info_obj is None:
            print("No disk information available.")
            return

        print(f"Total disk count: {disk_info_obj.disk_count}")

        # 輸出每個磁碟分區的資料
        for idx, part_info in enumerate(disk_info_obj.disk_part_info):
            print(f"Partition {idx + 1}:")
            print(f"  Partition ID: {part_info.partition_id}")
            print(f"  Partition Size: {part_info.partition_size} MB")
            print(f"  Partition Name: {part_info.partition_name}")

    @unittest.skip("source error")
    def test_get_etp_device_data(self):
        handler = platformsdk.PlatformSDK()
        result = handler.get_etp_device_data()
        print(result)

    def test_get_etp_user_data(self):
        handler = platformsdk.PlatformSDK()
        result = handler.get_etp_user_data()
        print(result)

    def test_get_led_id_list(self):
        handler = platformsdk.PlatformSDK()
        print(handler.get_led_id_list())

    def test_get_led_status(self):
        handler = platformsdk.PlatformSDK()
        print(handler.get_led_status(0))

    def test_set_led_status(self):
        handler = platformsdk.PlatformSDK()
        print(handler.set_led_status(0))

    def test_get_gpio_count(self):
        handler = platformsdk.PlatformSDK()
        print(handler.get_gpio_count())

    def test_get_gpio_level(self):
        handler = platformsdk.PlatformSDK()
        print(handler.get_gpio_level(0))

    def test_get_gpio_direction(self):
        handler = platformsdk.PlatformSDK()
        print(handler.get_gpio_direction(0))

    def test_get_gpio_capability(self):
        handler = platformsdk.PlatformSDK()
        print(handler.get_gpio_capability(0))

    def test_set_gpio_direction(self):
        handler = platformsdk.PlatformSDK()
        id_number = 0
        direction = 0
        print(handler.set_gpio_direction(id_number, direction))

    def test_set_gpio_level(self):
        handler = platformsdk.PlatformSDK()
        id_number = 0
        level = 0
        print(handler.set_gpio_level(id_number, level))

    def test_get_watchdog_capaility(self):
        handler = platformsdk.PlatformSDK()
        result = handler.get_watchdog_capability()
        max_delay_in_milliseconds = result[0]
        max_event_timeout_in_milliseconds = result[1]
        max_reset_timeout_in_milliseconds = result[2]
        print()
        print(max_delay_in_milliseconds)
        print(max_event_timeout_in_milliseconds)
        print(max_reset_timeout_in_milliseconds)

    @unittest.skip("no source")
    def test_get_storage_capability(self):
        handler = platformsdk.PlatformSDK()
        result = handler.get_storage_capability()
        print(result)


if __name__ == '__main__':
    unittest.main()
