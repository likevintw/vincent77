

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
# exec_by_menu
def execute_by_menu(susi_iot_lib,library_json):
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
        print("buffer ",buffer)
    print(jsonObject)

if __name__ == "__main__":
    argv = sys.argv

    susi_iot_lib = ctypes.CDLL("libSusiIoT.so")
    library_json=ctypes.CDLL("libjansson.so.4")

    susi_iot_lib.SusiIoTInitialize.restype = ctypes.c_int
    library_json.json_dumps.restype = ctypes.c_char_p

    status = susi_iot_lib.SusiIoTInitialize()
    if status != 0:
        print("Initialization failed.")
    else:
        print("Initialization successful.")

    susi_iot_lib.SusiIoTSetPFEventHandler()

    execute_by_menu(susi_iot_lib,library_json)

    susi_iot_lib.SusiIoTUninitialize()