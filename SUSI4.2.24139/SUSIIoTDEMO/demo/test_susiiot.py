
import unittest
import susiiot


class TestExcelHandler(unittest.TestCase):
    def test_get_susi_information(self):
        handler=susiiot.SusiIot()
        results=handler.get_susi_information()

        for result in results:
            print(result)

if __name__ == '__main__':
    unittest.main()
