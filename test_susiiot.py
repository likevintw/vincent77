
import unittest
import susiiot
import os
import platform
import logging

logging.basicConfig(
    level=logging.INFO,  # 设置日志级别（ DEBUG, INFO, WARNING, ERROR, CRITICAL）
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

    def test_get_gpio_list(self):
        handler = susiiot.SusiIot()
        self.assertNotEqual(len(handler.gpio_list), 0)
        logging.debug(handler.gpio_list)

    def test_get_memory_list(self):
        handler = susiiot.SusiIot()
        self.assertNotEqual(len(handler.memory_list), 0)
        logging.debug(handler.memory_list)

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
        uris = handler.susi_information.keys()
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

    def test_get_gpio_direction(self):
        handler = susiiot.SusiIot()
        gpio_count = handler.get_gpio_counter()
        for gpio in range(gpio_count):
            result = handler.get_gpio_direction(gpio)
            logging.debug(result)
            self.assertNotEqual(result, None)

    def test_get_gpio_level(self):
        handler = susiiot.SusiIot()
        gpio_count = handler.get_gpio_counter()
        for gpio in range(gpio_count):
            result = handler.get_gpio_level(gpio)
            logging.debug(result)
            self.assertNotEqual(result, None)

    def test_get_memory_count(self):
        handler = susiiot.SusiIot()
        result = handler.get_memory_count()
        logging.debug(result)
        self.assertNotEqual(result, 0)

    def test_get_memory_type(self):
        handler = susiiot.SusiIot()
        memory_count = handler.get_memory_count()
        for memeory_number in range(memory_count):
            result = handler.get_memory_type(memeory_number)
            logging.debug(result)
            self.assertNotEqual(result, None)

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

    def test_get_memory_voltage(self):
        handler = susiiot.SusiIot()
        results = handler.get_memory_voltage()
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
        result = handler.get_memory_temperature()
        logging.debug(result)
        self.assertNotEqual(result, None)

    def test_get_disk_total_disk_space(self):
        handler = susiiot.SusiIot()
        results = handler.get_disk_total_disk_space()
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


class TestCasesUNO1372G(unittest.TestCase):
    def test_boot_up_times(self):
        handler = susiiot.SusiIot()
        self.assertNotEqual(handler.boot_up_times, None)

    def test_running_time_in_hours(self):
        handler = susiiot.SusiIot()
        self.assertNotEqual(handler.running_time_in_hours, None)

    def test_board_name(self):
        handler = susiiot.SusiIot()
        self.assertNotEqual(handler.board_name, None)

    def test_bios_revision(self):
        handler = susiiot.SusiIot()
        self.assertNotEqual(handler.bios_revision, None)

    def test_firmware_name(self):
        handler = susiiot.SusiIot()
        self.assertNotEqual(handler.firmware_name, None)

    def test_driver_version(self):
        handler = susiiot.SusiIot()
        self.assertNotEqual(handler.driver_version, None)

    def test_firmware_version(self):
        handler = susiiot.SusiIot()
        self.assertNotEqual(handler.firmware_version, None)

    @unittest.skip("same id bug")
    def test_disk_total_disk_space(self):
        handler = susiiot.SusiIot()
        self.assertNotEqual(handler.disk_total_disk_space, None)

    def test_disk_free_disk_space(self):
        handler = susiiot.SusiIot()
        self.assertNotEqual(handler.disk_free_disk_space, None)

    def test_voltage_vcore(self):
        handler = susiiot.SusiIot()
        self.assertNotEqual(handler.voltage_vcore, None)

    def test_voltage_5v_standby(self):
        handler = susiiot.SusiIot()
        self.assertNotEqual(handler.voltage_5v_standby, None)

    def test_voltage_mos_battery(self):
        handler = susiiot.SusiIot()
        self.assertNotEqual(handler.voltage_mos_battery, None)

    def test_dc_power(self):
        handler = susiiot.SusiIot()
        self.assertNotEqual(handler.dc_power, None)

    def test_cpu_temperature_in_celsius(self):
        handler = susiiot.SusiIot()
        self.assertNotEqual(handler.cpu_temperature_in_celsius, None)

    def test_system_temperature_in_celsius(self):
        handler = susiiot.SusiIot()
        self.assertNotEqual(handler.system_temperature_in_celsius, None)


class TestCasesModule(unittest.TestCase):
    def test_boot_up_times(self):
        handler = susiiot.SusiIot()
        self.assertNotEqual(handler.boot_up_times, None)

    def test_running_time_in_hours(self):
        handler = susiiot.SusiIot()
        self.assertNotEqual(handler.running_time_in_hours, None)

    def test_board_name(self):
        handler = susiiot.SusiIot()
        self.assertNotEqual(handler.board_name, None)

    def test_bios_revision(self):
        handler = susiiot.SusiIot()
        self.assertNotEqual(handler.bios_revision, None)

    def test_firmware_name(self):
        handler = susiiot.SusiIot()
        self.assertNotEqual(handler.firmware_name, None)

    def test_driver_version(self):
        handler = susiiot.SusiIot()
        self.assertNotEqual(handler.driver_version, None)

    def test_firmware_version(self):
        handler = susiiot.SusiIot()
        self.assertNotEqual(handler.firmware_version, None)

    @unittest.skip("same id bug")
    def test_disk_total_disk_space(self):
        handler = susiiot.SusiIot()
        self.assertNotEqual(handler.disk_total_disk_space, None)

    def test_disk_free_disk_space(self):
        handler = susiiot.SusiIot()
        self.assertNotEqual(handler.disk_free_disk_space, None)

    def test_voltage_vcore(self):
        handler = susiiot.SusiIot()
        self.assertNotEqual(handler.voltage_vcore, None)

    def test_voltage_vcore(self):
        handler = susiiot.SusiIot()
        self.assertNotEqual(handler.voltage_vcore, None)

    def test_voltage_3p3v_standby(self):
        handler = susiiot.SusiIot()
        self.assertNotEqual(handler.voltage_3p3v_standby, None)

    def test_voltage_5v(self):
        handler = susiiot.SusiIot()
        self.assertNotEqual(handler.voltage_5v, None)

    def test_voltage_12v(self):
        handler = susiiot.SusiIot()
        self.assertNotEqual(handler.voltage_12v, None)

    def test_voltage_5v_standby(self):
        handler = susiiot.SusiIot()
        self.assertNotEqual(handler.voltage_5v_standby, None)

    def test_voltage_cmos_battery(self):
        handler = susiiot.SusiIot()
        self.assertNotEqual(handler.voltage_cmos_battery, None)

    def test_dc_power(self):
        handler = susiiot.SusiIot()
        self.assertNotEqual(handler.dc_power, None)

    def test_cpu_temperature_in_celsius(self):
        handler = susiiot.SusiIot()
        self.assertNotEqual(handler.cpu_temperature_in_celsius, None)

    def test_system_temperature_in_celsius(self):
        handler = susiiot.SusiIot()
        self.assertNotEqual(handler.system_temperature_in_celsius, None)

    def test_cpu_fan_speed(self):
        handler = susiiot.SusiIot()
        self.assertNotEqual(handler.cpu_fan_speed, None)

    def test_system_fan_speed(self):
        handler = susiiot.SusiIot()
        self.assertNotEqual(handler.system_fan_speed, None)

    def test_susiiot_version(self):
        handler = susiiot.SusiIot()
        self.assertNotEqual(handler.susiiot_version, None)

    @unittest.skip("api get null")
    def test_backlight_frequency(self):
        handler = susiiot.SusiIot()
        self.assertNotEqual(handler.backlight_frequency, None)

    @unittest.skip("api get null")
    def test_backlight_polarity(self):
        handler = susiiot.SusiIot()
        self.assertNotEqual(handler.backlight_polarity, None)

    @unittest.skip("api get null")
    def test_backlight_backlight(self):
        handler = susiiot.SusiIot()
        self.assertNotEqual(handler.backlight_backlight, None)

    @unittest.skip("api get null")
    def test_backlight_brightness(self):
        handler = susiiot.SusiIot()
        self.assertNotEqual(handler.backlight_brightness, None)


if __name__ == '__main__':
    unittest.main()
