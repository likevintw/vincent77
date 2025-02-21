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
#
# make static application
#USE_STATIC = -static
#LIBTYPE = a
LIBTYPE = so
#
# use gdb
# Maybe you should run cmd "ulimit -c unlimited"
# at first (allow gdb to store the dump core).
# Then run cmd "gdb ${PRG} core" to check gdb msg.
#USE_GDB = -g
#
LINKNAME = EAPI-IPS
VERCODE = 1.0.3
#
###########################################
# makefile
###########################################
LIBNAME = lib$(LINKNAME).$(LIBTYPE).$(VERCODE)
ARCH = $(shell uname -i)
ifeq ($(ARCH),x86_64)
ifeq ($(SYSTEM),Ubuntu)
INSTALL_PATH = /usr/lib
endif
ifeq ($(SYSTEM),Fedora)
INSTALL_PATH = /usr/lib64
endif
LIB_PATH = ../v$(VERCODE)/lib$(LINKNAME)_x64
else ifeq ($(ARCH),aarch64)
INSTALL_PATH = /usr/lib
LIB_PATH = ../v$(VERCODE)/lib$(LINKNAME)_aarch64
else
INSTALL_PATH = /usr/lib
LIB_PATH = ../v$(VERCODE)/lib$(LINKNAME)_x86
endif
LIB_EXIST = $(shell if [ -f "$(INSTALL_PATH)/$(LIBNAME)" ]; then echo "exist"; else echo "notexist"; fi;)
LINK_EXIST = $(shell if [ -f "$(INSTALL_PATH)/lib$(LINKNAME).$(LIBTYPE)" ]; then echo "exist"; else echo "notexist"; fi;)

INC = -I../../include -I/usr/include/python3.5
#LIB = -L$(LIB_PATH) -L/usr/lib/python3.5/config-3.5m-i386-linux-gnu $(USE_STATIC) -l$(LINKNAME) -pthread
LIB = -L$(LIB_PATH) -L/usr/lib/python3.5/config-3.5m-x86_64-linux-gnu $(USE_STATIC) -l$(LINKNAME) -pthread

CXX = g++ 
CXX_FLAG = ${USE_GDB} -Wall -std=c++11

PRG = testdl_ipsae
OBJ = testdl_ipsae.o

$(PRG):$(OBJ)
	$(CXX) $^ $(INC) $(LIB) -ldl -lpython3.5 -o $@
	@rm $^
	@if [ "x$(LIB_EXIST)" = "xnotexist" ]; then cp -arxf $(LIB_PATH)/$(LIBNAME) $(INSTALL_PATH); fi;
	@if [ "x$(LINK_EXIST)" = "xnotexist" ]; then ln -s $(INSTALL_PATH)/$(LIBNAME) $(INSTALL_PATH)/lib$(LINKNAME).$(LIBTYPE); fi;

.SUFFIXES: .cpp .o
.cpp.o:
	$(CXX) $(CXX_FLAG) $(INC) -c $*.cpp -o $*.o

.PHONY: libversion clean install uninstall

libversion:
	@echo "System lib version:"
	@if [ "x$(LIB_EXIST)" = "xexist" ]; then strings $(INSTALL_PATH)/$(LIBNAME) |grep "libEAPI-IPS version";else echo "Not found."; fi;
	@echo "Current lib version:"
	@strings $(LIB_PATH)/$(LIBNAME) |grep "libEAPI-IPS version"

clean:
	@echo "Removing linked and compiled files......"
	@rm -rf $(OBJ) $(PRG) *core* testdl_ipsae __pycache__ UPS_FIFO

install:
	@echo "Install lib......"
	@rm -f $(INSTALL_PATH)/lib$(LINKNAME).so*
	@cp -arxf $(LIB_PATH)/$(LIBNAME) $(INSTALL_PATH)
	@ln -s $(INSTALL_PATH)/$(LIBNAME) $(INSTALL_PATH)/lib$(LINKNAME).$(LIBTYPE)

uninstall:
	@echo "Uninstall lib......"
	@rm -f $(INSTALL_PATH)/lib$(LINKNAME).so*

