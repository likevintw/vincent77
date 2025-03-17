
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
        print(len(handler.gpio_list), 0)
        logging.debug(handler.gpio_list)

    def test_get_memory_list(self):
        handler = susiiot.SusiIot()
        print(len(handler.memory_list), 0)
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
        print(results)

    def test_get_running_time_in_hours(self):
        handler = susiiot.SusiIot()
        results = handler.get_running_time_in_hours()
        print(results)

    def test_get_board_name(self):
        handler = susiiot.SusiIot()
        results = handler.get_board_name()
        print(results)

    def test_get_bios_revision(self):
        handler = susiiot.SusiIot()
        results = handler.get_bios_revision()
        print(results)

    def test_get_firmware_name(self):
        handler = susiiot.SusiIot()
        results = handler.get_firmware_name()
        print(results)

    def test_get_driver_version(self):
        handler = susiiot.SusiIot()
        results = handler.get_driver_version()
        print(results)

    def test_get_firmware_version(self):
        handler = susiiot.SusiIot()
        results = handler.get_firmware_version()
        print(results)

    def test_get_vcore(self):
        handler = susiiot.SusiIot()
        results = handler.get_vcore()
        print(results)

    def test_get_vcore_max(self):
        handler = susiiot.SusiIot()
        results = handler.get_vcore_max()
        print(results)

    def test_get_vcore_min(self):
        handler = susiiot.SusiIot()
        results = handler.get_vcore_min()
        print(results)

    def test_get_5v_standby(self):
        handler = susiiot.SusiIot()
        results = handler.get_5v_standby()
        print(results)

    def test_get_5v_standby_max(self):
        handler = susiiot.SusiIot()
        results = handler.get_5v_standby_max()
        print(results)

    def test_get_5v_standby_min(self):
        handler = susiiot.SusiIot()
        results = handler.get_5v_standby_min()
        print(results)

    def test_get_cmos_battery(self):
        handler = susiiot.SusiIot()
        results = handler.get_cmos_battery()
        print(results)

    def test_get_cmos_battery_max(self):
        handler = susiiot.SusiIot()
        results = handler.get_cmos_battery_max()
        print(results)

    def test_get_cmos_battery_min(self):
        handler = susiiot.SusiIot()
        results = handler.get_cmos_battery_min()
        print(results)

    def test_get_dc_power(self):
        handler = susiiot.SusiIot()
        results = handler.get_dc_power()
        print(results)

    def test_get_dc_power_max(self):
        handler = susiiot.SusiIot()
        results = handler.get_dc_power_max()
        print(results)

    def test_get_dc_power_min(self):
        handler = susiiot.SusiIot()
        results = handler.get_dc_power_min()
        print(results)

    def test_get_cpu_temperature_in_celsius(self):
        handler = susiiot.SusiIot()
        results = handler.get_cpu_temperature_in_celsius()
        print(results)

    def test_get_cpu_temperature_max_in_celsius(self):
        handler = susiiot.SusiIot()
        results = handler.get_cpu_temperature_max_in_celsius()
        print(results)

    def test_get_cpu_temperature_min_in_celsius(self):
        handler = susiiot.SusiIot()
        results = handler.get_cpu_temperature_min_in_celsius()
        print(results)

    def test_get_system_temperature_in_celsius(self):
        handler = susiiot.SusiIot()
        results = handler.get_system_temperature_in_celsius()
        print(results)

    def test_get_system_temperature_max_in_celsius(self):
        handler = susiiot.SusiIot()
        results = handler.get_system_temperature_max_in_celsius()
        print(results)

    def test_get_system_temperature_min_in_celsius(self):
        handler = susiiot.SusiIot()
        results = handler.get_system_temperature_min_in_celsius()
        print(results)

    def test_get_gpio_counter(self):
        handler = susiiot.SusiIot()
        result = handler.get_gpio_counter()
        print(result)
        logging.debug(result)

    def test_get_gpio_direction(self):
        handler = susiiot.SusiIot()
        gpio_count = handler.get_gpio_counter()
        for gpio in range(gpio_count):
            result = handler.get_gpio_direction(gpio)
            logging.debug(result)
            print(result)

    def test_get_gpio_level(self):
        handler = susiiot.SusiIot()
        gpio_count = handler.get_gpio_counter()
        for gpio in range(gpio_count):
            result = handler.get_gpio_level(gpio)
            logging.debug(result)
            print(result)

    def test_get_memory_count(self):
        handler = susiiot.SusiIot()
        result = handler.get_memory_count()
        logging.debug(result)
        print(result, 0)

    def test_get_memory_type(self):
        handler = susiiot.SusiIot()
        memory_count = handler.get_memory_count()
        for memeory_number in range(memory_count):
            result = handler.get_memory_type(memeory_number)
            logging.debug(result)
            print(result)

    def test_get_module_type(self):
        handler = susiiot.SusiIot()
        results = handler.get_module_type()
        print(results)

    def test_get_module_size_in_GB(self):
        handler = susiiot.SusiIot()
        results = handler.get_module_size_in_GB()
        print(results)

    def test_get_memory_speed(self):
        handler = susiiot.SusiIot()
        results = handler.get_memory_speed()
        print(results)

    def test_get_memory_rank(self):
        handler = susiiot.SusiIot()
        results = handler.get_memory_rank()
        print(results)

    def test_get_memory_voltage(self):
        handler = susiiot.SusiIot()
        results = handler.get_memory_voltage()
        print(results)

    def test_get_memory_bank(self):
        handler = susiiot.SusiIot()
        results = handler.get_memory_bank()
        print(results)

    def test_get_memory_week_year(self):
        handler = susiiot.SusiIot()
        results = handler.get_memory_week_year()
        print(results)

    def test_get_memory_temperature(self):
        handler = susiiot.SusiIot()
        result = handler.get_memory_temperature()
        logging.debug(result)
        print(result)

    def test_get_disk_total_disk_space(self):
        handler = susiiot.SusiIot()
        results = handler.get_disk_total_disk_space()
        print(results)

    def test_get_disk_free_disk_space(self):
        handler = susiiot.SusiIot()
        results = handler.get_disk_free_disk_space()
        print(results)

    def test_get_disk_media_recovery_total_disk_space(self):
        handler = susiiot.SusiIot()
        results = handler.get_disk_media_recovery_total_disk_space()
        print(results)

    def test_get_disk_media_recovery_free_disk_space(self):
        handler = susiiot.SusiIot()
        results = handler.get_disk_media_recovery_free_disk_space()
        print(results)

    def test_get_disk_free_disk_space(self):
        handler = susiiot.SusiIot()
        results = handler.get_disk_free_disk_space()
        print(results)

    def test_get_susiiot_version(self):
        handler = susiiot.SusiIot()
        results = handler.get_susiiot_version()
        print(results)


class TestCasesUNO1372G(unittest.TestCase):
    def test_boot_up_times(self):
        handler = susiiot.SusiIot()
        print(handler.boot_up_times)

    def test_running_time_in_hours(self):
        handler = susiiot.SusiIot()
        print(handler.running_time_in_hours)

    def test_board_name(self):
        handler = susiiot.SusiIot()
        print(handler.board_name)

    def test_bios_revision(self):
        handler = susiiot.SusiIot()
        print(handler.bios_revision)

    def test_firmware_name(self):
        handler = susiiot.SusiIot()
        print(handler.firmware_name)

    def test_driver_version(self):
        handler = susiiot.SusiIot()
        print(handler.driver_version)

    def test_firmware_version(self):
        handler = susiiot.SusiIot()
        print(handler.firmware_version)

    @unittest.skip("same id bug")
    def test_disk_total_disk_space(self):
        handler = susiiot.SusiIot()
        print(handler.disk_total_disk_space)

    def test_disk_free_disk_space(self):
        handler = susiiot.SusiIot()
        print(handler.disk_free_disk_space)

    def test_voltage_vcore(self):
        handler = susiiot.SusiIot()
        print(handler.voltage_vcore)

    def test_voltage_5v_standby(self):
        handler = susiiot.SusiIot()
        print(handler.voltage_5v_standby)

    def test_voltage_cmos_battery(self):
        handler = susiiot.SusiIot()
        print(handler.voltage_cmos_battery)

    def test_dc_power(self):
        handler = susiiot.SusiIot()
        print(handler.dc_power)

    def test_cpu_temperature_in_celsius(self):
        handler = susiiot.SusiIot()
        print(handler.cpu_temperature_in_celsius)

    def test_system_temperature_in_celsius(self):
        handler = susiiot.SusiIot()
        print(handler.system_temperature_in_celsius)


class TestCasesModule(unittest.TestCase):
    def test_boot_up_times(self):
        handler = susiiot.SusiIot()
        print(handler.boot_up_times)

    def test_running_time_in_hours(self):
        handler = susiiot.SusiIot()
        print(handler.running_time_in_hours)

    def test_board_name(self):
        handler = susiiot.SusiIot()
        print(handler.board_name)

    def test_bios_revision(self):
        handler = susiiot.SusiIot()
        print(handler.bios_revision)

    def test_firmware_name(self):
        handler = susiiot.SusiIot()
        print(handler.firmware_name)

    def test_driver_version(self):
        handler = susiiot.SusiIot()
        print(handler.driver_version)

    def test_firmware_version(self):
        handler = susiiot.SusiIot()
        print(handler.firmware_version)

    @unittest.skip("same id bug")
    def test_disk_total_disk_space(self):
        handler = susiiot.SusiIot()
        print(handler.disk_total_disk_space)

    def test_disk_free_disk_space(self):
        handler = susiiot.SusiIot()
        print(handler.disk_free_disk_space)

    def test_voltage_vcore(self):
        handler = susiiot.SusiIot()
        print(handler.voltage_vcore)

    def test_voltage_vcore(self):
        handler = susiiot.SusiIot()
        print(handler.voltage_vcore)

    @unittest.skip("api get null")
    def test_voltage_3p3v_standby(self):
        handler = susiiot.SusiIot()
        print(handler.voltage_3p3v_standby)

    @unittest.skip("api get null")
    def test_voltage_5v(self):
        handler = susiiot.SusiIot()
        print(handler.voltage_5v)

    @unittest.skip("api get null")
    def test_voltage_12v(self):
        handler = susiiot.SusiIot()
        print(handler.voltage_12v)

    def test_voltage_5v_standby(self):
        handler = susiiot.SusiIot()
        print(handler.voltage_5v_standby)

    def test_voltage_cmos_battery(self):
        handler = susiiot.SusiIot()
        print(handler.voltage_cmos_battery)

    def test_dc_power(self):
        handler = susiiot.SusiIot()
        print(handler.dc_power)

    def test_cpu_temperature_in_celsius(self):
        handler = susiiot.SusiIot()
        print(handler.cpu_temperature_in_celsius)

    def test_system_temperature_in_celsius(self):
        handler = susiiot.SusiIot()
        print(handler.system_temperature_in_celsius)

    def test_cpu_fan_speed(self):
        handler = susiiot.SusiIot()
        print(handler.cpu_fan_speed)

    def test_system_fan_speed(self):
        handler = susiiot.SusiIot()
        print(handler.system_fan_speed)

    def test_susiiot_version(self):
        handler = susiiot.SusiIot()
        print(handler.susiiot_version)

    @unittest.skip("api get null")
    def test_backlight_frequency(self):
        handler = susiiot.SusiIot()
        print(handler.backlight_frequency)

    @unittest.skip("api get null")
    def test_backlight_polarity(self):
        handler = susiiot.SusiIot()
        print(handler.backlight_polarity)

    @unittest.skip("api get null")
    def test_backlight_backlight(self):
        handler = susiiot.SusiIot()
        print(handler.backlight_backlight)

    @unittest.skip("api get null")
    def test_backlight_brightness(self):
        handler = susiiot.SusiIot()
        print(handler.backlight_brightness)


if __name__ == '__main__':
    unittest.main()
