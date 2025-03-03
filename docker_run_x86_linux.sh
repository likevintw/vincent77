docker run \
    --rm \
    -it \
    --name susi_iot_demo \
    --privileged \
    -v /sys/firmware/efi/efivars/:/sys/firmware/efi/efivars/ \
    -v /home/:/volume \
    susiiot_ubuntu:1.0.1 \
    bash

# /sys/firmware/efi/efivars/:/sys/firmware/efi/efivars/