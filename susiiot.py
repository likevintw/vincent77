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

        self.import_library()
        self.initialize()

    def __del__(self):
        try:
            self.susi_iot_library.SusiIoTUninitialize()
        except:
            pass

    def import_library(self):
        current_dir = os.path.dirname(os.path.realpath(__file__))+"/"
        architecture = platform.machine()
        os_name = platform.system()

        if os_name == "Linux" and 'x86' in architecture.lower():
            susi_iot_library_path = current_dir+"libSusiIoT.x86.so"
            json_library_path = current_dir+"libjansson.x86.so"

        elif os_name == "Linux" and 'arm' in architecture.lower():
            susi_iot_library_path = current_dir+"libSusiIoT.arm.so"
            json_library_path = current_dir+"libjansson.4.arm.so"

        elif os_name == "Windows" and 'x86' in architecture.lower():
            pass

        elif os_name == "Windows" and 'arm' in architecture.lower():
            pass

        else:
            print(f"disable to import library, architechture:{architecture.lower()}, os:{os_name}")

        self.susi_iot_library = ctypes.CDLL(susi_iot_library_path)
        self.json_library = ctypes.CDLL(json_library_path)

    def initialize(self):
        try:
            if not self.check_root_authorization():
                pass
        except PermissionError as e:
            print(f"Error: {e}")
            exit(1)
        self.susi_iot_library.SusiIoTInitialize.restype = ctypes.c_int
        self.susi_iot_library.SusiIoTGetPFCapabilityString.restype = ctypes.c_char_p
        self.susi_iot_library.SusiIoTGetPFData.argtypes = [
            ctypes.c_uint32, ctypes.POINTER(JsonT)]
        self.susi_iot_library.SusiIoTGetPFData.restype = ctypes.c_uint32

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
        else:
            self.susi_json_t = self.json_library.json_dumps(jsonObject, self.get_json_indent(
                4) | self.json_max_indent | self.get_json_real_precision(10))
            self.susi_information = self.turn_byte_to_json(self.susi_json_t)

        self.id_list = self.extract_ids(self.susi_information)

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
        uri = "SUSIIoT Information"
        result = self.susi_iot_library.SusiIoTGetPFDataStringByUri(
            uri.encode('utf-8'))
        print(result.decode('utf-8'))

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
        # SusiIoTSetValue
        pass


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
