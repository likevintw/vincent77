from abc import ABC, abstractmethod
from typing import List
import ifeature


class IMotherboard(ABC):
    @property
    @abstractmethod
    def name(self) -> str:
        pass

    @property
    @abstractmethod
    def cpu_model(self) -> str:
        pass

    @property
    @abstractmethod
    def os_revision(self) -> str:
        pass

    @property
    @abstractmethod
    def bios_revision(self) -> str:
        pass

    @property
    @abstractmethod
    def ec_revision(self) -> str:
        pass

    @abstractmethod
    def get_voltage(self, voltage_source) -> float:
        pass

    @abstractmethod
    def get_temperature(self, temperature_source) -> float:
        pass

    @property
    @abstractmethod
    def voltage_sources(self) -> List[str]:
        pass

    @property
    @abstractmethod
    def temperature_sources(self) -> List[str]:
        pass
