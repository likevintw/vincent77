
import unittest
import susiiot
import os
import platform
import logging

class TestCases(unittest.TestCase):
    def test_record_test_information(self):
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

    def test_get_gpio_direction(self):
        handler = susiiot.SusiIot()
        for i in range(8):
            print(handler.get_gpio_direction(i))

    def test_get_gpio_level(self):
        handler = susiiot.SusiIot()
        for i in range(8):
            print(i, handler.get_gpio_level(i))

    def test_set_gpio_00(self):
        handler = susiiot.SusiIot()
        result = handler.set_value(17039873, 0)
        result = handler.get_data_by_id(17039873)
        print(result)
        result = handler.set_value(17039873, 1)
        result = handler.get_data_by_id(17039873)
        print(result)

    def test_set_gpio_direction(self):
        handler = susiiot.SusiIot()
        origin = 0
        changed = 0
        for gpio_number in range(8):
            print(f"GPIO {gpio_number}")
            origin = handler.get_gpio_direction(gpio_number)
            self.assertEqual(handler.get_gpio_direction(gpio_number), origin)
            changed = origin ^ 1
            handler.set_gpio_direction(gpio_number, changed)
            self.assertNotEqual(
                handler.get_gpio_direction(gpio_number), origin)
            handler.set_gpio_direction(gpio_number, origin)
            self.assertEqual(handler.get_gpio_direction(gpio_number), origin)

    def test_set_gpio_level(self):
        # todo
        pass
        # handler = susiiot.SusiIot()
        # origin=0
        # changed=0
        # for i in range(8):
        #     print(f"GPIO {i}")
        #     origin=handler.get_gpio_level(i)
        #     self.assertEqual(handler.get_gpio_level(i),origin)
        #     changed=origin^1
        #     handler.set_gpio_level(i,changed)
        #     self.assertNotEqual(handler.get_gpio_level(i),origin)
        #     handler.set_gpio_level(i,origin)
        #     self.assertEqual(handler.get_gpio_level(i),origin)

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

    def test_voltage_3p3v(self):
        handler = susiiot.SusiIot()
        print(handler.voltage_3p3v)

    def test_voltage_5v(self):
        handler = susiiot.SusiIot()
        print(handler.voltage_5v)

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

    def test_backlight_frequency(self):
        handler = susiiot.SusiIot()
        print(handler.backlight_frequency)

    def test_backlight_polarity(self):
        handler = susiiot.SusiIot()
        print(handler.backlight_polarity)

    def test_backlight_backlight(self):
        handler = susiiot.SusiIot()
        print(handler.backlight_backlight)

    def test_backlight_brightness(self):
        handler = susiiot.SusiIot()
        print(handler.backlight_brightness)


if __name__ == '__main__':
    unittest.main()
