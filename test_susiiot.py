
import unittest
import susiiot
import os
import platform
import logging

logging.basicConfig(
    level=logging.DEBUG,  # 设置日志级别（ DEBUG, INFO, WARNING, ERROR, CRITICAL）
    format='%(asctime)s - %(levelname)s - %(message)s',  # 设置日志输出格式
    handlers=[
        logging.StreamHandler()  # 输出到控制台
    ]
)

class TestHandler(unittest.TestCase):
    def test_get_susi_information(self):
        handler = susiiot.SusiIot()
        results = handler.get_susi_information()
        logging.debug(results)

    def test_get_id_list(self):
        handler = susiiot.SusiIot()
        results = handler.get_id_list()
        logging.debug(results)

    def test_get_data_by_id(self):
        handler = susiiot.SusiIot()
        id_list = handler.get_id_list()
        for device_id in id_list:
            logging.debug(handler.get_data_by_id(device_id))

    def test_get_data_by_uri(self):
        handler = susiiot.SusiIot()
        uris=handler.susi_information.keys()
        for uri in uris:
            result = handler.get_data_by_uri(uri)
            logging.debug(result)

    def test_check_root_authorization(self):
        handler = susiiot.SusiIot()
        results = handler.check_root_authorization()
        logging.debug(results)

    def test_get_log_path(self):
        handler = susiiot.SusiIot()
        results = handler.get_log_path()
        logging.debug(results)

    def test_get_json_format_data(self):
        handler = susiiot.SusiIot()
        results = handler.get_json_format_data(0)
        self.assertEqual(results.type, 3)
        results = handler.get_json_format_data(0.0)
        self.assertEqual(results.type, 4)
        results = handler.get_json_format_data("")
        logging.debug(results.type)

    def test_get_id_dictionary(self):
        handler = susiiot.SusiIot()
        results = handler.get_id_dictionary()
        for key in results.keys():
            logging.debug(key)

    def test_set_gpio_00(self):
        handler = susiiot.SusiIot()
        if 17039873 in handler.id_list:
            result = handler.set_value(17039873, 0)
            result = handler.get_data_by_id(17039873)
            logging.debug(result)
            result = handler.set_value(17039873, 1)
            result = handler.get_data_by_id(17039873)
            logging.debug(result)

    def test_get_id_dictionary(self):
        handler = susiiot.SusiIot()
        results = handler.get_id_dictionary()
        for key in results.keys():
            logging.debug(key)



    def test_get_boot_up_times(self):
        handler = susiiot.SusiIot()
        results = handler.get_boot_up_times()
        self.assertNotEqual(results, None)
    def test_get_running_time_in_hours(self):
        handler = susiiot.SusiIot()
        results = handler.get_running_time_in_hours()
        self.assertNotEqual(results, None)
    def test_get_board_name(self):
        handler = susiiot.SusiIot()
        results = handler.get_board_name()
        self.assertNotEqual(results, None)
    def test_get_bios_revision(self):
        handler = susiiot.SusiIot()
        results = handler.get_bios_revision()
        self.assertNotEqual(results, None)
    def test_get_firmware_name(self):
        handler = susiiot.SusiIot()
        results = handler.get_firmware_name()
        self.assertNotEqual(results, None)
    def test_get_driver_version(self):
        handler = susiiot.SusiIot()
        results = handler.get_driver_version()
        self.assertNotEqual(results, None)
    def test_get_firmware_version(self):
        handler = susiiot.SusiIot()
        results = handler.get_firmware_version()
        self.assertNotEqual(results, None)

    def test_get_vcore(self):
        handler = susiiot.SusiIot()
        results = handler.get_vcore()
        self.assertNotEqual(results, None)
    def test_get_vcore_max(self):
        handler = susiiot.SusiIot()
        results = handler.get_vcore_max()
        self.assertNotEqual(results, None)
    def test_get_vcore_min(self):
        handler = susiiot.SusiIot()
        results = handler.get_vcore_min()
        self.assertNotEqual(results, None)
    def test_get_5v_standby(self):
        handler = susiiot.SusiIot()
        results = handler.get_5v_standby()
        self.assertNotEqual(results, None)
    def test_get_5v_standby_max(self):
        handler = susiiot.SusiIot()
        results = handler.get_5v_standby_max()
        self.assertNotEqual(results, None)
    def test_get_5v_standby_min(self):
        handler = susiiot.SusiIot()
        results = handler.get_5v_standby_min()
        self.assertNotEqual(results, None)
    def test_get_cmos_battery(self):
        handler = susiiot.SusiIot()
        results = handler.get_cmos_battery()
        self.assertNotEqual(results, None)
    def test_get_cmos_battery_max(self):
        handler = susiiot.SusiIot()
        results = handler.get_cmos_battery_max()
        self.assertNotEqual(results, None)
    def test_get_cmos_battery_min(self):
        handler = susiiot.SusiIot()
        results = handler.get_cmos_battery_min()
        self.assertNotEqual(results, None)
    def test_get_dc_power(self):
        handler = susiiot.SusiIot()
        results = handler.get_dc_power()
        self.assertNotEqual(results, None)
    def test_get_dc_power_max(self):
        handler = susiiot.SusiIot()
        results = handler.get_dc_power_max()
        self.assertNotEqual(results, None)
    def test_get_dc_power_min(self):
        handler = susiiot.SusiIot()
        results = handler.get_dc_power_min()
        self.assertNotEqual(results, None)
    def test_get_cpu_temperature_in_celsius(self):
        handler = susiiot.SusiIot()
        results = handler.get_cpu_temperature_in_celsius()
        self.assertNotEqual(results, None)
    def test_get_cpu_temperature_max_in_celsius(self):
        handler = susiiot.SusiIot()
        results = handler.get_cpu_temperature_max_in_celsius()
        self.assertNotEqual(results, None)
    def test_get_cpu_temperature_min_in_celsius(self):
        handler = susiiot.SusiIot()
        results = handler.get_cpu_temperature_min_in_celsius()
        self.assertNotEqual(results, None)
    def test_get_system_temperature_in_celsius(self):
        handler = susiiot.SusiIot()
        results = handler.get_system_temperature_in_celsius()
        self.assertNotEqual(results, None)
    def test_get_system_temperature_max_in_celsius(self):
        handler = susiiot.SusiIot()
        results = handler.get_system_temperature_max_in_celsius()
        self.assertNotEqual(results, None)
    def test_get_system_temperature_min_in_celsius(self):
        handler = susiiot.SusiIot()
        results = handler.get_system_temperature_min_in_celsius()
        self.assertNotEqual(results, None)

    def test_get_gpio_counter(self):
        handler = susiiot.SusiIot()
        result = handler.get_gpio_counter()
        self.assertNotEqual(result, None)
        logging.debug(result)

    def test_get_gpio00_direction(self):
        handler = susiiot.SusiIot()
        results = handler.get_gpio00_direction()
        self.assertNotEqual(results, None)
    def test_get_gpio00_level(self):
        handler = susiiot.SusiIot()
        results = handler.get_gpio00_level()
        self.assertNotEqual(results, None)
    def test_get_gpio01_direction(self):
        handler = susiiot.SusiIot()
        results = handler.get_gpio01_direction()
        self.assertNotEqual(results, None)
    def test_get_gpio01_level(self):
        handler = susiiot.SusiIot()
        results = handler.get_gpio01_level()
        self.assertNotEqual(results, None)
    def test_get_gpio02_direction(self):
        handler = susiiot.SusiIot()
        results = handler.get_gpio02_direction()
        self.assertNotEqual(results, None)
    def test_get_gpio02_level(self):
        handler = susiiot.SusiIot()
        results = handler.get_gpio02_level()
        self.assertNotEqual(results, None)
    def test_get_gpio03_direction(self):
        handler = susiiot.SusiIot()
        results = handler.get_gpio03_direction()
        self.assertNotEqual(results, None)
    def test_get_gpio03_level(self):
        handler = susiiot.SusiIot()
        results = handler.get_gpio03_level()
        self.assertNotEqual(results, None)
    def test_get_gpio04_direction(self):
        handler = susiiot.SusiIot()
        results = handler.get_gpio04_direction()
        self.assertNotEqual(results, None)
    def test_get_gpio04_level(self):
        handler = susiiot.SusiIot()
        results = handler.get_gpio04_level()
        self.assertNotEqual(results, None)
    def test_get_gpio05_direction(self):
        handler = susiiot.SusiIot()
        results = handler.get_gpio05_direction()
        self.assertNotEqual(results, None)
    def test_get_gpio05_level(self):
        handler = susiiot.SusiIot()
        results = handler.get_gpio05_level()
        self.assertNotEqual(results, None)
    def test_get_gpio06_direction(self):
        handler = susiiot.SusiIot()
        results = handler.get_gpio06_direction()
        self.assertNotEqual(results, None)
    def test_get_gpio06_level(self):
        handler = susiiot.SusiIot()
        results = handler.get_gpio06_level()
        self.assertNotEqual(results, None)
    def test_get_gpio07_direction(self):
        handler = susiiot.SusiIot()
        results = handler.get_gpio07_direction()
        self.assertNotEqual(results, None)
    def test_get_gpio07_level(self):
        handler = susiiot.SusiIot()
        results = handler.get_gpio07_level()
        self.assertNotEqual(results, None)


    def test_get_memory_type(self):
        handler = susiiot.SusiIot()
        results = handler.get_memory_type()
        self.assertNotEqual(results, None)
    def test_get_module_type(self):
        handler = susiiot.SusiIot()
        results = handler.get_module_type()
        self.assertNotEqual(results, None)
    def test_get_module_size_in_GB(self):
        handler = susiiot.SusiIot()
        results = handler.get_module_size_in_GB()
        self.assertNotEqual(results, None)
    def test_get_memory_speed(self):
        handler = susiiot.SusiIot()
        results = handler.get_memory_speed()
        self.assertNotEqual(results, None)
    def test_get_memory_rank(self):
        handler = susiiot.SusiIot()
        results = handler.get_memory_rank()
        self.assertNotEqual(results, None)
    def test_get_SDRAM_voltage(self):
        handler = susiiot.SusiIot()
        results = handler.get_SDRAM_voltage()
        self.assertNotEqual(results, None)
    def test_get_memory_bank(self):
        handler = susiiot.SusiIot()
        results = handler.get_memory_bank()
        self.assertNotEqual(results, None)
    def test_get_memory_week_year(self):
        handler = susiiot.SusiIot()
        results = handler.get_memory_week_year()
        self.assertNotEqual(results, None)
    def test_get_memory_temperature(self):
        handler = susiiot.SusiIot()
        results = handler.get_memory_temperature()
        self.assertNotEqual(results, None)


    def test_get_disk_total_disk_space(self):
        handler = susiiot.SusiIot()
        results = handler.test_get_disk_total_disk_space()
        self.assertNotEqual(results, None)
    def test_get_disk_free_disk_space(self):
        handler = susiiot.SusiIot()
        results = handler.get_disk_free_disk_space()
        self.assertNotEqual(results, None)
    def test_get_disk_media_recovery_total_disk_space(self):
        handler = susiiot.SusiIot()
        results = handler.get_disk_media_recovery_total_disk_space()
        self.assertNotEqual(results, None)
    def test_get_disk_media_recovery_free_disk_space(self):
        handler = susiiot.SusiIot()
        results = handler.get_disk_media_recovery_free_disk_space()
        self.assertNotEqual(results, None)
    def test_get_disk_free_disk_space(self):
        handler = susiiot.SusiIot()
        results = handler.get_disk_free_disk_space()
        self.assertNotEqual(results, None)
    def test_get_susiiot_version(self):
        handler = susiiot.SusiIot()
        results = handler.get_susiiot_version()
        self.assertNotEqual(results, None)

if __name__ == '__main__':
    unittest.main()
