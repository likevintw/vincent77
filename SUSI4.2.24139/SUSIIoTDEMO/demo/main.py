

import ctypes
import json



    

if __name__ == "__main__":
    library_path = "libSusiIoT.so"
    # 加載 .so 文件
    susi_iot_lib = ctypes.CDLL(library_path)
    susi_iot_lib.SusiIoTInitialize.restype = ctypes.c_int
    status = susi_iot_lib.SusiIoTInitialize()
    if status != 0:
        print("Initialization failed.")
    else:
        print("Initialization successful.")

