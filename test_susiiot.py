
import unittest
import susiiot
import os
import platform


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
        result = handler.get_data_by_uri("Hardware Monitor")
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

    def test_get_system_temperature(self):
        handler = susiiot.SusiIot()
        result = handler.get_system_temperature()
        print(result)

    def test_get_id_dictionary(self):
        handler = susiiot.SusiIot()
        results = handler.get_id_dictionary()
        for key in results.keys():
            print(result)

    def test_set_gpio_01(self):
        handler = susiiot.SusiIot()
        result = handler.get_data_by_id(17039873)
        print(result)

    def test_set_value(self):
        handler = susiiot.SusiIot()
        result = handler.set_value(17039873, 0)
        result = handler.get_data_by_id(17039873)
        print(result)
        result = handler.set_value(17039873, 1)
        result = handler.get_data_by_id(17039873)
        print(result)


if __name__ == '__main__':
    unittest.main()
