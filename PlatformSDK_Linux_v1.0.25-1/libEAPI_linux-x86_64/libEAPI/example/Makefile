################################## 
## Makefile for simple programs ##
##################################

###########################################
# User defined
###########################################
#
# Current system (yocto2.1 system is like then ubuntu)
SYSTEM = Ubuntu
#SYSTEM = Fedora
LIBTYPE = so
#
# use gdb
# Maybe you should run cmd "ulimit -c unlimited"
# at first (allow gdb to store the dump core).
# Run cmd "gdb ${PRG} core" to check gdb msg.
# Run cmd "valgrind --leak-check=full ${PRG}" to  check mem leak.
#USE_GDB = -g
#
AUXIO_LINKNAME = ATAuxIO
EC_LINKNAME = EAPI
GPIO_LINKNAME = ATGPIO
IPS_LINKNAME = EAPI-IPS
SMBUS_LINKNAME = ATSMBUS
BOARDRESOURCE_LINKNAME = BoardResource

#
###########################################
# makefile
###########################################
LIBNAME = lib$(LINKNAME).$(LIBTYPE).$(VERCODE)
ARCH = $(shell uname -i)

INC = -I../include
LIB = -l$(LINKNAME)
CXX = g++ 
CXX_FLAG = ${USE_GDB} -Wall -std=c++11

ifeq ($(ARCH), armv7l)
ALLPROGRAM = \
    testdl_ec\
    testdl_gpio\
    testdl_wdt\
    testdl_etp\
    testdl_hwmon\
    testdl_extfunc\
    testdl_brightness\
    batterytest\
    nodeidtest\
    diotest\
    wdttest\
    ledtest\
    testdl_ipsae
else 
ifeq ($(ARCH), aarch64)
ALLPROGRAM = \
    testdl_ec\
    testdl_gpio\
    testdl_wdt\
    testdl_etp\
    testdl_hwmon\
    testdl_extfunc\
    testdl_brightness\
    batterytest\
    nodeidtest\
    diotest\
    wdttest\
    ledtest\
    testdl_ipsae
else
ALLPROGRAM = \
    testdl_AuxIO\
    testdl_ec\
    testdl_gpio\
    testdl_wdt\
    testdl_etp\
    testdl_hwmon\
    testdl_poe\
    testdl_extfunc\
    testdl_brightness\
    batterytest\
    nodeidtest\
    diotest\
    wdttest\
    ledtest\
    testdl_smbus\
    uno-mxm-info\
    testdl_ipsae
endif
endif

all: $(ALLPROGRAM)

testdl_AuxIO: testdl_AuxIO.o	
	$(CXX) $^ $(INC) -l$(AUXIO_LINKNAME) -ldl -o $@
	@rm $^

testdl_gpio: testdl_gpio.o
	$(CXX) $^ $(INC) -l$(GPIO_LINKNAME) -ldl -o $@
	@rm $^

testdl_poe: testdl_poe.o
	$(CXX) $^ $(INC) -l$(GPIO_LINKNAME) -ldl -o $@
	@rm $^

testdl_ec: testdl_ec.o
	$(CXX) $^ $(INC) -l$(EC_LINKNAME) -ldl -o $@
	@rm $^

testdl_brightness: testdl_brightness.o
	$(CXX) $^ $(INC) -l$(EC_LINKNAME) -ldl -o $@
	@rm $^

testdl_etp: testdl_etp.o
	$(CXX) $^ $(INC) -l$(EC_LINKNAME) -ldl -o $@
	@rm $^

testdl_extfunc: testdl_extfunc.o
	$(CXX) $^ $(INC) -l$(EC_LINKNAME) -ldl -o $@
	@rm $^

testdl_hwmon: testdl_hwmon.o
	$(CXX) $^ $(INC) -l$(EC_LINKNAME) -ldl -o $@
	@rm $^

testdl_wdt: testdl_wdt.o
	$(CXX) $^ $(INC) -l$(EC_LINKNAME) -ldl -o $@
	@rm $^

batterytest: batterytest.o
	$(CXX) $^ $(INC) -l$(BOARDRESOURCE_LINKNAME) -ldl -o $@
	@rm $^

diotest: diotest.o
	$(CXX) $^ $(INC) -l$(BOARDRESOURCE_LINKNAME) -ldl -o $@
	@rm $^

ledtest: ledtest.o
	$(CXX) $^ $(INC) -l$(BOARDRESOURCE_LINKNAME) -ldl -o $@
	@rm $^

nodeidtest: nodeidtest.o
	$(CXX) $^ $(INC) -l$(BOARDRESOURCE_LINKNAME) -ldl -o $@
	@rm $^

wdttest: wdttest.o
	$(CXX) $^ $(INC) -l$(BOARDRESOURCE_LINKNAME) -ldl -o $@
	@rm $^

testdl_ipsae: testdl_ipsae.o
	$(CXX) $^ $(INC) -l$(IPS_LINKNAME) -ldl -o $@
	@rm $^

testdl_smbus: testdl_smbus.o
	$(CXX) $^ $(INC) -ldl -o $@
	@rm $^

uno-mxm-info: uno-mxm-info.o
	$(CXX) $^ $(INC) -ldl -o $@
	@rm $^

.SUFFIXES: .c .o
.c.o:
	$(CXX) $(CXX_FLAG) $(INC) -c $*.c -o $*.o
.cpp.o:
	$(CXX) $(CXX_FLAG) $(INC) -c $*.cpp -o $*.o

.PHONY: libversion clean install uninstall

libversion:
	@echo "System lib version:"
	@if [ "x$(LIB_EXIST)" = "xexist" ]; then strings $(INSTALL_PATH)/$(LIBNAME) |grep "lib${LINKNAME} version";else echo "Not found."; fi;
	@echo "Current lib version:"
	@strings $(LIB_PATH)/$(LIBNAME) |grep "lib${LINKNAME} version"

clean:
	@echo "Removing linked and compiled files......"
	@rm -f *.o $(ALLPROGRAM)


