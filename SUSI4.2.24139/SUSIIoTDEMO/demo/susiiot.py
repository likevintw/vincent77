import ctypes
import json
import sys

JSON_MAX_INDENT = 0x1F
JSON_PRESERVE_ORDER= 0x100

class SusiIot:
    def __init__(self,susi_iot_library_path="libSusiIoT.so",json_library_path="libjansson.so.4"):
        self.susi_iot_library=ctypes.CDLL(susi_iot_library_path)
        self.json_library=ctypes.CDLL(json_library_path)
        self.susi_iot_library.SusiIoTInitialize.restype = ctypes.c_int
        self.json_library.json_dumps.restype = ctypes.c_char_p
        self.susi_iot_library.SusiIoTGetPFCapabilityString.restype = ctypes.c_char_p
        self.susi_iot_library_status = self.susi_iot_library.SusiIoTInitialize()
        self.susi_iot_library.SusiIoTSetPFEventHandler()
        jsonObject=self.json_library.json_object()
        if self.susi_iot_library.SusiIoTGetPFCapability(jsonObject) != 0:
                self.susi_information="SusiIoTGetPFCapability failed."
        else:
            buffer = self.json_library.json_dumps(jsonObject, self.json_indent(4) | JSON_PRESERVE_ORDER | self.json_real_precision(10))
            buffer=self.turn_byte_to_json(buffer)
            self.susi_information=buffer
        self.susi_iot_library.SusiIoTUninitialize()
        
    def get_susi_information(self):
        return self.susi_information
    
    def json_indent(self,n):
        return n & JSON_MAX_INDENT

    def json_real_precision(self,n):
        return ((n & 0x1F) << 11)

    def turn_byte_to_json(self,json_bytes ):
        json_str = json_bytes.decode('utf-8')
        data = json.loads(json_str)
        return data