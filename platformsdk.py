




class PlatformSDK:
    def __init__(self):
        self.e_api_library = None
        
        self.EAPI_ID_BOARD_MANUFACTURER_STR = 0
        self.EAPI_ID_BOARD_NAME_STR = 1
        self.EAPI_ID_BOARD_REVISION_STR = 2
        self.EAPI_ID_BOARD_SERIAL_STR = 3
        self.EAPI_ID_BOARD_BIOS_REVISION_STR = 4
        self.EAPI_ID_BOARD_HW_REVISION_STR = 5
        self.EAPI_ID_BOARD_PLATFORM_TYPE_STR = 6

        self.import_library()
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
            print(f"disable to import library, architechture:{architecture.lower()}, os:{os_name}")

        self.e_api_library = ctypes.CDLL(e_api_library_path)

    def initialize(self):
        self.e_api_library = None
