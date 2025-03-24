
import susiiot
import imotherboad

class Device(imotherboad.IMotherboard):
    def __init__(self):
        self.library = None

    def initialize():
        # check device version to determine library, susi, platform or others
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
