import ctypes
import json
import sys
import os
import platform


class SusiIot:
    def __init__(self):
        self.susi_iot_library = None
        self.json_library = None
        self.susi_iot_library_status = None
        self.json_max_indent = 0x1F
        self.json_preserve_order = 0x100
        self.susi_information = None
        self.susi_id_name_table = {}
        self.gpio_list = []
        self.memory_list = []

        self.import_library()
        self.initialize()
        self.create_name_id_list()

    def __del__(self):
        try:
            # self.susi_iot_library.SusiIoTUninitialize()
            pass
        except:
            pass

    def create_name_id_list(self):
        data_sort = "Platform Information"
        try:
            id_value = self.susi_information[data_sort]["id"]
            self.susi_id_name_table.update({data_sort: id_value})
            for item in self.susi_information[data_sort]["e"]:
                self.susi_id_name_table.update({item["n"]: item["id"]})
        except:
            pass

        data_sort = "Hardware Monitor"
        try:
            id_value = self.susi_information[data_sort]["id"]
            self.susi_id_name_table.update({data_sort: id_value})
            for item in self.susi_information[data_sort]:
                if "id" in item or "bn" in item:
                    pass
                else:
                    sources = self.susi_information[data_sort][item]['e']
                    for source in sources:
                        self.susi_id_name_table.update(
                            {item+" "+source["n"]: source["id"]})
        except:
            pass

        data_sort = "GPIO"
        try:
            id_value = self.susi_information[data_sort]["id"]
            self.susi_id_name_table.update({data_sort: id_value})
            for data_index in self.susi_information[data_sort].keys():
                if "GPIO" in data_index:
                    self.susi_id_name_table.update(
                        {data_index: self.susi_information[data_sort][data_index]["id"]})
                    for informations in self.susi_information[data_sort][data_index]["e"]:
                        self.susi_id_name_table.update(
                            {data_index+" "+informations["n"]: informations["id"]})
        except:
            pass

        data_sort = "SDRAM"
        try:
            id_value = self.susi_information[data_sort]["id"]
            self.susi_id_name_table.update({data_sort: id_value})
            for data_index in self.susi_information[data_sort].keys():
                if "SDRAM" in data_index:
                    self.susi_id_name_table.update(
                        {data_index: self.susi_information[data_sort][data_index]["id"]})
                    for informations in self.susi_information[data_sort][data_index]["e"]:
                        self.susi_id_name_table.update(
                            {data_index+" "+informations["n"]: informations["id"]})
        except:
            pass

        data_sort = "DiskInfo"
        try:
            id_value = self.susi_information[data_sort]["id"]
            self.susi_id_name_table.update({data_sort: id_value})
            for data_index in self.susi_information[data_sort]["e"]:
                self.susi_id_name_table.update(
                    {data_index["n"]: data_index["id"]})
        except:
            pass

        data_sort = "SUSIIoT Information"
        try:
            id_value = self.susi_information[data_sort]["id"]
            self.susi_id_name_table.update({data_sort: id_value})
            for data_index in self.susi_information[data_sort]["e"]:
                self.susi_id_name_table.update(
                    {data_index["n"]: data_index["id"]})
        except:
            pass

        data_sort = "M2Talk"
        try:
            id_value = self.susi_information[data_sort]["id"]
            self.susi_id_name_table.update({data_sort: id_value})
            for data_index in self.susi_information[data_sort].keys():
                if "Device" in data_index:
                    sources = self.susi_information[data_sort][data_index]['e']
                    for source in sources:
                        self.susi_id_name_table.update(
                            {data_sort+" "+source['n']: source['id']})
        except:
            pass

        data_sort = "Backlight"
        try:
            id_value = self.susi_information[data_sort]["id"]
            self.susi_id_name_table.update({data_sort: id_value})
            for data_index in self.susi_information[data_sort].keys():
                if "Backlight" in data_index:
                    sources = self.susi_information[data_sort][data_index]['e']
                    for source in sources:
                        self.susi_id_name_table.update(
                            {data_sort+" "+source['n']: source['id']})
        except:
            pass

    def import_library(self):
        current_dir = os.path.dirname(os.path.realpath(__file__))+"/"
        architecture = platform.machine()
        os_name = platform.system()
        susi_iot_library_path = ""
        json_library_path = ""

        if os_name == "Linux" and 'x86' in architecture.lower():
            susi_iot_library_path = current_dir+"libSusiIoT.x86.so"
            json_library_path = current_dir+"libjansson.x86.so"

        elif os_name == "Linux" and 'aarch64' in architecture.lower():
            susi_iot_library_path = current_dir+"libSusiIoT.arm.so"
            json_library_path = current_dir+"libjansson.arm.so"

        elif os_name == "Windows" and 'x86' in architecture.lower():
            pass

        elif os_name == "Windows" and 'aarch64' in architecture.lower():
            pass

        else:
            print(
                f"disable to import library, architechture:{architecture.lower()}, os:{os_name}")

        self.susi_iot_library = ctypes.CDLL(susi_iot_library_path)
        self.json_library = ctypes.CDLL(json_library_path)

    def initialize(self):
        try:
            if not self.check_root_authorization():
                print("check_root_authorizationcheck_root_authorization")
        except PermissionError as e:
            print(f"Error: {e}")
            exit(1)

        self.susi_iot_library.SusiIoTInitialize.restype = ctypes.c_int

        self.susi_iot_library.SusiIoTSetValue.argtypes = [
            ctypes.c_uint32, ctypes.POINTER(JsonT)]
        self.susi_iot_library.SusiIoTSetValue.restype = ctypes.c_uint32

        self.susi_iot_library.SusiIoTGetLoggerPath.restype = ctypes.c_char_p

        self.susi_iot_library.SusiIoTGetPFDataString.restype = ctypes.c_char_p
        self.susi_iot_library.SusiIoTGetPFDataString.argtypes = [
            ctypes.c_uint32]

        self.susi_iot_library.SusiIoTGetPFDataStringByUri.restype = ctypes.c_char_p
        self.susi_iot_library.SusiIoTGetPFDataStringByUri.argtypes = [
            ctypes.c_char_p]

        self.json_library.json_dumps.restype = ctypes.c_char_p
        self.json_library.json_integer.restype = ctypes.POINTER(JsonT)

        self.json_library.json_real.restype = ctypes.POINTER(JsonT)
        self.json_library.json_string.restype = ctypes.POINTER(JsonT)

        self.susi_iot_library_status = self.susi_iot_library.SusiIoTInitialize()

        jsonObject = self.json_library.json_object()
        if self.susi_iot_library.SusiIoTGetPFCapability(jsonObject) != 0:
            self.susi_information = "SusiIoTGetPFCapability failed."
            exit(1)
        else:
            self.susi_json_t = self.json_library.json_dumps(jsonObject, self.get_json_indent(
                4) | self.json_max_indent | self.get_json_real_precision(10))
            self.susi_information = self.turn_byte_to_json(self.susi_json_t)

        for key in self.susi_information["GPIO"].keys():
            if "GPIO" in key:
                self.gpio_list.append(key)
        for key in self.susi_information["SDRAM"].keys():
            if "SDRAM" in key:
                self.memory_list.append(key)

    def check_root_authorization(self):
        if os.geteuid() != 0:
            raise PermissionError(
                "Please run this program with root authorization (sudo).")
        else:
            return True

    def get_json_indent(self, n):
        return n & self.json_max_indent

    def get_json_real_precision(self, n):
        return ((n & 0x1F) << 11)

    def turn_byte_to_json(self, json_bytes):
        json_str = json_bytes.decode('utf-8')
        data = json.loads(json_str)
        return data

    def get_susi_information(self):
        return self.susi_information

    def get_susi_json_t(self):
        return self.susi_json_t

    def get_data_by_id(self, device_id):
        result = self.susi_iot_library.SusiIoTGetPFDataString(device_id)
        return self.turn_byte_to_json(result)

    def get_data_by_uri(self, uri):
        result = self.susi_iot_library.SusiIoTGetPFDataStringByUri(
            uri.encode('utf-8'))
        return result.decode('utf-8')

    def get_log_path(self):
        return self.susi_iot_library.SusiIoTGetLoggerPath().decode()

    def get_json_format_data(self, data):
        result = None
        if isinstance(data, int):
            self.json_library.json_integer.argtypes = [ctypes.c_int]
            result_ptr = self.json_library.json_integer(0)
            result = result_ptr.contents
        elif isinstance(data, float):
            self.json_library.json_integer.argtypes = [ctypes.c_double]
            result_ptr = self.json_library.json_real(ctypes.c_double(data))
            result = result_ptr.contents
        elif isinstance(data, str):
            self.json_library.json_string.argtypes = [ctypes.c_char_p]
            result_ptr = self.json_library.json_string(
                ctypes.c_char_p("".encode("utf-8")))
            result = result_ptr.contents

        else:
            print(f"type {type(data)} is not support")
        return result

    def set_value(self, device_id, value):
        result_ptr = self.json_library.json_integer(value)
        result = result_ptr.contents
        return self.susi_iot_library.SusiIoTSetValue(device_id, result)

    @property
    def boot_up_times(self):
        try:
            id_number = self.susi_id_name_table["Boot up times"]
            return self.get_data_by_id(id_number)["v"]
        except:
            return None

    @property
    def running_time_in_hours(self):
        try:
            id_number = self.susi_id_name_table["Running time (hours)"]
            return self.get_data_by_id(id_number)["v"]
        except:
            return None

    @property
    def board_name(self):
        try:
            id_number = self.susi_id_name_table["Board name"]
            return self.get_data_by_id(id_number)["sv"]
        except:
            return None

    @property
    def bios_revision(self):
        try:
            id_number = self.susi_id_name_table["BIOS revision"]
            return self.get_data_by_id(id_number)["sv"]
        except:
            return None

    @property
    def firmware_name(self):
        try:
            id_number = self.susi_id_name_table["Firmware Name"]
            return self.get_data_by_id(id_number)["sv"]
        except:
            return None

    @property
    def driver_version(self):
        try:
            id_number = self.susi_id_name_table["Driver version"]
            return self.get_data_by_id(id_number)["sv"]
        except:
            return None

    @property
    def firmware_version(self):
        try:
            id_number = self.susi_id_name_table["Firmware version"]
            return self.get_data_by_id(id_number)["sv"]
        except:
            return None

    @property
    def gpio_counter(self):
        pass

    def get_gpio_direction(self, gpio_number=0):
        try:
            gpio_string = self.gpio_list[gpio_number]
            id_number=self.susi_information["GPIO"][gpio_string]["e"][0]["id"]
            return self.get_data_by_id(id_number)['bv']
        except:
            return None

    def set_gpio_direction(self, gpio_number=0,level=0):
        try:
            gpio_string = self.gpio_list[gpio_number]
            id_number=self.susi_information["GPIO"][gpio_string]["e"][0]["id"]
            self.set_value(id_number,level)
            return True
        except:
            return None
    
    def get_gpio_level(self, gpio_number=0):
        try:
            gpio_string = self.gpio_list[gpio_number]
            id_number=self.susi_information["GPIO"][gpio_string]["e"][1]["id"]
            print(id_number)
            return self.get_data_by_id(id_number)['bv']
        except:
            return None

    def set_gpio_level(self, gpio_number=0,level=0):
        try:
            gpio_string = self.gpio_list[gpio_number]
            id_number=self.susi_information["GPIO"][gpio_string]["e"][1]["id"]
            print(id_number)
            self.set_value(id_number,level)
            return True
        except:
            return None

    

    @property
    def memory_count(self):
        pass

    @property
    def memory_type(self, memory_number=0):
        pass

    @property
    def module_type(self, memory_number=0):
        pass

    @property
    def module_size_in_GB(self, memory_number=0):
        pass

    @property
    def memory_speed(self, memory_number=0):
        pass

    @property
    def memory_rank(self, memory_number=0):
        pass

    @property
    def memory_voltage(self, memory_number=0):
        pass

    @property
    def memory_bank(self, memory_number=0):
        pass

    @property
    def memory_week_year(self, memory_number=0):
        pass

    @property
    def memory_temperature(self, memory_number=0):
        pass

    @property
    def disk_total_disk_space(self):
        try:
            id_number = self.susi_id_name_table["Disk - Total Disk Space"]
            return self.get_data_by_id(id_number)["v"]
        except:
            return None

    @property
    def disk_free_disk_space(self):
        try:
            id_number = self.susi_id_name_table["Disk - Free Disk Space"]
            return self.get_data_by_id(id_number)["v"]
        except:
            return None

    @property
    def disk_media_recovery_total_disk_space(self):
        try:
            id_number = self.susi_id_name_table["Disk -media-recovery Total Disk Space"]
            return self.get_data_by_id(id_number)["v"]
        except:
            return None

    @property
    def disk_media_recovery_free_disk_space(self):
        try:
            id_number = self.susi_id_name_table["Disk -media-recovery Free Disk Space"]
            return self.get_data_by_id(id_number)["v"]
        except:
            return None

    @property
    def disk_home_total_disk_space(self):
        try:
            id_number = self.susi_id_name_table["Disk -home Total Disk Space"]
            return self.get_data_by_id(id_number)["v"]
        except:
            return None

    @property
    def disk_free_disk_space(self):
        try:
            id_number = self.susi_id_name_table["Disk -home Free Disk Space"]
            return self.get_data_by_id(id_number)["v"]
        except:
            return None

    @property
    def voltage_vcore(self):
        try:
            id_number = self.susi_id_name_table["Voltage Vcore"]
            return self.get_data_by_id(id_number)["v"]
        except:
            return None

    @property
    def voltage_3p3v_standby(self):
        try:
            id_number = self.susi_id_name_table["Voltage 3.3V"]
            return self.get_data_by_id(id_number)["v"]
        except:
            return None

    @property
    def voltage_5v(self):
        try:
            id_number = self.susi_id_name_table["Voltage 5V"]
            return self.get_data_by_id(id_number)["v"]
        except:
            return None

    @property
    def voltage_12v(self):
        try:
            id_number = self.susi_id_name_table["Voltage 12V"]
            return self.get_data_by_id(id_number)["v"]
        except:
            return None

    @property
    def voltage_5v_standby(self):
        try:
            id_number = self.susi_id_name_table["Voltage 5V Standby"]
            return self.get_data_by_id(id_number)["v"]
        except:
            return None

    @property
    def voltage_cmos_battery(self):
        try:
            id_number = self.susi_id_name_table["Voltage CMOS Battery"]
            return self.get_data_by_id(id_number)["v"]
        except:
            return None

    @property
    def dc_power(self):
        try:
            id_number = self.susi_id_name_table["Voltage DC"]
            return self.get_data_by_id(id_number)["v"]
        except:
            return None

    @property
    def cpu_temperature_in_celsius(self):
        try:
            id_number = self.susi_id_name_table["Temperature System"]
            return self.get_data_by_id(id_number)["v"]
        except:
            return None

    @property
    def system_temperature_in_celsius(self):
        try:
            id_number = self.susi_id_name_table["Temperature System"]
            return self.get_data_by_id(id_number)["v"]
        except:
            return None

    @property
    def cpu_fan_speed(self):
        try:
            id_number = self.susi_id_name_table["Fan Speed CPU"]
            return self.get_data_by_id(id_number)["v"]
        except:
            return None

    @property
    def system_fan_speed(self):
        try:
            id_number = self.susi_id_name_table["Fan Speed System"]
            return self.get_data_by_id(id_number)["v"]
        except:
            return None

    @property
    def susiiot_version(self):
        try:
            id_number = self.susi_id_name_table["version"]
            return self.get_data_by_id(id_number)["sv"]
        except:
            return None

    @property
    def backlight_frequency(self):
        try:
            id_number = self.susi_id_name_table["Backlight frequency"]
            return self.get_data_by_id(id_number)["v"]
        except:
            return None

    @property
    def backlight_polarity(self):
        try:
            id_number = self.susi_id_name_table["Backlight polarity"]
            return self.get_data_by_id(id_number)["v"]
        except:
            return None

    @property
    def backlight_backlight(self):
        try:
            id_number = self.susi_id_name_table["Backlight backlight"]
            return self.get_data_by_id(id_number)["v"]
        except:
            return None

    @property
    def backlight_brightness(self):
        try:
            id_number = self.susi_id_name_table["Backlight brightness"]
            return self.get_data_by_id(id_number)["v"]
        except:
            return None


class JsonType:
    JSON_OBJECT = 0
    JSON_ARRAY = 1
    JSON_STRING = 2
    JSON_INTEGER = 3
    JSON_REAL = 4
    JSON_TRUE = 5
    JSON_FALSE = 6
    JSON_NULL = 7


class JsonT(ctypes.Structure):
    _fields_ = [
        ("type", ctypes.c_int),
        ("refcount", ctypes.c_size_t)
    ]
