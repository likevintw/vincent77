docker run \
    -dit \
    --name susi_iot_demo \
    --privileged \
    -v /sys/:/sys/ \
    -v /etc/:/etc/ \
    -v /dev/:/dev/ \
    -v /home/:/volume \
    susiiot_ubuntu:1.0.1
