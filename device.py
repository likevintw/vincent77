
import susiiot


class Device:
    def __init__(self):
        self.cpu = cpu.Cpu()
        self.memory = memory.Memory()

        self.provider = FeatureProvider()
        self.motherboard = provider.motherboard

    @property
    def cpu_temperature(self):
        return self.susiiot.get_cpu_tempature()
