import ctypes
import json
import sys
import os



class SusiIot:
    def __init__(self, susi_iot_library_path="libSusiIoT.so",
                 json_library_path="libjansson.so.4"):
        self.susi_iot_library = ctypes.CDLL(susi_iot_library_path)
        self.json_library = ctypes.CDLL(json_library_path)
        self.susi_iot_library_status = None
        self.id_list = None
        self.json_max_indent = 0x1F
        self.json_preserve_order = 0x100
        self.susi_information = None
        self.initialize()

    def initialize(self):
        try:
            if not self.check_root_authorization():
                pass
        except PermissionError as e:
            print(f"Error: {e}")
            exit(1)
        self.susi_iot_library.SusiIoTInitialize.restype = ctypes.c_int
        self.susi_iot_library.SusiIoTGetPFCapabilityString.restype = ctypes.c_char_p
        self.susi_iot_library.SusiIoTGetPFDataString.restype = ctypes.c_char_p
        self.susi_iot_library.SusiIoTGetPFDataString.argtypes = [
            ctypes.c_uint32]
        self.susi_iot_library.SusiIoTGetPFDataStringByUri.restype = ctypes.c_char_p
        self.susi_iot_library.SusiIoTGetPFDataStringByUri.argtypes = [
            ctypes.c_char_p]
        self.json_library.json_dumps.restype = ctypes.c_char_p

        self.susi_iot_library_status = self.susi_iot_library.SusiIoTInitialize()

        jsonObject = self.json_library.json_object()
        if self.susi_iot_library.SusiIoTGetPFCapability(jsonObject) != 0:
            self.susi_information = "SusiIoTGetPFCapability failed."
        else:
            self.susi_json_t = self.json_library.json_dumps(jsonObject, self.get_json_indent(
                4) | self.json_max_indent | self.get_json_real_precision(10))
            self.susi_information = self.turn_byte_to_json(self.susi_json_t)

        self.susi_iot_library.SusiIoTUninitialize()

        self.id_list = self.extract_ids(self.susi_information)

    def check_root_authorization(self):
        if os.geteuid() != 0:
            raise PermissionError("Please run this program with root authorization (sudo).")
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
        print("33333333333")
        result = self.susi_iot_library.SusiIoTGetPFDataString(int(device_id))
        print("444444")
        print(result)
        return self.turn_byte_to_json(result)

    def get_data_by_uri(self, uri):
        uri = "SUSIIoT Information"
        result = self.susi_iot_library.SusiIoTGetPFDataStringByUri(
            uri.encode('utf-8'))
        print(result.decode('utf-8'))
