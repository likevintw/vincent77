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
        self.id_list = None
        self.json_max_indent = 0x1F
        self.json_preserve_order = 0x100
        self.susi_information = None
        self.susi_id_dictionary = {}
        self.import_library()
        self.initialize()
        self.id_list = self.extract_ids(self.susi_information)
        self.susi_id_dictionary = self.get_id_dictionary()

    def __del__(self):
        try:
            # self.susi_iot_library.SusiIoTUninitialize()
            pass
        except Exception as e:
            print(e)

    def import_library(self):
        current_dir = os.path.dirname(os.path.realpath(__file__))+"/"
        architecture = platform.machine()
        os_name = platform.system()

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
            print(f"disable to import library, architechture:{architecture.lower()}, os:{os_name}")
        
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
        self.susi_iot_library.SusiIoTGetPFCapabilityString.restype = ctypes.c_char_p
        self.susi_iot_library.SusiIoTGetPFData.argtypes = [
            ctypes.c_uint32, ctypes.POINTER(JsonT)]
        self.susi_iot_library.SusiIoTGetPFData.restype = ctypes.c_uint32
        self.susi_iot_library.SusiIoTSetValue.argtypes = [
            ctypes.c_uint32, ctypes.POINTER(JsonT)]
        self.susi_iot_library.SusiIoTSetValue.restype = ctypes.c_uint32

        self.susi_iot_library.SusiIoTGetPFDataString.restype = ctypes.c_char_p
        self.susi_iot_library.SusiIoTGetLoggerPath.restype = ctypes.c_char_p
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

    def extract_ids(self, data, id_list=None):
        if id_list is None:
            id_list = []

        if isinstance(data, dict):
            for key, value in data.items():
                if key == "id":
                    id_list.append(value)
                self.extract_ids(value, id_list)
        elif isinstance(data, list):
            for item in data:
                self.extract_ids(item, id_list)

        return id_list

    def get_susi_information(self):
        return self.susi_information

    def get_id_list(self):
        return self.id_list

    def get_susi_json_t(self):
        return self.susi_json_t

    def get_data_by_id(self, device_id):
        result = self.susi_iot_library.SusiIoTGetPFDataString(device_id)
        return self.turn_byte_to_json(result)

    def get_data_by_uri(self, uri):
        print(uri)
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

    def get_id_dictionary(self):
        if self.susi_id_dictionary == {}:
            id_list = self.get_id_list()
            for device_id in id_list:
                results = self.get_data_by_id(device_id)
                try:
                    self.susi_id_dictionary.update(
                        {results['n']: results['id']})
                except:
                    pass
        return self.susi_id_dictionary
    
    def get_boot_up_times(self):
        if 'Boot up times' in self.susi_id_dictionary:
            return self.get_data_by_id(self.susi_id_dictionary['Boot up times'])['v']
        else:
            return None
    def get_running_time_in_hours(self):
        if 'Running time' in self.susi_id_dictionary:
            return self.get_data_by_id(self.susi_id_dictionary['Running time'])['v']
        else:
            return None
    def get_board_name(self):
        if 'Board name' in self.susi_id_dictionary:
            return self.get_data_by_id(self.susi_id_dictionary['Board name'])['sv']
        else:
            return None
    def get_bios_revision(self):
        uri="BIOS revision"
        if uri in self.susi_id_dictionary:
            return self.get_data_by_id(self.susi_id_dictionary[uri])['sv']
        else:
            return None
    def get_firmware_name(self):
        uri="Firmware Name"
        if uri in self.susi_id_dictionary:
            return self.get_data_by_id(self.susi_id_dictionary[uri])['sv']
        else:
            return None
    def get_driver_version(self):
        uri="Driver version"
        if uri in self.susi_id_dictionary:
            return self.get_data_by_id(self.susi_id_dictionary[uri])['sv']
        else:
            return None
    def get_firmware_version(self):
        uri="Firmware version"
        if uri in self.susi_id_dictionary:
            return self.get_data_by_id(self.susi_id_dictionary[uri])['sv']
        else:
            return None
    
    def get_vcore(self):
        try:
            return self.susi_information["Hardware Monitor"]["Voltage"]["e"][0]["v"]
        except:
            return None
    def get_vcore_max(self):
        try:
            return self.susi_information["Hardware Monitor"]["Voltage"]["e"][0]["max"]
        except:
            return None
    def get_vcore_min(self):
        try:
            return self.susi_information["Hardware Monitor"]["Voltage"]["e"][0]["min"]
        except:
            return None
    def get_5v_standby(self):
        try:
            return self.susi_information["Hardware Monitor"]["Voltage"]["e"][1]["v"]
        except:
            return None
    def get_5v_standby_max(self):
        try:
            return self.susi_information["Hardware Monitor"]["Voltage"]["e"][1]["max"]
        except:
            return None
    def get_5v_standby_min(self):
        try:
            return self.susi_information["Hardware Monitor"]["Voltage"]["e"][1]["min"]
        except:
            return None
    def get_cmos_battery(self):
        try:
            return self.susi_information["Hardware Monitor"]["Voltage"]["e"][2]["v"]
        except:
            return None
    def get_cmos_battery_max(self):
        try:
            return self.susi_information["Hardware Monitor"]["Voltage"]["e"][2]["max"]
        except:
            return None
    def get_cmos_battery_min(self):
        try:
            return self.susi_information["Hardware Monitor"]["Voltage"]["e"][2]["min"]
        except:
            return None
    def get_dc_power(self):
        try:
            return self.susi_information["Hardware Monitor"]["Voltage"]["e"][3]["v"]
        except:
            return None
    def get_dc_power_max(self):
        try:
            return self.susi_information["Hardware Monitor"]["Voltage"]["e"][3]["max"]
        except:
            return None
    def get_dc_power_min(self):
        try:
            return self.susi_information["Hardware Monitor"]["Voltage"]["e"][3]["min"]
        except:
            return None

    def get_cpu_temperature_in_celsius(self):
        try:
            return self.susi_information["Hardware Monitor"]["Temperature"]["e"][0]["v"]
        except:
            return None
    def get_cpu_temperature_max_in_celsius(self):
        try:
            return self.susi_information["Hardware Monitor"]["Temperature"]["e"][0]["max"]
        except:
            return None
    def get_cpu_temperature_min_in_celsius(self):
        try:
            return self.susi_information["Hardware Monitor"]["Temperature"]["e"][0]["min"]
        except:
            return None
    def get_system_temperature_in_celsius(self):
        try:
            return self.susi_information["Hardware Monitor"]["Temperature"]["e"][1]["v"]
        except:
            return None
    def get_system_temperature_max_in_celsius(self):
        try:
            return self.susi_information["Hardware Monitor"]["Temperature"]["e"][1]["max"]
        except:
            return None
    def get_system_temperature_min_in_celsius(self):
        try:
            return self.susi_information["Hardware Monitor"]["Temperature"]["e"][1]["min"]
        except:
            return None
        
    def get_gpio_counter(self):
        counter=0
        for key in self.susi_information["GPIO"].keys():
            if "GPIO" in key:
                counter+=1
        return counter
    def get_gpio00_level(self):
        try:
            return self.susi_information["GPIO00"]["e"][1]["bv"]
        except:
            return None
    def get_gpio01_direction(self):
        try:
            return self.susi_information["GPIO01"]["e"][0]["bv"]
        except:
            return None
    def get_gpio01_level(self):
        try:
            return self.susi_information["GPIO01"]["e"][1]["bv"]
        except:
            return None
    def get_gpio02_direction(self):
        try:
            return self.susi_information["GPIO02"]["e"][0]["bv"]
        except:
            return None
    def get_gpio02_level(self):
        try:
            return self.susi_information["GPIO02"]["e"][1]["bv"]
        except:
            return None
    def get_gpio03_direction(self):
        try:
            return self.susi_information["GPIO03"]["e"][0]["bv"]
        except:
            return None
    def get_gpio03_level(self):
        try:
            return self.susi_information["GPIO03"]["e"][1]["bv"]
        except:
            return None
    def get_gpio04_direction(self):
        try:
            return self.susi_information["GPIO04"]["e"][0]["bv"]
        except:
            return None
    def get_gpio04_level(self):
        try:
            return self.susi_information["GPIO04"]["e"][1]["bv"]
        except:
            return None
    def get_gpio05_direction(self):
        try:
            return self.susi_information["GPIO05"]["e"][0]["bv"]
        except:
            return None
    def get_gpio05_level(self):
        try:
            return self.susi_information["GPIO05"]["e"][1]["bv"]
        except:
            return None
    def get_gpio06_direction(self):
        try:
            return self.susi_information["GPIO06"]["e"][0]["bv"]
        except:
            return None
    def get_gpio06_level(self):
        try:
            return self.susi_information["GPIO06"]["e"][1]["bv"]
        except:
            return None
    def get_gpio07_direction(self):
        try:
            return self.susi_information["GPIO07"]["e"][0]["bv"]
        except:
            return None
    def get_gpio07_level(self):
        try:
            return self.susi_information["GPIO07"]["e"][1]["bv"]
        except:
            return None


    def get_memory_type(self):
        uri="Memory Type"
        if uri in self.susi_id_dictionary:
            return self.get_data_by_id(self.susi_id_dictionary[uri])['sv']
        else:
            return None
    def get_module_type(self):
        uri="Module Type"
        if uri in self.susi_id_dictionary:
            return self.get_data_by_id(self.susi_id_dictionary[uri])['sv']
        else:
            return None
    def get_module_size_in_GB(self):
        uri="Module Size"
        if uri in self.susi_id_dictionary:
            return self.get_data_by_id(self.susi_id_dictionary[uri])['v']
        else:
            return None
    def get_memory_speed(self):
        uri="Memory Speed"
        if uri in self.susi_id_dictionary:
            return self.get_data_by_id(self.susi_id_dictionary[uri])['sv']
        else:
            return None
    def get_memory_rank(self):
        uri="Rank"
        if uri in self.susi_id_dictionary:
            return self.get_data_by_id(self.susi_id_dictionary[uri])['v']
        else:
            return None
    def get_SDRAM_voltage(self):
        pass
        # todo
    def get_memory_bank(self):
        uri="Bank"
        if uri in self.susi_id_dictionary:
            return self.get_data_by_id(self.susi_id_dictionary[uri])['sv']
        else:
            return None
    def get_memory_week_year(self):
        uri="Week Year"
        if uri in self.susi_id_dictionary:
            return self.get_data_by_id(self.susi_id_dictionary[uri])['sv']
        else:
            return None
    def get_memory_temperature(self):
        pass
        # todo


    def get_disk_total_disk_space(self):
        uri="Disk - Total Disk Space"
        if uri in self.susi_id_dictionary:
            return self.get_data_by_id(self.susi_id_dictionary[uri])['v']
        else:
            return None
    def get_disk_total_disk_space_max(self):
        uri="Disk - Total Disk Space"
        if uri in self.susi_id_dictionary:
            return self.get_data_by_id(self.susi_id_dictionary[uri])['max']
        else:
            return None
    def get_disk_total_disk_space_min(self):
        uri="Disk - Total Disk Space"
        if uri in self.susi_id_dictionary:
            return self.get_data_by_id(self.susi_id_dictionary[uri])['min']
        else:
            return None
    def get_disk_free_disk_space(self):
        uri="Disk - Free Disk Space"
        if uri in self.susi_id_dictionary:
            return self.get_data_by_id(self.susi_id_dictionary[uri])['v']
        else:
            return None
    def get_disk_free_disk_space_max(self):
        uri="Disk - Free Disk Space"
        if uri in self.susi_id_dictionary:
            return self.get_data_by_id(self.susi_id_dictionary[uri])['max']
        else:
            return None
    def get_disk_free_disk_space_min(self):
        uri="Disk - Free Disk Space"
        if uri in self.susi_id_dictionary:
            return self.get_data_by_id(self.susi_id_dictionary[uri])['min']
        else:
            return None
    def get_disk_media_recovery_total_disk_space(self):
        uri="Disk -media-recovery Total Disk Space"
        if uri in self.susi_id_dictionary:
            return self.get_data_by_id(self.susi_id_dictionary[uri])['v']
        else:
            return None
    def get_disk_media_recovery_total_disk_space_max(self):
        uri="Disk -media-recovery Total Disk Space"
        if uri in self.susi_id_dictionary:
            return self.get_data_by_id(self.susi_id_dictionary[uri])['max']
        else:
            return None
    def get_disk_media_recovery_total_disk_space_min(self):
        uri="Disk -media-recovery Total Disk Space"
        if uri in self.susi_id_dictionary:
            return self.get_data_by_id(self.susi_id_dictionary[uri])['min']
        else:
            return None
    def get_disk_media_recovery_free_disk_space(self):
        uri="Disk -media-recovery Free Disk Space"
        if uri in self.susi_id_dictionary:
            return self.get_data_by_id(self.susi_id_dictionary[uri])['v']
        else:
            return None
    def get_disk_media_recovery_free_disk_space_max(self):
        uri="Disk -media-recovery Free Disk Space"
        if uri in self.susi_id_dictionary:
            return self.get_data_by_id(self.susi_id_dictionary[uri])['max']
        else:
            return None
    def get_disk_media_recovery_free_disk_space_min(self):
        uri="Disk -media-recovery Free Disk Space"
        if uri in self.susi_id_dictionary:
            return self.get_data_by_id(self.susi_id_dictionary[uri])['min']
        else:
            return None
    def get_disk_home_total_disk_space(self):
        uri="Disk -home Total Disk Space"
        if uri in self.susi_id_dictionary:
            return self.get_data_by_id(self.susi_id_dictionary[uri])['v']
        else:
            return None
    def get_disk_home_total_disk_space_max(self):
        uri="Disk -home Total Disk Space"
        if uri in self.susi_id_dictionary:
            return self.get_data_by_id(self.susi_id_dictionary[uri])['max']
        else:
            return None
    def get_disk_home_total_disk_space_min(self):
        uri="Disk -home Total Disk Space"
        if uri in self.susi_id_dictionary:
            return self.get_data_by_id(self.susi_id_dictionary[uri])['min']
        else:
            return None     
    def get_disk_free_disk_space(self):
        uri="Disk -home Free Disk Space"
        if uri in self.susi_id_dictionary:
            return self.get_data_by_id(self.susi_id_dictionary[uri])['v']
        else:
            return None
    def get_disk_free_disk_space_max(self):
        uri="Disk -home Free Disk Space"
        if uri in self.susi_id_dictionary:
            return self.get_data_by_id(self.susi_id_dictionary[uri])['max']
        else:
            return None
    def get_disk_free_disk_space_min(self):
        uri="Disk -home Free Disk Space"
        if uri in self.susi_id_dictionary:
            return self.get_data_by_id(self.susi_id_dictionary[uri])['min']
        else:
            return None
        
    def get_susiiot_version(self):
        uri="version"
        if uri in self.susi_id_dictionary:
            return self.get_data_by_id(self.susi_id_dictionary[uri])['sv']
        else:
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
