


# Pass
sudo python3 -m unittest -v test_susiiot.TestHandler.test_get_susi_information
sudo python3 -m unittest -v test_susiiot.TestHandler.test_check_root_authorization
sudo python3 -m unittest -v test_susiiot.TestHandler.test_get_data_by_id
sudo python3 -m unittest -v test_susiiot.TestHandler.test_get_data_by_uri
sudo python3 -m unittest -v test_susiiot.TestHandler.test_get_log_path
sudo python3 -m unittest -v test_susiiot.TestHandler.test_get_id_list
sudo python3 -m unittest -v test_susiiot.TestHandler.test_get_json_format_data
sudo python3 -m unittest -v test_susiiot.TestHandler.test_get_system_temperature
sudo python3 -m unittest -v test_susiiot.TestHandler.test_get_id_dictionary
sudo python3 -m unittest -v test_susiiot.TestHandler.test_get_gpio_list

sudo python3 -m unittest -v test_platformsdk.TestHandler.test_get_board_string_data
sudo python3 -m unittest -v test_platformsdk.TestHandler.test_get_board_value_data
sudo python3 -m unittest -v test_platformsdk.TestHandler.test_initial_EApiLibrary
sudo python3 -m unittest -v test_platformsdk.TestHandler.test_check_table
sudo python3 -m unittest -v test_platformsdk.TestHandler.test_get_board_information
sudo python3 -m unittest -v test_platformsdk.TestHandler.test_get_available_memory
sudo python3 -m unittest -v test_platformsdk.TestHandler.test_get_disk_information
sudo python3 -m unittest -v test_platformsdk.TestHandler.test_get_led_id_list
sudo python3 -m unittest -v test_platformsdk.TestHandler.test_get_led_status
sudo python3 -m unittest -v test_platformsdk.TestHandler.test_set_led_status
sudo python3 -m unittest -v test_platformsdk.TestHandler.test_get_gpio_count
sudo python3 -m unittest -v test_platformsdk.TestHandler.test_get_gpio_direction
sudo python3 -m unittest -v test_platformsdk.TestHandler.test_get_gpio_capability
sudo python3 -m unittest -v test_platformsdk.TestHandler.test_get_gpio_level
sudo python3 -m unittest -v test_platformsdk.TestHandler.test_set_gpio_direction
sudo python3 -m unittest -v test_platformsdk.TestHandler.test_set_gpio_level
sudo python3 -m unittest -v test_platformsdk.TestHandler.test_get_watchdog_capaility
sudo python3 -m unittest -v test_platformsdk.TestHandler.test_get_storage_capability
sudo python3 -m unittest -v test_platformsdk.TestHandler.test_get_etp_device_data
sudo python3 -m unittest -v test_platformsdk.TestHandler.test_get_etp_user_data
sudo python3 -m unittest -v test_susiiot.TestCases.test_cpu_temperature_in_celsius

# Todo
export LOG_LEVEL=DEBUG && sudo -E python3 -m unittest -v test_susiiot.TestCases.test_backlight_polarity
export LOG_LEVEL=DEBUG && sudo -E python3 -m unittest -v test_susiiot.TestCases.test_system_temperature_in_celsius

export LOG_LEVEL=DEBUG && sudo -E python3 -m unittest -v test_susiiot.TestCases.test_set_gpio_level
sudo python3 -m unittest -v test_susiiot.TestCases.test_get_susi_information_string

git clone https://github.com/likevintw/vincent77.git && \
    cd vincent77 && \
    sudo python3 -m unittest -v test_susiiot.TestCases > "$(date +\%Y\%m\%d\%H\%M\%S)_result.txt"

sudo python3 -m unittest -v test_susiiot.TestMotherBoardInterface
sudo python3 -m unittest -v test_susiiot.TestCases.test_susi_id_name_table






