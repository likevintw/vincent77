docker run \
    -dit \
    --name susi_demo \
    --privileged \
    -p 1080:5000 \
    -p 1081:5001 \
    -v /sys/:/sys/ \
    -v /etc/:/etc/ \
    -v /dev/:/dev/ \
    -v /home/:/volume \
    ubuntu:20.04
