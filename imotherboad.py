from abc import ABC, abstractmethod
from typing import List
import ifeature


class IMotherboard(ABC, ifeature.IFeature):
    @abstractmethod
    @property
    def name(self) -> str:
        pass

    @abstractmethod
    @property
    def cpu_model(self) -> str:
        pass

    @abstractmethod
    @property
    def os_revision(self) -> str:
        pass

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
