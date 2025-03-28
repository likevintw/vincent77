from abc import ABC, abstractmethod
from typing import List



class IMemory(ABC):
    @abstractmethod
    def get_direction(self, pin: str) -> None:
        pass

    @abstractmethod
    def set_direction(self, pin: str, direction: GpioDirectionType) -> None:
        pass

    @abstractmethod
    def get_level(self, pin: str) -> None:
        pass

    @abstractmethod
    def set_level(self, pin: str, level: GpioLevelType) -> None:
        pass

    @property
    @abstractmethod
    def memory_count(self) -> List[str]:
        pass
