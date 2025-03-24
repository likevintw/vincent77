
import susiiot
import imotherboad
import igpio
import iwatchdog


class Device(imotherboad.IMotherboard):
    def __init__(self):
        self.sdk=None

    def initialize():
        pass

    @abstractmethod
    @property
    def name(self) -> str:
        return

    @abstractmethod
    @property
    def cpu_model(self) -> str:
        pass

    @abstractmethod
    @property
    def os_revision(self) -> str:
        return "todo"

    @abstractmethod
    @property
    def bios_revision(self) -> str:
        pass

    @abstractmethod
    @property
    def ec_revision(self) -> str:
        pass

    @abstractmethod
    def get_voltage(self, voltage_source) -> float:
        pass

    @abstractmethod
    def get_temperature(self, temperature_source) -> float:
        pass

    @abstractmethod
    @property
    def voltage_sources(self) -> List[str]:
        pass

    @abstractmethod
    @property
    def temperature_sources(self) -> List[str]:
        pass
