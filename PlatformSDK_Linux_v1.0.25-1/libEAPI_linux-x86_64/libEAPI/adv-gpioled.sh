#!/bin/bash

if [ $# -eq 0 ];then
	echo "Please input arguments!"
	exit 1
fi

PRODUCT_NAME=`cat /sys/devices/virtual/dmi/id/product_name`

if [ -e /proc/board ]; then
        #from adv driver
        CURRENT_DEV_NAME=`cat /proc/board | awk -F "-" '{print $1"-"$2}'`
else
        #from dmi
        CURRENT_DEV_NAME=`cat /sys/devices/virtual/dmi/id/product_name | awk -F "-" '{print $1"-"$2}'`
fi

if [ -f /usr/src/advantech/libEAPI/confs/sysfs-gpio/${PRODUCT_NAME}.conf ]; then
        CURRENT_DEV_NAME=`cat /sys/devices/virtual/dmi/id/product_name`
fi

if [ -f /usr/src/advantech/libEAPI/confs/sysfs-gpio/${CURRENT_DEV_NAME}.conf ]; then
	. /usr/src/advantech/libEAPI/confs/sysfs-gpio/${CURRENT_DEV_NAME}.conf
	if [ $CONF_VERSION -eq 1 ]; then
		if [ -z ${SYSFS_LED_BASE_PATH} ] || [ -z ${SYSFS_LED_PIN_SHIFT} ]; then
			echo "The LED GPIO base or shift value path does not exist."
			exit 1
		else
			if [ -f ${SYSFS_LED_BASE_PATH} ]; then
				BASE=`cat ${SYSFS_LED_BASE_PATH}`
                        else
                                echo "${SYSFS_LED_BASE_PATH} not exist."
                                echo "You must load gpio driver."
                                exit 1
                        fi
		fi
		for i in ${!SYSFS_LED_PIN_SHIFT[@]}
		do
			shift=${SYSFS_LED_PIN_SHIFT[i]}
			total=`expr ${BASE} + ${shift}`
			case "$1" in
				start)
					#export gpio
					if [ -f ${SYSFS_LED_BASE_PATH} ]; then
						if [ -d /sys/class/gpio/gpio${total} ];then
							echo "LED gpio exported"
							exit 1
						else
							echo $total > /sys/class/gpio/export
							echo out > /sys/class/gpio/gpio${total}/direction
						fi
					else
						echo "LED GPIO export failed"
						exit 1
					fi
					;;
				stop)
					#unexport gpio
					if [ -d /sys/class/gpio/gpio${total} ]; then
						echo $total > /sys/class/gpio/unexport
					else
						echo "LED GPIO unexport failed"
						exit 1
					fi
					;;
				*)
					;;
			esac
		done
	elif [ $CONF_VERSION -eq 2 ]; then
		count=0
		if [ -z ${SYSFS_LED_GPIO_COUNT} ]; then
                        echo "Not support LED GPIO"
                        exit 1
                fi
		while [ $count -lt $SYSFS_LED_GPIO_COUNT ]; do
			eval "base=\${SYSFS_LED_GPIO_PIN_$count[0]}"
			eval "shift=\${SYSFS_LED_GPIO_PIN_$count[1]}"
			if [ -f ${SYSFS_LED_GPIO_PIN_0} ]; then
                                total=$((`cat $base` + $shift))
                        else
                                echo "LED GPIO system node not exits"
                                echo "You must load gpio driver"
                                exit 1
                        fi
			((count++))
			case "$1" in
				start)
					#export gpio
					if [ -f ${base} ]; then
						if [ -d /sys/class/gpio/gpio${total} ];then
							echo "LED gpio exported"
							exit 1
						else
							echo ${total} > /sys/class/gpio/export
							echo out > /sys/class/gpio/gpio${total}/direction
						fi
					else
						echo "LED GPIO export failed"
						exit 1
					fi
					;;
				stop)
					#unexport gpio
					if [ -d /sys/class/gpio/gpio${total} ]; then
						echo $total > /sys/class/gpio/unexport
					else
						echo "LED GPIO unexport failed"
						exit 1
					fi
					;;
				*)
					;;
			esac
		done
	else
		echo "lack of CONF_VERSION"
        fi
else
	echo "lack of configuration"
	exit 1
fi

echo "Finished"
exit 0

