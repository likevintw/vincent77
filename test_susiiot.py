
import unittest
import susiiot


class TestHandler(unittest.TestCase):
    def test_get_susi_information(self):
        susi_iot_library_path="libSusiIoT.so"
        json_library_path="libjansson.so.4"
        handler = susiiot.SusiIot(susi_iot_library_path,json_library_path)
        results = handler.get_susi_information()
        print(results)
        print(handler.get_id_list())

    def test_get_id_list(self):
        susi_iot_library_path="libSusiIoT.so"
        json_library_path="libjansson.so.4"
        handler = susiiot.SusiIot(susi_iot_library_path,json_library_path)
        results = handler.get_id_list()
        print(results)

    def test_get_data_by_id(self):
        susi_iot_library_path="libSusiIoT.so"
        json_library_path="libjansson.so.4"
        handler = susiiot.SusiIot(susi_iot_library_path,json_library_path)
        id_list=handler.get_id_list()
        for device_id in id_list:
            print(handler.get_data_by_id(device_id))

    def test_get_data_by_uri(self):
        susi_iot_library_path="libSusiIoT.so"
        json_library_path="libjansson.so.4"
        handler = susiiot.SusiIot(susi_iot_library_path,json_library_path)
        result = handler.get_data_by_uri("SUSIIoT Information")
        print(result)

    def test_check_root_authorization(self):
        susi_iot_library_path="libSusiIoT.so"
        json_library_path="libjansson.so.4"
        handler = susiiot.SusiIot(susi_iot_library_path,json_library_path)
        results = handler.check_root_authorization()
        print(results)


if __name__ == '__main__':
    unittest.main()
