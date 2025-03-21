
import unittest
import susiiot
import os
import platform
import logging
import time
import datetime


formatted_time = datetime.datetime.fromtimestamp(
    time.time()).strftime('%Y-%m-%d %H:%M:%S')
print(f"test time: {formatted_time}")
print(f"OS Name: {platform.system()}")
print(f"OS Version: {platform.system()}")
print(f"architecture: {platform.machine()}")


class AttributeTestCases(unittest.TestCase):
    @unittest.skip("pass")
    def test_get_data_by_id_with_json(self):
        handler = susiiot.SusiIot()
        handler.susi_information = {
            "Hardware Monitor": {
                "id": 131072,
                "bn": "Hardware Monitor",
                "Temperature": {
                    "e": [
                        {
                            "n": "CPU",
                            "v": 69.5,
                            "max": 100,
                            "min": 0,
                            "id": 16908545
                        },
                        {
                            "n": "System",
                            "v": 0,
                            "max": 100,
                            "min": 0,
                            "id": 16908547
                        }
                    ],
                    "bn": "Temperature",
                    "bt": 1276020076,
                    "bu": "Cel",
                    "ver": 1,
                    "id": 131328
                },
                "Voltage": {
                    "e": [
                        {
                            "n": "Vcore",
                            "v": 1.184,
                            "max": 15,
                            "min": 0,
                            "id": 16908801
                        },
                        {
                            "n": "3.3V",
                            "v": 3.408,
                            "max": 15,
                            "min": 0,
                            "id": 16908804
                        },
                        {
                            "n": "5V",
                            "v": 5.088,
                            "max": 15,
                            "min": 0,
                            "id": 16908805
                        },
                        {
                            "n": "12V",
                            "v": 12.288,
                            "max": 15,
                            "min": 0,
                            "id": 16908806
                        },
                        {
                            "n": "5V Standby",
                            "v": 5.056,
                            "max": 15,
                            "min": 0,
                            "id": 16908807
                        },
                        {
                            "n": "CMOS Battery",
                            "v": 3.024,
                            "max": 15,
                            "min": 0,
                            "id": 16908809
                        }
                    ],
                    "bn": "Voltage",
                    "bt": 1276020076,
                    "bu": "V",
                    "ver": 1,
                    "id": 131584
                },
                "Fan Speed": {
                    "e": [
                        {
                            "n": "CPU",
                            "v": 0,
                            "max": 8000,
                            "min": 0,
                            "id": 16909057
                        },
                        {
                            "n": "System",
                            "v": 10465,
                            "max": 8000,
                            "min": 0,
                            "id": 16909058
                        }
                    ],
                    "bn": "Fan Speed",
                    "bt": 1276020076,
                    "bu": "RPM",
                    "ver": 1,
                    "id": 131840
                }
            },
            "Platform Information": {
                "e": [
                    {
                        "n": "Board manufacturer",
                        "sv": "Advantech",
                        "id": 16843777
                    },
                    {
                        "n": "Board name",
                        "sv": "ARK-DS520",
                        "id": 16843778
                    },
                    {
                        "n": "BIOS revision",
                        "sv": "V1.13",
                        "id": 16843781
                    },
                    {
                        "n": "Driver version",
                        "sv": "4.0.12800",
                        "id": 16843265
                    },
                    {
                        "n": "Library version",
                        "sv": "4.0.12800",
                        "id": 16843266
                    }
                ],
                "bu": "Info",
                "bn": "Platform Information",
                "bt": 1276020076,
                "id": 65536,
                "ver": 1
            },
            "M2Talk": {
                "bn": "M2Talk",
                "id": 34603008,
                "Device1": {
                    "e": [
                        {
                            "min": 0,
                            "asm": "rw",
                            "n": "Brightness",
                            "v": 1,
                            "u": "Lv",
                            "max": 255,
                            "sui": "",
                            "ui": "TextBox",
                            "id": 34603281
                        },
                        {
                            "min": 0,
                            "asm": "r",
                            "n": "Backlight Current",
                            "v": 2,
                            "u": "A",
                            "max": 255,
                            "sui": "",
                            "ui": "Label",
                            "id": 34603282
                        },
                        {
                            "min": 0,
                            "asm": "r",
                            "n": "Button 1",
                            "v": 0,
                            "u": "Bool",
                            "max": 1,
                            "sui": "",
                            "ui": "CheckBox",
                            "id": 34603297
                        },
                        {
                            "min": 0,
                            "asm": "r",
                            "n": "Button 2",
                            "v": 0,
                            "u": "Bool",
                            "max": 1,
                            "sui": "",
                            "ui": "CheckBox",
                            "id": 34603298
                        },
                        {
                            "min": 0,
                            "asm": "r",
                            "n": "Button 3",
                            "v": 0,
                            "u": "Bool",
                            "max": 1,
                            "sui": "",
                            "ui": "CheckBox",
                            "id": 34603299
                        },
                        {
                            "min": 0,
                            "asm": "r",
                            "n": "Button 4",
                            "v": 0,
                            "u": "Bool",
                            "max": 1,
                            "sui": "",
                            "ui": "CheckBox",
                            "id": 34603300
                        },
                        {
                            "min": 0,
                            "asm": "r",
                            "n": "Proximity",
                            "v": 2,
                            "u": "V",
                            "max": 255,
                            "sui": "",
                            "ui": "Label",
                            "id": 34603313
                        },
                        {
                            "min": -128,
                            "asm": "r",
                            "n": "Punch Acc X",
                            "v": -32,
                            "u": "g",
                            "max": 127,
                            "sui": "",
                            "ui": "Label",
                            "id": 34603329
                        },
                        {
                            "min": -128,
                            "asm": "r",
                            "n": "Punch Acc Y",
                            "v": 29,
                            "u": "g",
                            "max": 127,
                            "sui": "",
                            "ui": "Label",
                            "id": 34603330
                        },
                        {
                            "min": -128,
                            "asm": "r",
                            "n": "Punch Acc Z",
                            "v": 254,
                            "u": "g",
                            "max": 127,
                            "sui": "",
                            "ui": "Label",
                            "id": 34603331
                        },
                        {
                            "min": 0,
                            "asm": "rw",
                            "n": "Punch Threshold",
                            "v": 10,
                            "u": "g",
                            "max": 255,
                            "sui": "",
                            "ui": "TextBox",
                            "id": 34603332
                        },
                        {
                            "min": 0,
                            "asm": "rw",
                            "n": "Punch Time",
                            "v": 4,
                            "u": "ms",
                            "max": 255,
                            "sui": "",
                            "ui": "TextBox",
                            "id": 34603333
                        },
                        {
                            "min": 0,
                            "asm": "rw",
                            "n": "Tap Threshold",
                            "v": 1,
                            "u": "g",
                            "max": 255,
                            "sui": "",
                            "ui": "TextBox",
                            "id": 34603345
                        },
                        {
                            "min": 0,
                            "asm": "rw",
                            "n": "Tap Width",
                            "v": 20,
                            "u": "ms",
                            "max": 255,
                            "sui": "",
                            "ui": "TextBox",
                            "id": 34603346
                        },
                        {
                            "min": 0,
                            "asm": "rw",
                            "n": "Tap Latency",
                            "v": 20,
                            "u": "ms",
                            "max": 255,
                            "sui": "",
                            "ui": "TextBox",
                            "id": 34603347
                        },
                        {
                            "min": 0,
                            "asm": "r",
                            "n": "Display 5V",
                            "v": 1,
                            "u": "Bool",
                            "max": 1,
                            "sui": "",
                            "ui": "CheckBox",
                            "id": 34603361
                        },
                        {
                            "min": 0,
                            "asm": "r",
                            "n": "Ext Light",
                            "v": 0,
                            "u": "Bool",
                            "max": 1,
                            "sui": "",
                            "ui": "CheckBox",
                            "id": 34603362
                        },
                        {
                            "min": -128,
                            "asm": "r",
                            "n": "Temperature",
                            "v": 31,
                            "u": "Cel",
                            "max": 127,
                            "sui": "",
                            "ui": "Label",
                            "id": 34603363
                        },
                        {
                            "min": 0,
                            "asm": "r",
                            "n": "Up Time",
                            "v": 50,
                            "u": "hr",
                            "max": 438000,
                            "sui": "",
                            "ui": "Label",
                            "id": 34603364
                        }
                    ],
                    "bu": "",
                    "bn": "Device1",
                    "bt": 0,
                    "id": 34603264,
                    "ver": 1
                }
            },
            "GPIO": {
                "id": 262144,
                "bn": "GPIO",
                "GPIO00": {
                    "e": [
                        {
                            "n": "Dir",
                            "bv": 1,
                            "max": 1,
                            "min": 0,
                            "id": 17039873,
                            "asm": "rw",
                            "ui": "TextBox"
                        },
                        {
                            "n": "level",
                            "bv": 1,
                            "max": 1,
                            "min": 0,
                            "id": 17040129,
                            "asm": "rw",
                            "ui": "TextBox"
                        }
                    ],
                    "bn": "GPIO00",
                    "bt": 1276020076,
                    "bu": "V",
                    "ver": 1,
                    "id": 17039617
                },
                "GPIO01": {
                    "e": [
                        {
                            "n": "Dir",
                            "bv": 1,
                            "max": 1,
                            "min": 0,
                            "id": 17039874,
                            "asm": "rw",
                            "ui": "TextBox"
                        },
                        {
                            "n": "level",
                            "bv": 1,
                            "max": 1,
                            "min": 0,
                            "id": 17040130,
                            "asm": "rw",
                            "ui": "TextBox"
                        }
                    ],
                    "bn": "GPIO01",
                    "bt": 1276020076,
                    "bu": "V",
                    "ver": 1,
                    "id": 17039618
                },
                "GPIO04": {
                    "e": [
                        {
                            "n": "Dir",
                            "bv": 1,
                            "max": 1,
                            "min": 0,
                            "id": 17039877,
                            "asm": "rw",
                            "ui": "TextBox"
                        },
                        {
                            "n": "level",
                            "bv": 1,
                            "max": 1,
                            "min": 0,
                            "id": 17040133,
                            "asm": "rw",
                            "ui": "TextBox"
                        }
                    ],
                    "bn": "GPIO04",
                    "bt": 1276020076,
                    "bu": "V",
                    "ver": 1,
                    "id": 17039621
                },
                "GPIO02": {
                    "e": [
                        {
                            "n": "Dir",
                            "bv": 1,
                            "max": 1,
                            "min": 0,
                            "id": 17039875,
                            "asm": "rw",
                            "ui": "TextBox"
                        },
                        {
                            "n": "level",
                            "bv": 1,
                            "max": 1,
                            "min": 0,
                            "id": 17040131,
                            "asm": "rw",
                            "ui": "TextBox"
                        }
                    ],
                    "bn": "GPIO02",
                    "bt": 1276020076,
                    "bu": "V",
                    "ver": 1,
                    "id": 17039619
                },
                "GPIO03": {
                    "e": [
                        {
                            "n": "Dir",
                            "bv": 1,
                            "max": 1,
                            "min": 0,
                            "id": 17039876,
                            "asm": "rw",
                            "ui": "TextBox"
                        },
                        {
                            "n": "level",
                            "bv": 1,
                            "max": 1,
                            "min": 0,
                            "id": 17040132,
                            "asm": "rw",
                            "ui": "TextBox"
                        }
                    ],
                    "bn": "GPIO03",
                    "bt": 1276020076,
                    "bu": "V",
                    "ver": 1,
                    "id": 17039620
                },
                "GPIO05": {
                    "e": [
                        {
                            "n": "Dir",
                            "bv": 1,
                            "max": 1,
                            "min": 0,
                            "id": 17039878,
                            "asm": "rw",
                            "ui": "TextBox"
                        },
                        {
                            "n": "level",
                            "bv": 1,
                            "max": 1,
                            "min": 0,
                            "id": 17040134,
                            "asm": "rw",
                            "ui": "TextBox"
                        }
                    ],
                    "bn": "GPIO05",
                    "bt": 1276020076,
                    "bu": "V",
                    "ver": 1,
                    "id": 17039622
                },
                "GPIO06": {
                    "e": [
                        {
                            "n": "Dir",
                            "bv": 1,
                            "max": 1,
                            "min": 0,
                            "id": 17039879,
                            "asm": "rw",
                            "ui": "TextBox"
                        },
                        {
                            "n": "level",
                            "bv": 1,
                            "max": 1,
                            "min": 0,
                            "id": 17040135,
                            "asm": "rw",
                            "ui": "TextBox"
                        }
                    ],
                    "bn": "GPIO06",
                    "bt": 1276020076,
                    "bu": "V",
                    "ver": 1,
                    "id": 17039623
                },
                "GPIO07": {
                    "e": [
                        {
                            "n": "Dir",
                            "bv": 1,
                            "max": 1,
                            "min": 0,
                            "id": 17039880,
                            "asm": "rw",
                            "ui": "TextBox"
                        },
                        {
                            "n": "level",
                            "bv": 1,
                            "max": 1,
                            "min": 0,
                            "id": 17040136,
                            "asm": "rw",
                            "ui": "TextBox"
                        }
                    ],
                    "bn": "GPIO07",
                    "bt": 1276020076,
                    "bu": "V",
                    "ver": 1,
                    "id": 17039624
                }
            },
            "Backlight": {
                "id": 327680,
                "bn": "Backlight",
                "Backlight 1": {
                    "e": [
                        {
                            "n": "frequency",
                            "v": 234,
                            "max": 65535,
                            "min": 1,
                            "id": 17105409,
                            "asm": "rw",
                            "ui": "TextBox"
                        },
                        {
                            "n": "polarity",
                            "bv": 0,
                            "max": 1,
                            "min": 0,
                            "id": 17105665,
                            "asm": "rw",
                            "ui": "TextBox"
                        },
                        {
                            "n": "backlight",
                            "bv": 0,
                            "max": 1,
                            "min": 0,
                            "id": 17105921,
                            "asm": "rw",
                            "ui": "TextBox"
                        },
                        {
                            "n": "brightness",
                            "v": 250,
                            "max": 255,
                            "min": 0,
                            "id": 17106177,
                            "asm": "rw",
                            "ui": "TextBox"
                        }
                    ],
                    "bn": "Backlight 1",
                    "bt": 1276020076,
                    "bu": "V",
                    "ver": 1,
                    "id": 17105153
                }
            }
        }
        handler.create_name_id_list()
        print()
        for item_name in handler.susi_id_name_table.keys():
            result = handler.get_data_by_id(
                handler.susi_id_name_table[item_name])
            if result == {}:
                print(f"{item_name} result is {result}")

    def test_get_data_by_id(self):
        handler = susiiot.SusiIot()
        for item_name in handler.susi_id_name_table.keys():
            result = handler.get_data_by_id(
                handler.susi_id_name_table[item_name])
            if result == {}:
                print(f"{item_name} result is {result}")

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
        handler.cpu

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
        print()
        for i in range(handler.gpio_counter):
            print(f"GPIO{i}, direction:{handler.get_gpio_direction(i)}")

    def test_get_gpio_level(self):
        handler = susiiot.SusiIot()
        print()
        for i in range(handler.gpio_counter):
            print(f"GPIO{i}, level:{handler.get_gpio_level(i)}")

    def test_set_gpio_direction(self):
        handler = susiiot.SusiIot()
        origin = 0
        changed = 0
        print()
        for gpio_number in range(handler.gpio_counter):
            origin = handler.get_gpio_direction(gpio_number)
            changed = origin ^ 1
            result = handler.set_gpio_direction(gpio_number, changed)
            if not result:
                print(f"set GPIO direction {gpio_number} from {origin} to {changed}, fail")
                exit(1)
            print(f"set GPIO direction {gpio_number} from {origin} to {changed}, successfully")
            handler.set_gpio_direction(gpio_number, origin)
            if not result:
                print(f"set GPIO direction {gpio_number} from {origin} to {changed}, fail")
                exit(1)
            self.assertEqual(handler.get_gpio_direction(gpio_number), origin)
            print(f"set GPIO direction {gpio_number} from {changed} to {origin}, successfully")

    def test_set_gpio_level(self):
        handler = susiiot.SusiIot()
        origin = 0
        changed = 0
        print()
        for gpio_number in range(handler.gpio_counter):
            origin = handler.get_gpio_level(gpio_number)
            changed = origin ^ 1
            result = handler.set_gpio_level(gpio_number, changed)
            if result == False:
                print(f"set GPIO{gpio_number} level {result}, Please check the direction; it must be output.")
                continue
            if result == None:
                print(f"GPIO{gpio_number} is not exist")
                continue
            print(f"set GPIO{gpio_number} level from {origin} to {changed}, successfully")
            handler.set_gpio_level(gpio_number, origin)
            if result == False:
                print(f"set GPIO{gpio_number} level {result}, Please check the direction; it must be output.")
                continue
            if result == None:
                print(f"GPIO{gpio_number} is not exist")
                continue
            print(f"set GPIO{gpio_number} level from {changed} to {origin}, successfully")

    def test_get_memory_type(self):
        handler = susiiot.SusiIot()
        for i in range(handler.memory_count):
            print(f"SDRAM{i} type: {handler.get_memory_type(i)}")

    def test_get_module_type(self):
        handler = susiiot.SusiIot()
        for i in range(handler.memory_count):
            print(f"SDRAM{i} module: {handler.get_module_type(i)}")

    def test_get_module_size_in_GB(self):
        handler = susiiot.SusiIot()
        for i in range(handler.memory_count):
            print(f"SDRAM{i} module size: {handler.get_module_size_in_GB(i)} GB")

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


class TestCases(unittest.TestCase):
    def test_susi_information(self):
        handler = susiiot.SusiIot()
        print(handler.susiiot_information)

    def test_susi_id_name_table(self):
        handler = susiiot.SusiIot()
        print()
        for name in handler.susi_id_name_table.keys():
            print(name, handler.susi_id_name_table[name])

    def test_get_data_by_id(self):
        handler = susiiot.SusiIot()
        for item_name in handler.susi_id_name_table.keys():
            result = handler.get_data_by_id(
                handler.susi_id_name_table[item_name])
            print(f"{item_name} result is {result}")
            print()


if __name__ == '__main__':
    unittest.main()
