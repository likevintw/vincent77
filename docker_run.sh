docker run \
    -dit \
    --name susi_iot_demo \
    --privileged \
    -v /sys/:/sys/ \
    -v /proc/:/proc/ \
    -v /etc/:/etc/ \
    -v /dev/:/dev/ \
    -v /var/:/var/ \
    -v /lib/:/lib/ \
    -v /home/:/volume \
    susiiot_ubuntu:1.0.1 \
    /bin/bash
