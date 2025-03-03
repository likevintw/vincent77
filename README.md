
# Requirement on Linux
```sh
apt update \
    apt install python3 python3-pip \
    apt install libjansson4
```
# Run Example
```sh
sudo python3 test_susiiot.py
```
```sh
sudo python3 -m unittest -v test_susiiot.py
```

## Todo
* remind user to run python with root authorization, sudo, ok

test on arm linux:
* test_get_data_by_uri, ok
* sudo python3 -m unittest -v test_susiiot, Segmentation fault, ok
-> self.susi_iot_library.SusiIoTUninitialize()