
import unittest
import susiiot
import os
import platform

current_dir = os.path.dirname(os.path.realpath(__file__))+"/"


class TestHandler(unittest.TestCase):
    def test_get_susi_information(self):
        handler = susiiot.SusiIot()
        results = handler.get_susi_information()
        print(results)
        print(handler.get_id_list())

    def test_get_id_list(self):
        handler = susiiot.SusiIot()
        results = handler.get_id_list()
        print(results)

    def test_get_data_by_id(self):
        handler = susiiot.SusiIot()
        id_list = handler.get_id_list()
        for device_id in id_list:
            print(handler.get_data_by_id(device_id))

    def test_get_data_by_uri(self):
        handler = susiiot.SusiIot()
        result = handler.get_data_by_uri("SUSIIoT Information")
        print(result)

    def test_check_root_authorization(self):
        handler = susiiot.SusiIot()
        results = handler.check_root_authorization()
        print(results)

    def test_get_log_path(self):
        handler = susiiot.SusiIot()
        results = handler.get_log_path()
        print(results)

    def test_get_json_format_data(self):
        handler = susiiot.SusiIot()
        results = handler.get_json_format_data(0)
        self.assertEqual(results.type, 3)
        results = handler.get_json_format_data(0.0)
        self.assertEqual(results.type, 4)
        results = handler.get_json_format_data("")
        print(results.type)


if __name__ == '__main__':
    unittest.main()
