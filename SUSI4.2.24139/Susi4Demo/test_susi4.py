
import unittest
import susi4


class TestHandler(unittest.TestCase):
    def test_get_gpio_information(self):
        handler=susi4.Susi4()
        print(handler.get_gpio_information())

if __name__ == '__main__':
    unittest.main()
