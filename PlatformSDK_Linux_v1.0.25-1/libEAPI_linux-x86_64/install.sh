#!/bin/bash


## ANSI escape codes for colors
readonly cc_BOLD_GREEN="\033[1;32m"
readonly cc_YELLOW="\033[0;33m"
readonly cc_BOLD_YELLOW="\033[1;33m"
readonly cc_NC="\033[0m"    # No color

_commonfunc_print() {
    ### color output function
    #$1 color
    #$2 text
    echo -e ${1} "${2}" ${cc_NC}
}

CURRENT_DEV_NAME=`cat /sys/devices/virtual/dmi/id/product_name | awk -F "-" '{print $1"-"$2}'`

ARCH=`uname -i`
VERSION="1.0.21-1"

ATAUxIO_LIBNAME="libATAuxIO"
ATAUxIO_VERSION="0.0.9"

BoardResource_LIBNAME="libBoardResource"
BoardResource_VERSION="1.0.1"

EC_LIBNAME="libEAPI"
EC_VERSION="1.0.18"

GPIO_LIBNAME="libATGPIO"
GPIO_VERSION="0.0.3"

IPS_VLIBNAME="libEAPI-IPS"
IPS_VERSION="1.0.3"

ECGPIO_LIBNAME="libECGPIO"
ECGPIO_VERSION="1.0.3"

PACKAGE_NAME="libEAPI"
LIB=/usr/src/advantech/EAPI_*


DIR=`readlink -f $0`
BASEDIR=$(dirname $DIR)

mkdir -p /usr/src/advantech

# remove old driver
if [ -d /usr/src/advantech/${PACKAGE_NAME}* ]; then
	rm -rf /usr/src/advantech/${PACKAGE_NAME}*
        echo "Remove old folder. Copy files"
else
        echo "Copy files"
fi

sudo cp -rf ${BASEDIR}/${PACKAGE_NAME} /usr/src/advantech

# install libiio0
echo ""
echo "---check libiio-dev---"
if [ "x${ARCH}" = "xx86_64" ] || [ "x${ARCH}" = "xi686" ]; then
    dpkg -l "libiio-dev" 1>/dev/null 2>/dev/null
    if [ "1" = "$?" ]
    then
        _commonfunc_print ${cc_BOLD_YELLOW} "=================================================================="
        _commonfunc_print ${cc_BOLD_YELLOW} "   Library libiio is not found in this system."
        _commonfunc_print ${cc_BOLD_YELLOW} "   GPIO EAPI functions of certain devices need it."
        _commonfunc_print ${cc_BOLD_YELLOW} "   It's suggested to install libiio with following instruction:"
        _commonfunc_print ${cc_BOLD_GREEN}  "   sudo apt-get update && sudo apt-get install libiio-dev -y"
        _commonfunc_print ${cc_BOLD_YELLOW} "=================================================================="
	exit 1
    fi
    else
	echo "libiio-dev exists"
fi

# check make
echo ""
echo "---check make---"
if type make > /dev/null 2>&1; then
	echo "make exists"
else
	_commonfunc_print ${cc_BOLD_YELLOW} "=================================================================="
        _commonfunc_print ${cc_BOLD_YELLOW} "   make is not found in this system."
        _commonfunc_print ${cc_BOLD_YELLOW} "   It must install make with following instruction:"
        _commonfunc_print ${cc_BOLD_GREEN}  "   sudo apt-get update && sudo apt-get install make -y"
        _commonfunc_print ${cc_BOLD_YELLOW} "=================================================================="
	exit 1
fi

# check g++
if type g++ > /dev/null 2>&1; then
        echo "g++ exists"
else
        _commonfunc_print ${cc_BOLD_YELLOW} "=================================================================="
        _commonfunc_print ${cc_BOLD_YELLOW} "   make is not found in this system."
        _commonfunc_print ${cc_BOLD_YELLOW} "   It must install make with following instruction:"
        _commonfunc_print ${cc_BOLD_GREEN}  "   sudo apt-get update && sudo apt-get install build-essential -y"
        _commonfunc_print ${cc_BOLD_YELLOW} "=================================================================="
        exit 1
fi

echo "---check finished---"


echo ""
echo "---check EAPI.so---"

if [ -d "/usr/src/advantech/EAPI_"* ];then
        echo "EAPI directory exists. Revome old"
        rm -rf /usr/src/advantech/EAPI_*
fi

if [ -f "/usr/lib/libATAuxIO.so" ];then
	echo "libATAuxIO exists. Revome old"
	rm -rf /usr/lib/libATAuxIO.so*
fi

if [ -f "/usr/lib/libBoardResource.so" ];then
	echo "libBoardResource exists. Revome old"
	rm -rf /usr/lib/libBoardResource.so*
fi

if [ -f "/usr/lib/libEAPI.so" ];then
	echo "libEAPI exists. Remove old"
	rm -rf /usr/lib/libEAPI.so*
fi

if [ -f "/usr/lib/libECGPIO.so" ];then
	echo "libECGPIO exists. Remove old"
	rm -rf /usr/lib/libECGPIO.so*
fi

if [ -f "/usr/lib/libATGPIO.so" ];then
	echo "libATGPIO exists. Remove old"
	rm -rf /usr/lib/libATGPIO.so*
fi

if [ -f "/usr/lib/libEAPI-IPS.so" ];then
	echo "libEAPI-IPS exists. Remove old"
	rm -rf /usr/lib/libEAPI-IPS.so*
fi

echo ""
echo "---copy lib.so to /usr/lib---"

if [ "x${ARCH}" = "xx86_64" ] || [ "x${ARCH}" = "xi686" ]; then
	sudo cp -al -f /usr/src/advantech/${PACKAGE_NAME}/libEAPI_linux-x86_64/libATAuxIO* /usr/lib/
else
	sudo rm -f /usr/src/advantech/${PACKAGE_NAME}/libEAPI_linux-x86_64/libATAuxIO*
fi

sudo cp -al -f /usr/src/advantech/${PACKAGE_NAME}/libEAPI_linux-x86_64/* /usr/lib/
sudo cp /usr/src/advantech/${PACKAGE_NAME}/adv-export.service /etc/systemd/system/

systemctl daemon-reload
systemctl enable adv-export.service
systemctl start adv-export.service
cd /usr/src/advantech/${PACKAGE_NAME}/example/
make

#export gpio and gpioLED
if [ -f /usr/src/advantech/libEAPI/confs/sysfs-gpio/${CURRENT_DEV_NAME}.conf ]; then
        . /usr/src/advantech/libEAPI/confs/sysfs-gpio/${CURRENT_DEV_NAME}.conf
        if [ ${CONF_VERSION} == "1" ]; then
                if [ ${SYSFS_BASE_PATH} ] && [ ${SYSFS_PIN_SHIFT} ]; then
                        /usr/src/advantech/libEAPI/adv-gpio.sh start
                fi

                if [ ${SYSFS_LED_BASE_PATH} ] && [ ${SYSFS_LED_PIN_SHIFT} ]; then
                        /usr/src/advantech/libEAPI/adv-gpioled.sh start
                fi
        fi
        if [ ${CONF_VERSION} == "2" ]; then
                if [ ${SYSFS_GPIO_PIN_0} ]; then
                        echo "export GPIO"
                        /usr/src/advantech/libEAPI/adv-gpio.sh start
                fi

                if [ ${SYSFS_LED_GPIO_PIN_0} ]; then
                        echo "export LED GPIO"
                        /usr/src/advantech/libEAPI/adv-gpioled.sh start
                fi
        fi
fi

echo "Done"

