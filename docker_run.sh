# docker run \
#     -dit \
#     --name susi_iot_demo \
#     --privileged \
#     -v /sys/:/sys/ \
#     -v /proc/:/proc/ \
#     -v /etc/:/etc/ \
#     -v /dev/:/dev/ \
#     -v /var/:/var/ \
#     -v /lib/:/lib/ \
#     -v /home/:/volume \
#     susiiot_ubuntu:1.0.1 \
#     /bin/bash

# sudo docker run \
#     --rm \
#     -it \
#     --name susi_iot_demo \
#     --privileged \
#     -v /sys/:/sys/ \
#     -v /proc/:/proc/ \
#     -v /etc/:/etc/ \
#     -v /dev/:/dev/ \
#     -v /var/:/var/ \
#     -v /home/:/volume \
#     susiiot_ubuntu:1.0.1 \
#     /bin/bash

# sudo docker run \
#     -it \
#     --rm \
#     --name susi_iot_demo \
#     --privileged \
#     -v /sys/firmware/efi/efivars/:/sys/firmware/efi/efivars/ \
#     -v /etc/:/etc/ \
#     -v /home/:/volume \
#     ubuntu:20.04 \
#     /bin/bash

sudo docker run \
    -it \
    --rm \
    --name susi_iot_demo \
    --privileged \
    -v /sys/firmware/efi/efivars/:/sys/firmware/efi/efivars/ \
    -v /etc/board/:/etc/board/ \
    -v /home/:/volume \
    susiiot_ubuntu:1.0.1 \
    /bin/bash

apt-get update && \
    apt-get install -y git python3 python3-pip libjansson4 

git clone https://github.com/likevintw/vincent77.git && \
    cd vincent77 && \
    sudo python3 -m unittest -v test_susiiot.TestCases > "$(date +\%Y\%m\%d\%H\%M\%S)_result.txt"

cd root  && \
    git clone https://github.com/likevintw/vincent77.git && \
    cd vincent77 && \
    python3 -m unittest -v test_susiiot.TestCases > "$(date +\%Y\%m\%d\%H\%M\%S)_result.txt"