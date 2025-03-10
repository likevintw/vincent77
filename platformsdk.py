
import ctypes
import os
import platform


class PlatformSDK:
    def __init__(self):
        self.e_api_library = None
        self.EApiBoardGetStringA = None
        self.EApiBoardGetValue = None
        self.EApiLibInitialize= None

        self.import_library()
        self.initial_constant()
        self.initialize()

    def import_library(self):
        current_dir = os.path.dirname(os.path.realpath(__file__))+"/"
        architecture = platform.machine()
        os_name = platform.system()
        e_api_library_path = ""

        if os_name == "Linux" and 'x86' in architecture.lower():
            e_api_library_path = current_dir+"libEAPI.x86.so"

        elif os_name == "Linux" and 'aarch64' in architecture.lower():
            e_api_library_path = current_dir+"libSusiIoT.arm.so"

        elif os_name == "Windows" and 'x86' in architecture.lower():
            pass

        elif os_name == "Windows" and 'aarch64' in architecture.lower():
            pass

        else:
            print(
                f"disable to import library, architechture:{architecture.lower()}, os:{os_name}")

        self.e_api_library = ctypes.CDLL(e_api_library_path)

    def initial_constant(self):
        self.EAPI_VER_MASK_VER = 0xFF000000
        self.EAPI_VER_MASK_REV = 0x00FF0000
        self.EAPI_VER_MASK_BUILD = 0x0000FFFF

        self.EAPI_VER = 1
        self.EAPI_REVISION = 0

        self.EAPI_STATUS_NOT_INITIALIZED = 0xFFFFFFFF
        self.EAPI_STATUS_INITIALIZED = 0xFFFFFFFE
        self.EAPI_STATUS_ALLOC_ERROR = 0xFFFFFFFD
        self.EAPI_STATUS_DRIVER_TIMEOUT = 0xFFFFFFFC
        self.EAPI_STATUS_INVALID_PARAMETER = 0xFFFFFEFF
        self.EAPI_STATUS_INVALID_BLOCK_ALIGNMENT = 0xFFFFFEFE
        self.EAPI_STATUS_INVALID_BLOCK_LENGTH = 0xFFFFFEFD
        self.EAPI_STATUS_INVALID_DIRECTION = 0xFFFFFEFC
        self.EAPI_STATUS_INVALID_BITMASK = 0xFFFFFEFB
        self.EAPI_STATUS_RUNNING = 0xFFFFFEFA
        self.EAPI_STATUS_UNSUPPORTED = 0xFFFFFCFF
        self.EAPI_STATUS_NOT_FOUND = 0xFFFFFBFF
        self.EAPI_STATUS_TIMEOUT = 0xFFFFFBFE
        self.EAPI_STATUS_BUSY_COLLISION = 0xFFFFFBFD
        self.EAPI_STATUS_READ_ERROR = 0xFFFFFAFF
        self.EAPI_STATUS_WRITE_ERROR = 0xFFFFFAFE
        self.EAPI_STATUS_MORE_DATA = 0xFFFFF9FF
        self.EAPI_STATUS_GET_STATUS_ERROR = 0xFFFFF8FF
        self.EAPI_STATUS_LOCKED = 0xFFFFF8FE
        self.EAPI_STATUS_ERROR = 0xFFFFF0FF
        self.EAPI_STATUS_SUCCESS = 0

        self.EAPI_ID_BASE_GET_NAME_INFO = 0x00000000
        self.EAPI_ID_BASE_GET_NAME_HWMON = 0x10000000
        self.EAPI_ID_BASE_GET_NAME_I2C = 0x20000000
        self.EAPI_ID_BASE_GET_NAME_SMB = 0x30000000
        self.EAPI_ID_BASE_GET_NAME_GPIO = 0x40000000
        self.EAPI_ID_BASE_GET_NAME_WDT = 0x50000000
        self.EAPI_ID_BASE_GET_NAME_VGA_BACKLIGHT = 0x60000000
        self.EAPI_ID_BASE_GET_NAME_STORAGE = 0x70000000
        self.EAPI_ID_BASE_GET_NAME_TML = 0x80000000

        self.EAPI_ID_BOARD_MANUFACTURER_STR = 0
        self.EAPI_ID_BOARD_NAME_STR = 1
        self.EAPI_ID_BOARD_REVISION_STR = 2
        self.EAPI_ID_BOARD_SERIAL_STR = 3
        self.EAPI_ID_BOARD_BIOS_REVISION_STR = 4
        self.EAPI_ID_BOARD_HW_REVISION_STR = 5
        self.EAPI_ID_BOARD_PLATFORM_TYPE_STR = 6

        self.EAPI_ID_HWMON_TEMP_MAX = 10
        self.EAPI_ID_HWMON_TEMP_BASE = 0x00050000
        self.EAPI_ID_HWMON_TEMP = self.EAPI_ID_HWMON_TEMP_BASE
        self.EAPI_ID_HWMON_TEMP_CPU = self.EAPI_ID_HWMON_TEMP_BASE + 0
        self.EAPI_ID_HWMON_TEMP_CHIPSET = self.EAPI_ID_HWMON_TEMP_BASE + 1
        self.EAPI_ID_HWMON_TEMP_SYSTEM = self.EAPI_ID_HWMON_TEMP_BASE + 2
        self.EAPI_ID_HWMON_TEMP_CPU2 = self.EAPI_ID_HWMON_TEMP_BASE + 3
        self.EAPI_ID_HWMON_TEMP_OEM0 = self.EAPI_ID_HWMON_TEMP_BASE + 4
        self.EAPI_ID_HWMON_TEMP_OEM1 = self.EAPI_ID_HWMON_TEMP_BASE + 5
        self.EAPI_ID_HWMON_TEMP_OEM2 = self.EAPI_ID_HWMON_TEMP_BASE + 6
        self.EAPI_ID_HWMON_TEMP_OEM3 = self.EAPI_ID_HWMON_TEMP_BASE + 7
        self.EAPI_ID_HWMON_TEMP_OEM4 = self.EAPI_ID_HWMON_TEMP_BASE + 8
        self.EAPI_ID_HWMON_TEMP_OEM5 = self.EAPI_ID_HWMON_TEMP_BASE + 9

        self.EAPI_ID_HWMON_VOLTAGE_MAX = 25
        self.EAPI_ID_HWMON_VOLTAGE_BASE = 0x00051000
        self.EAPI_ID_HWMON_VOLTAGE = self.EAPI_ID_HWMON_VOLTAGE_BASE
        self.EAPI_ID_HWMON_VOLTAGE_VCORE = self.EAPI_ID_HWMON_VOLTAGE_BASE + 0
        self.EAPI_ID_HWMON_VOLTAGE_VCORE2 = self.EAPI_ID_HWMON_VOLTAGE_BASE + 1
        self.EAPI_ID_HWMON_VOLTAGE_2V5 = self.EAPI_ID_HWMON_VOLTAGE_BASE + 2
        self.EAPI_ID_HWMON_VOLTAGE_3V3 = self.EAPI_ID_HWMON_VOLTAGE_BASE + 3
        self.EAPI_ID_HWMON_VOLTAGE_5V = self.EAPI_ID_HWMON_VOLTAGE_BASE + 4
        self.EAPI_ID_HWMON_VOLTAGE_12V = self.EAPI_ID_HWMON_VOLTAGE_BASE + 5
        self.EAPI_ID_HWMON_VOLTAGE_5VSB = self.EAPI_ID_HWMON_VOLTAGE_BASE + 6
        self.EAPI_ID_HWMON_VOLTAGE_3VSB = self.EAPI_ID_HWMON_VOLTAGE_BASE + 7
        self.EAPI_ID_HWMON_VOLTAGE_VBAT = self.EAPI_ID_HWMON_VOLTAGE_BASE + 8
        self.EAPI_ID_HWMON_VOLTAGE_5NV = self.EAPI_ID_HWMON_VOLTAGE_BASE + 9
        self.EAPI_ID_HWMON_VOLTAGE_12NV = self.EAPI_ID_HWMON_VOLTAGE_BASE + 10
        self.EAPI_ID_HWMON_VOLTAGE_VTT = self.EAPI_ID_HWMON_VOLTAGE_BASE + 11
        self.EAPI_ID_HWMON_VOLTAGE_24V = self.EAPI_ID_HWMON_VOLTAGE_BASE + 12
        self.EAPI_ID_HWMON_VOLTAGE_DC = self.EAPI_ID_HWMON_VOLTAGE_BASE + 13
        self.EAPI_ID_HWMON_VOLTAGE_DCSTBY = self.EAPI_ID_HWMON_VOLTAGE_BASE + 14
        self.EAPI_ID_HWMON_VOLTAGE_VBATLI = self.EAPI_ID_HWMON_VOLTAGE_BASE + 15
        self.EAPI_ID_HWMON_VOLTAGE_OEM0 = self.EAPI_ID_HWMON_VOLTAGE_BASE + 16
        self.EAPI_ID_HWMON_VOLTAGE_OEM1 = self.EAPI_ID_HWMON_VOLTAGE_BASE + 17
        self.EAPI_ID_HWMON_VOLTAGE_OEM2 = self.EAPI_ID_HWMON_VOLTAGE_BASE + 18
        self.EAPI_ID_HWMON_VOLTAGE_OEM3 = self.EAPI_ID_HWMON_VOLTAGE_BASE + 19
        self.EAPI_ID_HWMON_VOLTAGE_1V05 = self.EAPI_ID_HWMON_VOLTAGE_BASE + 20
        self.EAPI_ID_HWMON_VOLTAGE_1V5 = self.EAPI_ID_HWMON_VOLTAGE_BASE + 21
        self.EAPI_ID_HWMON_VOLTAGE_1V8 = self.EAPI_ID_HWMON_VOLTAGE_BASE + 22
        self.EAPI_ID_HWMON_VOLTAGE_DC2 = self.EAPI_ID_HWMON_VOLTAGE_BASE + 23
        self.EAPI_ID_HWMON_VOLTAGE_VIN = self.EAPI_ID_HWMON_VOLTAGE_BASE + 24

        self.EAPI_ID_HWMON_FAN_MAX = 10
        self.EAPI_ID_HWMON_FAN_BASE = 0x00052000
        self.EAPI_ID_HWMON_FAN_CPU = self.EAPI_ID_HWMON_FAN_BASE + 0
        self.EAPI_ID_HWMON_FAN_SYSTEM = self.EAPI_ID_HWMON_FAN_BASE + 1
        self.EAPI_ID_HWMON_FAN_CPU2 = self.EAPI_ID_HWMON_FAN_BASE + 2
        self.EAPI_ID_HWMON_FAN_OEM0 = self.EAPI_ID_HWMON_FAN_BASE + 3
        self.EAPI_ID_HWMON_FAN_OEM1 = self.EAPI_ID_HWMON_FAN_BASE + 4
        self.EAPI_ID_HWMON_FAN_OEM2 = self.EAPI_ID_HWMON_FAN_BASE + 5
        self.EAPI_ID_HWMON_FAN_OEM3 = self.EAPI_ID_HWMON_FAN_BASE + 6
        self.EAPI_ID_HWMON_FAN_OEM4 = self.EAPI_ID_HWMON_FAN_BASE + 7
        self.EAPI_ID_HWMON_FAN_OEM5 = self.EAPI_ID_HWMON_FAN_BASE + 8
        self.EAPI_ID_HWMON_FAN_OEM6 = self.EAPI_ID_HWMON_FAN_BASE + 9

        self.EAPI_ID_HWMON_CURRENT_MAX = 3
        self.EAPI_ID_HWMON_CURRENT_BASE = 0x00053000
        self.EAPI_ID_HWMON_CURRENT_OEM0 = self.EAPI_ID_HWMON_CURRENT_BASE + 0
        self.EAPI_ID_HWMON_CURRENT_OEM1 = self.EAPI_ID_HWMON_CURRENT_BASE + 1
        self.EAPI_ID_HWMON_CURRENT_OEM2 = self.EAPI_ID_HWMON_CURRENT_BASE + 2

        self.EAPI_ID_HWMON_POWER_MAX = 1
        self.EAPI_ID_HWMON_POWER_BASE = 0x00054000
        self.EAPI_ID_HWMON_POWER_OEM0 = self.EAPI_ID_HWMON_POWER_BASE + 0

        self.EAPI_ID_HWMON_MAX = self.EAPI_ID_HWMON_VOLTAGE_MAX

        self.EAPI_KELVINS_OFFSET = 2731
        self.EAPI_ENCODE_CELCIUS = lambda Celsius: (
            (Celsius) * 10) + self.EAPI_KELVINS_OFFSET
        self.EAPI_DECODE_CELCIUS = lambda Kelvins: (
            (Kelvins) - self.EAPI_KELVINS_OFFSET) / 10
        self.EAPI_DECODE_HWMON_VALUE = lambda RawValue: RawValue / 1000
        self.EAPI_CELCIUS_TO_FAHRENHEIT = lambda Celsius: 32 + \
            (Celsius * 9 / 5)

        self.EAPI_ID_CAP_MAX = 12
        self.EAPI_ID_CAP_BASE = 0x00060000
        self.EAPI_ID_CAP_HWMON = self.EAPI_ID_CAP_BASE + 0
        self.EAPI_ID_CAP_HWMON_TEMPERATURE = self.EAPI_ID_CAP_BASE + 1
        self.EAPI_ID_CAP_HWMON_VOLTAGE = self.EAPI_ID_CAP_BASE + 2
        self.EAPI_ID_CAP_HWMON_FAN = self.EAPI_ID_CAP_BASE + 3
        self.EAPI_ID_CAP_HWMON_CURRENT = self.EAPI_ID_CAP_BASE + 4
        self.EAPI_ID_CAP_HWMON_POWER = self.EAPI_ID_CAP_BASE + 5
        self.EAPI_ID_CAP_GPIO = self.EAPI_ID_CAP_BASE + 6
        self.EAPI_ID_CAP_GPIO_COUNT = self.EAPI_ID_CAP_BASE + 7
        self.EAPI_ID_CAP_GPIO_INTERRUPT = self.EAPI_ID_CAP_BASE + 8
        self.EAPI_ID_CAP_BRIGHTNESS = self.EAPI_ID_CAP_BASE + 9
        self.EAPI_ID_CAP_WDOG = self.EAPI_ID_CAP_BASE + 10
        self.EAPI_ID_CAP_ETP = self.EAPI_ID_CAP_BASE + 11

        self.EAPI_ID_GPIO_MAX = 1
        self.EAPI_ID_GPIO_BASE = 0x00070000
        self.EAPI_ID_GPIO_POE_PINNUM = self.EAPI_ID_GPIO_BASE + 1

    def initialize(self):
        EApiStatus_t = ctypes.c_int
        EApiId_t = ctypes.c_int

        prototype = ctypes.CFUNCTYPE(
            EApiStatus_t,           # 返回類型
            EApiId_t,               # 參數 1: EApiId_t
            ctypes.POINTER(ctypes.c_char),   # 參數 2: char *pValue
            ctypes.POINTER(ctypes.c_uint32)  # 參數 3: uint32_t *pBufLen
        )
        self.EApiBoardGetStringA = prototype(
            ("EApiBoardGetStringA", self.e_api_library))

        prototype = ctypes.CFUNCTYPE(
            EApiStatus_t,
            EApiId_t,
            ctypes.POINTER(ctypes.c_uint32),
        )
        self.EApiBoardGetValue = prototype(
            ("EApiBoardGetValue", self.e_api_library))

        prototype = ctypes.CFUNCTYPE(
            EApiStatus_t,
        )
        self.EApiBoardGetValue = prototype(
            ("EApiLibInitialize", self.e_api_library))

        prototype = ctypes.CFUNCTYPE(
            EApiStatus_t,
            EApiId_t,
            ctypes.c_uint32,
            ctypes.POINTER(ctypes.c_uint32),
        )
        self.EApiLibInitialize = prototype(
            ("EApiGPIOGetLevel", self.e_api_library))
        
    def get_board_string_data(self, id_number):
        # 緩衝區大小和初始化
        buf_len = 100
        pValue = ctypes.create_string_buffer(0)  # 創建一個字符緩衝區
        pBufLen = ctypes.c_uint32(0)  # 創建緩衝區長度

        # 調用函數
        status = self.EApiBoardGetStringA(
            id_number, pValue, ctypes.byref(pBufLen))

        if status == 0:  # 假設 0 是成功的狀態碼
            return pValue.value.decode("utf-8")
        else:
            print("eeeeeeeeeeeeeerror", status)
            return None

    def get_board_value_data(self, id_number):
        pValue = ctypes.c_uint32(0)

        # 調用函數
        print("555555555", id_number)
        status = self.e_api_library.EApiBoardGetValue(
            id_number, ctypes.byref(pValue))

        if status == 0:  # 假設 0 是成功的狀態碼
            return pValue.value
        else:
            print("eeeeeeeeeeeeeerror", status)
            return None

    def initial_EApiLibrary(self):
        return self.e_api_library.EApiLibInitialize()

    def get_gpio_level(self,id):
        buf_len=100
        pLevel = ctypes.c_uint32(buf_len)  # 創建緩衝區長度
        self.e_api_library.EApiGPIOGetLevel()