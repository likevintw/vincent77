
import unittest
import susiiot


class TestHandler(unittest.TestCase):
    def test_get_susi_information(self):
        handler = susiiot.SusiIot()
        results = handler.get_susi_information()
        print(results)
        print(handler.get_id_list())

    def test_get_id_list(self):
        handler = susiiot.SusiIot()
        results = handler.get_susi_information()
        print(handler.get_id_list())

    def test_get_susi_json_t(self):
        handler = susiiot.SusiIot()
        results = handler.get_susi_information()
        print(handler.get_susi_json_t())

    @unittest.skip("todo")
    def test_get_data_by_id(self):
        handler = susiiot.SusiIot()
        identities = handler.get_id_list()
        print(identities)
        # for identity in identities:
        #     print(handler.get_data_by_id(identity))
        print(handler.get_data_by_id(257))

    @unittest.skip("todo")
    def test_get_data_by_uri(self):
        handler = susiiot.SusiIot()
        result = handler.get_data_by_uri("SUSIIoT Information")
        print(result)


if __name__ == '__main__':
    unittest.main()
