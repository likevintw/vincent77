
import susiiot


class Device:
    def __init__(self):
        self.cusor = None

        self.boot_up_time = None
        self.running_time_in_hours = None
        self.board_name = None
        self.board_manufacturer = None
        self.bios_version = None
        self.firmware_name = None
        self.firmware_version = None
        self.driver_version = None
        self.library_version = None
        self.voltage_vcore = None
        self.voltage_5v_standby = None
        self.voltage_cmos_battery = None
        self.voltage_dc = None
        self.cpu_temperature_in_celsius = None
        self.system_temperature_in_celsius = None
        self.cpu_fan_speed = None
        self.system_fan_speed = None

    def initialize():
        pass

    @property
    def cpu_temperature_in_celsius(self):
        return self.cusor.get_cpu_tempature()

    @property
    def system_temperature_in_celsius(self):
        return self.cusor.system_temperature_in_celsius()

    @property
    def cpu_fan_speed(self):
        return self.cusor.cpu_fan_speed()

    @property
    def system_fan_speed(self):
        return self.cusor.system_fan_speed()
