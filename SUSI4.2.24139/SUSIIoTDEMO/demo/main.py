

import ctypes
import json
import sys


JSON_MAX_INDENT = 0x1F
JSON_PRESERVE_ORDER= 0x100

def json_indent(n):
    return n & JSON_MAX_INDENT

def json_real_precision(n):
    return ((n & 0x1F) << 11)

def turn_byte_to_json(json_bytes ):
    json_str = json_bytes.decode('utf-8')
    data = json.loads(json_str)
    return data

class SusiIot:
    def __init__(susi_iot_library_path="libSusiIoT.so",json_library_path="libjansson.so.4"):
        self.susi_iot_library=ctypes.CDLL(susi_iot_library_path)
        self.json_library=ctypes.CDLL(json_library_path)
        self.susi_iot_library.SusiIoTInitialize.restype = ctypes.c_int
        self.json_library.json_dumps.restype = ctypes.c_char_p
        self.susi_iot_library.SusiIoTGetPFCapabilityString.restype = ctypes.c_char_p
        self.susi_iot_library_status = self.susi_iot_library.SusiIoTInitialize()
        self.susi_iot_library.SusiIoTSetPFEventHandler()
        jsonObject=json_library.json_object()
        if self.susi_iot_lib.SusiIoTGetPFCapability(jsonObject) != 0:
                self.susi_information="SusiIoTGetPFCapability failed."
        else:
            buffer = library_json.json_dumps(jsonObject, json_indent(4) | JSON_PRESERVE_ORDER | json_real_precision(10))
            buffer=turn_byte_to_json(buffer)
            self.susi_information=buffer
        self.susi_iot_library.SusiIoTUninitialize()
        
    def get_susi_information():
        return self.susi_information

if __name__ == "__main__":
    argv = sys.argv

    susi_iot_lib = ctypes.CDLL("libSusiIoT.so")
    library_json=ctypes.CDLL("libjansson.so.4")

    susi_iot_lib.SusiIoTInitialize.restype = ctypes.c_int
    library_json.json_dumps.restype = ctypes.c_char_p
    susi_iot_lib.SusiIoTGetPFCapabilityString.restype = ctypes.c_char_p

    status = susi_iot_lib.SusiIoTInitialize()
    if status != 0:
        print("Initialization failed.")
    else:
        print("Initialization successful.")

    susi_iot_lib.SusiIoTSetPFEventHandler()

    # if(op == OPT_CAPABILITY_OBJECT)
    jsonObject=library_json.json_object()
    print(jsonObject)
    print( "4 ",json_indent(4))
    print( "20480 ",json_real_precision(10))
    if susi_iot_lib.SusiIoTGetPFCapability(jsonObject) != 0:
        print("SusiIoTGetPFCapability failed.")
    else:
        buffer = library_json.json_dumps(jsonObject, json_indent(4) | JSON_PRESERVE_ORDER | json_real_precision(10))
        buffer=turn_byte_to_json(buffer)
        print("json_dumps ",buffer)
    print(jsonObject)

    # else if(op == OPT_CAPABILITY_STRING)
    buffer=susi_iot_lib.SusiIoTGetPFCapabilityString()
    buffer=turn_byte_to_json(buffer)
    print("SusiIoTGetPFCapabilityString ",buffer)

    # else if(op == OPT_GET_DATA_OBJECT)
    jsonObject=library_json.json_object()

    susi_iot_lib.SusiIoTUninitialize()