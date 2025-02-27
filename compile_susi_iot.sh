# exit

# on x86
# sudo apt-get install libjansson-dev

sudo rm kengweisusiiot
g++ -Wall -O2 -I. -D _LINUX \
    /home/advantech/kengwei/vincent77/SUSI4.2.24139/SUSIIoTDEMO/demo/main.cpp \
    -o kengweisusiiot libjansson.x86.so libSusiIoT.x86.so
sudo ./kengweisusiiot

# on ARM, todo
# g++ -Wall -O2 -I. -D _LINUX \
#     /home/advantech/kengwei/vincent77/SUSI5.0.23985/SUSIIoTDEMO/demo/main.cpp \
#     -o kengweisusiiot libjansson.so.4 libSusiIoT.so