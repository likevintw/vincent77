import ctypes
import json
import sys


class Susi4:
    def __init__(self, susi4_library_path="./libSUSI-4.00.so.1 "):
        self.susi4_library = ctypes.CDLL(susi4_library_path)
        self.initialization()
        self.SUSIDEMO_INFORMATION_STRING_MAX = 9
        self.gpio_bank_base = int(0x00010000)
        self.SUSI_ID_GPIO_INPUT_SUPPORT = int(0x00000000)
        self.SUSI_ID_GPIO_OUTPUT_SUPPORT = int(0x00000001)
        self.gpio_bank_base = int(0x00010000)

    def __del__(self):
        self.susi4_library.SusiLibUninitialize()

    def initialization(self):
        self.susi4_library.SusiLibInitialize.restype = ctypes.c_uint32

        status = self.susi4_library.SusiLibInitialize()
        if status == int(0xFFFFF0FF):
            print("Your Linux capabilities is not enough, recommond to become ROOT!")
            print("Aborting demo now.")
            exit(0)
        elif status != 0 and status != int(0xFFFFF0FF):
            print("SusiLibInitialize() failed. (0x%08X)", status)
            print("Exit the program...")
            exit(0)
        print("susi4 initialize successfully: ", status)

    def get_gpio_information(self):
        # todo, when _RISC system, SUSIDEMO_BANK_MAX=40, esle =4
        SUSIDEMO_BANK_MAX = 40
        # SUSIDEMO_BANK_MAX=4
        result = 0
        for pin in range(SUSIDEMO_BANK_MAX):
            id_number = self.gpio_bank_base+pin
            state = self.susi4_library.SusiGPIOGetCaps(
                id_number, self.SUSI_ID_GPIO_INPUT_SUPPORT, result)
            print("result: ", result)
            print("state: ", state)
