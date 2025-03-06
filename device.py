
import susiiot



class Device:
    def __init__(self):
        self.susiiot=susiiot.SusiIot()
    @property
    def cpu_temperature(self):
        return self.susiiot.get_cpu_tempature()

device=Device()
device.cpu_temperature
device.cpu_temperature=5