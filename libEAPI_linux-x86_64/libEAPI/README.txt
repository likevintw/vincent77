---
                   Advantech EAPI Library
                     Installation Guide
             Copyright (C) 2024, Advantech Co., Ltd.
---

# Contents

1. [Introduction](#introduction)
2. [Device support list](#device-support-list)
3. [Files](#files)
4. [Release Notes](#release-notes)
5. [Installation](#installation)
6. [Run Example Program](#run-example-program)
7. [Limitation](#limitation)
8. [Known Issue](#known-issue)

-----------------------------------------------------------------------------
# Introduction
	
   Advantech Linux EApi Library.

-----------------------------------------------------------------------------
# Device support list

```
   Information and reference:
   BOARDRESOURCE Library:
        WISE-710, TPC-71W
   
   IPS Library:
        PPC-IPS-AE

   EC Library:
	AMAX-5570, AMAX-5570E, AMAX-5570S, APAX-5580-433AE, APAX-5580-473AE,
	APAX-5580-4C3AE, ECU-4784

	PPC-3120-7701, PPC-6121-7703, PPC-4*-7705, PPC-3*-7706, PPC-3*-7707, PPC-4*-7708
	PPC-421W-7709, PPC-3*-7710, PPC-3*-7711, PPC-3*-7712, PPC-6*-7760, PPC-6*-7762
	PPC-61X1C-8260

        TPC-8100TR, TPC-651T-E3AE, TPC-1251T-E3AE, TPC-1551T-E3AE, TPC-1751T-E3AE, 
        TPC-1051WP-E3AE, TPC-1551WP-E3AE, TPC-71W, TPC-B300, TPC-B520, TPC-307W, TPC-300 EHL
	TPC-315-R83xB(TPC-300-?8??B), TPC-1782H-433AE

	UNO-1172A(not support lock operation), UNO-127, UNO-1372G-E3AE, UNO-1372G-J021AE, 
	UNO-1483G-434AE, UNO-2271G-E2xAE, UNO-2372G, UNO-238V2, UNO-2473G-JxAE, UNO-2483G-434AE, 
        UNO-2484G-673xAE, UNO-3283G-674AE, UNO-3285G-674AE, UNO-3483G-374AE, 
        UNO-348, UNO-420, UNO-430
        
	PR/VR4

	WISE-710

        Watchdog feature: (in EC library)
            UNO-137_V2, UNO-2271G_V2, UNO-2372G_V2, PPC-3100-7701, PPC-3120-7701,
            PPC-3150-7701, PPC-415-7705, PPC-310-7706, PPC-312-7706, PPC-315-7706,
            PPC-321W-7706, PPC-315W-7707, PPC-318W-7707, PPC-321W-7707,
            PPC-324W-7707, PPC-415-7708, PPC-417-7708, PPC-419-7708, PPC-415W-7709,
            PPC-421W-7709, PPC-306-7710, TPC-307W, TPC-B300, TPC-B520, TPC-B610H-A*,
            TPC-B610W-A*, TPC-315-RE22A

	Hardware monitor function:
	    AMAX-5570, AMAX-5570E, AMAX-5570S, AMAX-5580
	
	    MIC-770V3H, MIC-770V3W

	    PPC-3120-7701, PPC-6121-7703, PPC-4*-7705, PPC-3*-7706, PPC-3*-7707, PPC-4*-7708
	    PPC-421W-7709, PPC-3*-7710, PPC-3*-7711, PPC-3*-7712, PPC-6*-7760, PPC-6*-7762
	    PPC-61X1C-8260
	    
	    TPC-300, TPC-300-X2XXX, TPC-307W, TPC-B300, TPC-B500, TPC-B520, TPC-B610H, TPC-B610W
	    
	    UNO-127, UNO-137, UNO-1372, UNO-137, UNO-137_V2, UNO-148, UNO-148_V2, UNO-2271G_V2
	    UNO-2372G, UNO-2372G_V2, UNO-238, UNO-238_V2, UNO-238V2, UNO-247, UNO-247V2, UNO-2473G, 
	    UNO-2484G, UNO-2484G_V2, UNO-348, UNO-348_H, UNO-348_W, UNO-410, UNO-420, UNO-430

   GPIO Library:
     ECGPIO Library: (libECGPIO.so, EC backend)
        RSB-4760, UNO-1372G-E3AE, UNO-1372G-J021AE, WISE-710, TPC-71W, UNO-2484G
     AuxIO Library: (libATAuxIO.so, sysfs backend)
	AMAX-5570, AMAX-5570S, MIC-770V3H, MIC-770V3W, UNO-127, UNO-137, UNO-137_V2, UNO-148, UNO-2271G_V2, UNO-2372G_V2, 
	UNO-238, UNO-238_V2, UNO-247V2, UNO-2484G_V2, UNO-348, UNO-348_H, UNO-348_W, UNO-410, UNO-420,
	PPC-3120-7701, PPC-3*-7711 and PPC-6*-7762

   SMBUS Library:
        Products with SMBus master function.

```

-----------------------------------------------------------------------------
# Files
   After installation, directories and files are listed below.
```
/usr
├── lib
│   ├── libATAuxIO.so -> /usr/src/advantech/libEAPI_linux-x86_64/libATAuxIO.so
│   ├── libATGPIO.so -> /usr/src/advantech/libEAPI_linux-x86_64/libATGPIO.so
│   ├── libBoardResource.so -> /usr/src/advantech/libEAPI_linux-x86_64/libBoardResource.so
│   ├── libEAPI-IPS.so -> /usr/src/advantech/libEAPI_linux-x86_64/libEAPI-IPS.so
│   ├── libEAPI.so -> /usr/src/advantech/libEAPI_linux-x86_64/libEAPI.so
│   ├── libECGPIO.so -> /usr/src/advantech/libEAPI_linux-x86_64/libECGPIO.so
│   └── libATSMBUS.so -> /usr/src/advantech/libEAPI_linux-x86_64/libATSMBUS.so

/usr/src/advantech/libEAPI
├── adv-gpioled.sh
├── adv-gpio.sh
├── confs
│   ├── hwmon
│   │   ├── Advantech EAMB9918-A1 board.ini
│   │   ├── AMAX-5570E.ini
│   │   ├── AMAX-5570.ini
│   │   ├── AMAX-5570S.ini
│   │   ├── AMAX-5580.ini -> WISE-5580.ini
│   │   ├── Freescale i.MX6 DualLite WISE710 A1.ini
│   │   ├── LICENSE
│   │   ├── MIC-770V3H.ini -> MIC-770V3W.ini
│   │   ├── MIC-770V3W.ini
│   │   ├── PPC-306.ini -> PPC-310.ini
│   │   ├── PPC-3100.ini -> PPC-3120.ini
│   │   ├── PPC-310.ini
│   │   ├── PPC-3120.ini
│   │   ├── PPC-312.ini -> PPC-310.ini
│   │   ├── PPC-312SW-7712.ini
│   │   ├── PPC-315.ini -> PPC-310.ini
│   │   ├── PPC-315S-7712.ini -> PPC-312SW-7712.ini
│   │   ├── PPC-315SW-7711.ini
│   │   ├── PPC-315SW-7712.ini -> PPC-312SW-7712.ini
│   │   ├── PPC-315W-7707.ini
│   │   ├── PPC-315W.ini
│   │   ├── PPC-317S-7712.ini -> PPC-312SW-7712.ini
│   │   ├── PPC-317SW-7712.ini -> PPC-312SW-7712.ini
│   │   ├── PPC-318SW-7711.ini -> PPC-315SW-7711.ini
│   │   ├── PPC-318W-7707.ini -> PPC-315W-7707.ini
│   │   ├── PPC-318W.ini -> PPC-315W.ini
│   │   ├── PPC-321SW-7711.ini -> PPC-315SW-7711.ini
│   │   ├── PPC-321W-7707.ini -> PPC-315W-7707.ini
│   │   ├── PPC-321W.ini -> PPC-315W.ini
│   │   ├── PPC-324W-7707.ini -> PPC-315W-7707.ini
│   │   ├── PPC-324W.ini -> PPC-315W.ini
│   │   ├── PPC-415-7705.ini
│   │   ├── PPC-415-7708.ini
│   │   ├── PPC-415W-7709.ini
│   │   ├── PPC-417-7705.ini -> PPC-415-7705.ini
│   │   ├── PPC-417-7708.ini -> PPC-415-7708.ini
│   │   ├── PPC-417W-7709.ini -> PPC-415W-7709.ini
│   │   ├── PPC-419-7705.ini -> PPC-415-7705.ini
│   │   ├── PPC-419-7708.ini -> PPC-415-7708.ini
│   │   ├── PPC-419W-7709.ini -> PPC-415W-7709.ini
│   │   ├── PPC-6121-7703.ini
│   │   ├── PPC-612-7760.ini
│   │   ├── PPC-612-7762.ini
│   │   ├── PPC-6151C-7760.ini -> PPC-612-7760.ini
│   │   ├── PPC-6151C-7762.ini -> PPC-612-7762.ini
│   │   ├── PPC-615W-7760.ini -> PPC-612-7760.ini
│   │   ├── PPC-615W-7762.ini -> PPC-612-7762.ini
│   │   ├── PPC-6171C-7760.ini -> PPC-612-7760.ini
│   │   ├── PPC-6171C-7762.ini -> PPC-612-7762.ini
│   │   ├── PPC-618W-7760.ini -> PPC-612-7760.ini
│   │   ├── PPC-618W-7762.ini -> PPC-612-7762.ini
│   │   ├── PPC-6191C-7760.ini -> PPC-612-7760.ini
│   │   ├── PPC-6191C-7762.ini -> PPC-612-7762.ini
│   │   ├── PPC-61X1C-8260H.ini
│   │   ├── PPC-61X1C-8260.ini
│   │   ├── PPC-621W-7760.ini -> PPC-612-7760.ini
│   │   ├── PPC-621W-7762.ini -> PPC-612-7762.ini
│   │   ├── README.md
│   │   ├── TPC-300.ini
│   │   ├── TPC-300-X2XXX.ini
│   │   ├── TPC-307W.ini
│   │   ├── TPC-310W.ini -> TPC-307W.ini
│   │   ├── TPC-B300.ini
│   │   ├── TPC-B500.ini
│   │   ├── TPC-B520.ini
│   │   ├── TPC-B520L.ini -> TPC-B520.ini
│   │   ├── TPC-B610H.ini
│   │   ├── TPC-B610W.ini
│   │   ├── UNO-127.ini
│   │   ├── UNO-1372.ini
│   │   ├── UNO-137.ini
│   │   ├── UNO-137_V2.ini
│   │   ├── UNO-137V2.ini -> UNO-137_V2.ini
│   │   ├── UNO-148.ini
│   │   ├── UNO-148_V2.ini
│   │   ├── UNO-148V2.ini -> UNO-148_V2.ini
│   │   ├── UNO-2271G_V2.ini
│   │   ├── UNO-2271GV2.ini -> UNO-2271G_V2.ini
│   │   ├── UNO-2372G.ini
│   │   ├── UNO-2372G_V2.ini
│   │   ├── UNO-2372GV2.ini -> UNO-2372G_V2.ini
│   │   ├── UNO-238.ini
│   │   ├── UNO-238_V2.ini
│   │   ├── UNO-238V2.ini -> UNO-238_V2.ini
│   │   ├── UNO-2473G.ini
│   │   ├── UNO-247.ini
│   │   ├── UNO-247_V2.ini -> UNO-247V2.ini
│   │   ├── UNO-247V2.ini
│   │   ├── UNO-2484G.ini
│   │   ├── UNO-2484G_V2.ini
│   │   ├── UNO-2484GV2.ini -> UNO-2484G_V2.ini
│   │   ├── UNO-348_H.ini
│   │   ├── UNO-348.ini
│   │   ├── UNO-348_W.ini
│   │   ├── UNO-410.ini -> UNO-137.ini
│   │   ├── UNO-420.ini
│   │   ├── UNO-430.ini
│   │   └── WISE-5580.ini
│   └── sysfs-gpio
│       ├── AMAX-5570.conf -> UNO-127.conf
│       ├── AMAX-5570E.conf
│       ├── AMAX-5570S.conf
│       ├── MIC-770V3H.conf -> MIC-770V3W.conf
│       ├── MIC-770V3W.conf
│       ├── PPC-3100-7701.conf
│       ├── PPC-3120-7701.conf -> PPC-3100-7701.conf
│       ├── PPC-3150-7701.conf -> PPC-3100-7701.conf
│       ├── PPC-315SW-7711.conf -> PPC-318SW-7711.conf
│       ├── PPC-318SW-7711.conf
│       ├── PPC-321SW-7711.conf -> PPC-318SW-7711.conf
│       ├── PPC-612-7762.conf -> PPC-318SW-7711.conf
│       ├── PPC-6151C-7762.conf -> PPC-318SW-7711.conf
│       ├── PPC-615W-7762.conf -> PPC-318SW-7711.conf
│       ├── PPC-6171C-7762.conf -> PPC-318SW-7711.conf
│       ├── PPC-618W-7762.conf -> PPC-318SW-7711.conf
│       ├── PPC-6191C-7762.conf -> PPC-318SW-7711.conf
│       ├── PPC-621W-7762.conf -> PPC-318SW-7711.conf
│       ├── UNO-127.conf
│       ├── UNO-137.conf
│       ├── UNO-137_V2.conf
│       ├── UNO-137V2.conf -> UNO-137_V2.conf
│       ├── UNO-148.conf
│       ├── UNO-148_V2.conf
│       ├── UNO-148V2.conf -> UNO-148_V2.conf
│       ├── UNO-2271G_V2.conf -> UNO-127.conf
│       ├── UNO-2271GV2.conf -> UNO-2271G_V2.conf
│       ├── UNO-2372G_V2.conf
│       ├── UNO-2372GV2.conf -> UNO-2372G_V2.conf
│       ├── UNO-238.conf
│       ├── UNO-238_V2.conf
│       ├── UNO-238V2.conf -> UNO-238_V2.conf
│       ├── UNO-247_V2.conf -> UNO-247V2.conf
│       ├── UNO-247V2.conf
│       ├── UNO-2484G_V2.conf
│       ├── UNO-2484GV2.conf -> UNO-2484G_V2.conf
│       ├── UNO-348.conf
│       ├── UNO-348_H.conf -> UNO-348.conf
│       ├── UNO-348_W.conf -> UNO-348.conf
│       ├── UNO-410.conf -> UNO-137.conf
│       └── UNO-420.conf
├── EAPI - Developer Guide.pdf
├── example
│   ├── batterytest
│   ├── batterytest.c
│   ├── diotest
│   ├── diotest.c
│   ├── ledtest
│   ├── ledtest.c
│   ├── Makefile
│   ├── nodeidtest
│   ├── nodeidtest.c
│   ├── python-example
│   │   ├── cppCallPython.py
│   │   ├── Makefile
│   │   ├── pythonCallCpp.py
│   │   ├── pythonCallCppWithPipe.py
│   │   ├── README
│   │   └── testdl_ipsae.cpp
│   ├── README
│   ├── testdl_AuxIO
│   ├── testdl_AuxIO.c
│   ├── testdl_brightness
│   ├── testdl_brightness.c
│   ├── testdl_ec
│   ├── testdl_ec.c
│   ├── testdl_etp
│   ├── testdl_etp.c
│   ├── testdl_extfunc
│   ├── testdl_extfunc.c
│   ├── testdl_gpio
│   ├── testdl_gpio.c
│   ├── testdl_hwmon
│   ├── testdl_hwmon.c
│   ├── testdl_ipsae
│   ├── testdl_ipsae.cpp
│   ├── testdl_poe
│   ├── testdl_poe.c
│   ├── testdl_smbus
│   ├── testdl_smbus.c
│   ├── testdl_wdt
│   ├── testdl_wdt.c
│   ├── uno-mxm-info
│   ├── uno-mxm-info.c
│   ├── wdttest
│   └── wdttest.c
├── include
│   ├── atAuxIO.h
│   ├── atEAPI.h
│   ├── atECBRIGHTNESS.h
│   ├── atECETP.h
│   ├── atECEXTFUNC.h
│   ├── atECWDT.h
│   ├── atGPIO.h
│   ├── atHWMON.h
│   ├── atIPSAE.h
│   ├── atSMBUS.h
│   ├── board_resource.h
│   ├── EApi.h
│   └── eapi_sharefunc.h
├── README.txt
└── Tools
    ├── eeprom
    │   └── PRVR-Bosch-DTOS
    │       ├── etp-factory-burner.tar.gz
    │       └── etp-factory-burner.tar.gz.md5
    ├── IPS-test
    │   └── test_example
    │       ├── embeddedproxy.cc
    │       ├── inc
    │       │   ├── atIPSAE.h
    │       │   ├── EApi.h
    │       │   └── embeddedproxy.h
    │       ├── main
    │       ├── main.cpp
    │       └── Makefile
    ├── node
    │   └── RSB4760-Schneider-DTOS
    │       ├── node-atgpio.tar.gz
    │       ├── node-atgpio.tar.gz.md5
    │       ├── node-atlmsensor.tar.gz
    │       ├── node-atlmsensor.tar.gz.md5
    │       ├── node-atplatform.tar.gz
    │       ├── node-atplatform.tar.gz.md5
    │       ├── node-installer.tar.gz
    │       ├── node-installer.tar.gz.md5
    │       ├── node-ipsae.tar.gz
    │       └── node-ipsae.tar.gz.md5
    └── README
/usr/src/advantech/libEAPI_linux-aarch64
├── libATAuxIO.so -> libATAuxIO.so.0.0.7
├── libATAuxIO.so.0.0.7
├── libATGPIO.so -> libATGPIO.so.0.0.3
├── libATGPIO.so.0.0.3
├── libBoardResource.so -> libBoardResource.so.1.0.1
├── libBoardResource.so.1.0.1
├── libEAPI-IPS.so -> libEAPI-IPS.so.1.0.3
├── libEAPI-IPS.so.1.0.3
├── libEAPI.so -> libEAPI.so.1.0.15
├── libEAPI.so.1.0.15
├── libECGPIO.so -> libECGPIO.so.1.0.3
└── libECGPIO.so.1.0.3
/usr/src/advantech/libEAPI_linux-armv7l
├── libATAuxIO.so -> libATAuxIO.so.0.0.7
├── libATAuxIO.so.0.0.7
├── libATGPIO.so -> libATGPIO.so.0.0.3
├── libATGPIO.so.0.0.3
├── libBoardResource.so -> libBoardResource.so.1.0.1
├── libBoardResource.so.1.0.1
├── libEAPI-IPS.so -> libEAPI-IPS.so.1.0.3
├── libEAPI-IPS.so.1.0.3
├── libEAPI.so -> libEAPI.so.1.0.15
├── libEAPI.so.1.0.15
├── libECGPIO.so -> libECGPIO.so.1.0.3
└── libECGPIO.so.1.0.3
/usr/src/advantech/libEAPI_linux-i686
├── libATAuxIO.so -> libATAuxIO.so.0.0.7
├── libATAuxIO.so.0.0.7
├── libATGPIO.so -> libATGPIO.so.0.0.3
├── libATGPIO.so.0.0.3
├── libBoardResource.so -> libBoardResource.so.1.0.1
├── libBoardResource.so.1.0.1
├── libEAPI-IPS.so -> libEAPI-IPS.so.1.0.3
├── libEAPI-IPS.so.1.0.3
├── libEAPI.so -> libEAPI.so.1.0.15
├── libEAPI.so.1.0.15
├── libECGPIO.so -> libECGPIO.so.1.0.3
└── libECGPIO.so.1.0.3
/usr/src/advantech/libEAPI_linux-x86_64
├── libATAuxIO.so -> libATAuxIO.so.0.0.9
├── libATAuxIO.so.0.0.9
├── libATGPIO.so -> libATGPIO.so.0.0.3
├── libATGPIO.so.0.0.3
├── libATSMBUS.so -> libATSMBUS.so.1.0.0
├── libATSMBUS.so.1.0.0
├── libBoardResource.so -> libBoardResource.so.1.0.2
├── libBoardResource.so.1.0.2
├── libEAPI-IPS.so -> libEAPI-IPS.so.1.0.3
├── libEAPI-IPS.so.1.0.3
├── libEAPI.so -> libEAPI.so.1.0.22
├── libEAPI.so.1.0.22
├── libECGPIO.so -> libECGPIO.so.1.0.3
└── libECGPIO.so.1.0.3

```
-----------------------------------------------------------------------------
# Release Notes
## CHANGES in v1.0.25-1
- Fixed [MIC-770V3W] had no CPU(PECI)

## CHANGES in v1.0.25
- Watchdog function supports:
    MIC-770V3H, MIC-770V3W, UNO-247V2
- Hwmon function supports:
    MIC-770V3H, MIC-770V3W, UNO-247V2
- GPIO function supports:
    MIC-770V3H, MIC-770V3W, UNO-247V2

## CHANGES in v1.0.24-3
- New SMBus library, libATSMBUS.so, support SMBus read function
- Watchdog function supports:
    AMAX-5570, AMAX-5570E, AMAX-5570S, UNO-127, UNO-137_V2, UNO-2271G_V2, UNO-2372G_V2,
    PPC-3100-7701, PPC-3120-7701, PPC-3150-7701, PPC-415-7705, PPC-310-7706, PPC-312-7706,
    PPC-315-7706, PPC-321W-7706, PPC-315W-7707, PPC-318W-7707, PPC-321W-7707, PPC-324W-7707,
    PPC-415-7708, PPC-417-7708, PPC-419-7708, PPC-415W-7709, PPC-421W-7709, PPC-306-7710,
    TPC-307W, TPC-B300, TPC-B520, TPC-B610H-A*, TPC-B610W-A*, TPC-315-RE22A
- Brightness function supports:
    PPC-306-7710, PPC-3???-7707, PPC-415W-7709, PPC-421W-7709, PPC-415-7705, 
    PPC-310-7706, PPC-312-7706, PPC-315-7706, PPC-321W-7706, PPC-415-7708, 
    PPC-417-7708, PPC-419-7708, TPC-307W, TPC-B300, TPC-B520, TPC-B610H-A*, TPC-B610W-A*,
    TPC-315-RE22A, TPC-312-RE23A, TPC-312-RJ23A, TPC-315-RE23A, TPC-315-RJ23A,
    TPC-317-RE23A, TPC-317-RJ23A, TPC-B520L
- Hwmon function supports:
    PPC-415-7705, PPC-417-7705, PPC-419-7705, PPC-315W-7707, PPC-318W-7707,
    PPC-321W-7707, PPC-324W-7707, PPC-415W-7709, PPC-417W-7709, PPC-419W-7709,
    PPC-315SW-7711, PPC-318SW-7711, PPC-321SW-7711, PPC-312SW-7712, PPC-315S-7712,
    PPC-315SW-7712, PPC-317S-7712, PPC-317SW-7712, PPC-612-7760, PPC-6151C-7760,
    PPC-615W-7760, PPC-6171C-7760, PPC-618W-7760, PPC-6191C-7760, PPC-621W-7760,
    PPC-612-7762, PPC-6151C-7762, PPC-615W-7762, PPC-6171C-7762, PPC-618W-7762,
    PPC-6191C-7762, PPC-621W-7762, PPC-61X1C-8260H, PPC-61X1C-8260, UNO-238V2
- GPIO function supports:
    PPC-315SW-7711, PPC-318SW-7711, PPC-321SW-7711, PPC-612-7762, PPC-6151C-7762,
    PPC-615W-7762, PPC-6171C-7762, PPC-618W-7762, PPC-6191C-7762, PPC-621W-7762,

## CHANGES in v1.0.23
- Support TPC-B520, TPC-307W, TPC-300 EHL in 1.0.23.

## CHANGES in v1.0.22-1
- Support PPC-306 PPC-3100 in 1.0.22-1.

## CHANGES in v1.0.22
- Update PPC-310 3VSB VBAT index.
- Add check 5VSB_R1 and R2.
- scale 3VSB for PPC-3xx PPC-4xx.

## CHANGES in v1.0.21-1
- Add some check strategy in install script.

## CHANGES in v1.0.21
- Support PPC-3*-7706 PPC-3*-7710 PPC-4*-7708 TPC-300-?8??B
- Add R1_5VSB and R2_5VSB for PPC-4*-7708 in Hardware monitor 

## CHANGES in v1.0.20
- Fixed read UNO-238 gpio sysfs-config failed 

## CHANGES in v1.0.19
- Hardware monitor support UNO-238_V2

## CHANGES in v1.0.18 v1.0.18-1
- Update UNO-238 &UNO-238_V2 config to verion 2.
- Config base path match two gpio path.
- ECfunction support sysfs gpio to control LED.
- Fixed gpio sysfs config get gpio number failed.

## CHANGES in v1.0.17
- Update AuxIO library version to 0.0.8
	- Can read version 2 config
	- GPIO support UNO-238_V2

## CHANGES in v1.0.16-2	
- support UNO-410
- optimized testdl_extfunc

## CHANGES in v1.0.16
- sysfs GPIO information (base path and pin shift) is kept as config file.
  libATAuxIO.so gets GPIO information from config file and reference built-in
  table as backup plan.
- EApiBoardGetValue and EApiBoardGetStringA are supported in RISC platform.
- GPIO functions are supported in libEAPI.so. (But functions of libATGPIO.so
   remains.)
- x86_64, armv7l and aarch64 are all supported in Debian package. i686 (x86
   32bit) is also supported for EdgeLink container.

## CHANGES in v1.0.15
- Support Debian software package.
- Support UNO-2372G_V2, UNO-2484G_V2
- Dynamically load iio library for UNO-420. (Then no dependency of libiio.)
- EApiBoardGetValue/EApiBoardGetStringA enhanced for RISC platform.

## CHANGES in v1.0.14
- New library, named libATGPIO.so, is made to handle GPIO and PoE EAPI function
  calls. There are two types of GPIO backend in product: sysfs and EC driver.
  This library detects product which it running in and uses corresponding
  backend to make GPIO EAPI work smoothly.
- PoE EAPI functions applied in libATGPIO.so: EAPIPoEGetLevel and
  EAPIPoESetLevel. 
- New GPIO function : EAPIGPIOGetCount
- The EC-driver backend GPIO library is renamed in this release: libECGPIO.so.
  The only change made in this library is GPIO direction value. Now output
  direction is defined as 0 and input direction is defined as 1.
- The sysfs backend GPIO library, libATAuxIO.so, now supports product:
  UNO-2484G_V2.
- New EAPI IDs are supported by libEAPI.so

  - For EApiBoardGetStringA:

        EAPI_ID_BOARD_DMIBIOS_VENDOR_STR
        EAPI_ID_BOARD_DMIBIOS_VERSION_STR
        EAPI_ID_BOARD_DMIBIOS_DATE_STR
        EAPI_ID_BOARD_DMISYS_UUID_STR
        EAPI_ID_BOARD_DMISYS_VENDOR_STR 
        EAPI_ID_BOARD_DMISYS_PRODUCT_STR
        EAPI_ID_BOARD_DMISYS_VERSION_STR
        EAPI_ID_BOARD_DMISYS_SERIAL_STR
        EAPI_ID_BOARD_DMIBOARD_VENDOR_STR
        EAPI_ID_BOARD_DMIBOARD_NAME_STR
        EAPI_ID_BOARD_DMIBOARD_VERSION_STR
        EAPI_ID_BOARD_DMIBOARD_SERIAL_STR
        EAPI_ID_BOARD_DMIBOARD_ASSET_TAG_STR

  - For EApiBoardGetValue:

        EAPI_ID_GPIO_POE_PINNUM

- Rename rules:
```
Folder of libATGPIO.so : WGPIO -> GPIO
Folder of libECGPIO.so : GPIO -> ECGPIO
Folder of libATAuxIO.so: unchanged
```

# Installation
- Executing the following instructions to install EAPI

```
# sudo apt-get install -y ./adv-libeapi_1.0.16_all.deb

```

# Run example program
   - Go to installed directory: /usr/src/advantech/libEAPI/example

   _NOTE: Running example program usually needs root privilege._
```
# cd /usr/src/advantech/libEAPI/example
```
### GPIO
- Export GPIO node
/usr/src/advantech/libEAPI/adv-gpio.sh start

- Unexport GPIO node
/usr/src/advantech/libEAPI/adv-gpio.sh stop

- Export LEDGPIO node
/usr/src/advantech/libEAPI/adv-gpioled.sh start

- Unexport LEDGPIO node
/usr/src/advantech/libEAPI/adv-gpioled.sh stop


- Run following command to test GPIO and PoE API. Follow help guide printed by
  example program.
```
# make testdl_gpio testdl_poe
# ./testdl_gpio
# ./testdl_poe
```

### AuxIO
- Run following command to test AuxIO API and get more usage.
```
# make testdl_AuxIO
# ./testdl_AuxIO
```

### COMMON, HWmon, ExtFunction, WDT, Brightness and SMBus
- Run following command to test COMMON API. 
```
# make testdl_ec
# ./testdl_ec
```
- Run following command to test HWmon API. 
```
# make testdl_hwmon
# ./testdl_hwmon
```
- Run following command to test WDT API. 
```
# make testdl_wdt
# ./testdl_wdt
```
- Run following command to test ExtFunction API. 
```
# make testdl_extfunc
# ./testdl_extfunc
```
- Run following command to test Brightness API.
```
# make testdl_brightness
# ./testdl_brightness
```

- Run uno-mxm-info to get GPU-related information

```
# make uno-mxm-info
# ./uno-mxm-info
```

  SMBus examples use EApiSMBReadByte to collect GPU-related information. SMBus
  API only supports UNO-MXM-* devices. These examples have been verified with
  UNO-MXM-CB01.

  Output format:
  <pre>[DATA-ADDRESS] -- [description for retrieved data]: [date retrieved] </pre>
  Some information is combined with two bytes, so two addresses are displayed
  in first column.

- Run testdl_smbus to get data via SMBus by specifying r/w, I2C bus ID, slave
  address and data address.
```
# make testdl_smbus
# ./testdl_smbus [R/W] [BUSID] [SLAVE-ADDRESS] [DATA-ADDRESS]
```

  - description for each input
  ```
            [R/W]: r(read) or w(write) function
          [BUSID]: I2C bus ID
  [SLAVE-ADDRESS]: slave address
   [DATA-ADDRESS]: data address
  ```
- Compare results between testdl_smbus and i2c tool.
  - install i2c-tools
  ```
  # sudo apt-get install -y i2c-tools
  ```
  - i2cget command format
  <pre>i2cget -y [BUSID] [SLAVE-ADDRESS] [DATA-ADDRESS]</pre>
  - results from testdl_smbus and i2cget would be the same
  ```
  # sudo ./testdl_smbus r 0 0x4f 0xff
  # sudo i2cget -y 0 0x4f 0xff
  ```
  
### IPS

By default, UPS status information is output to the screen at intervals. 
The log was store in /var/log/syslog. Also, users can modify the example 
'atCallBack' function to realize customization requirements.

- Run following command to communicate with IPSAE. 

"/dev/ttyS0" is currently serial node which is connected to UPS device.
```
# cd /usr/src/advantech/libEAPI/example
# make testdl_ipsae
# ./testdl_ipsae "/dev/ttyS0"
```

---
# Limitation
### Dependent
We suggest to use GLIBC 2.23 or above version.

### Compiler
We suggest to use GCC/G++ 5.4.0 or above version to compile.

### UNO-1372G-E3AE LED operation
<pre>
Due to using the old EC firmware, UNO-1372G-E3AE LED operation was 
must be based on the GPIO Library. DI0~3:0~3, DO0~3:4~7.
</pre>
Please use following cmd to test LED 'PL1':
```
# cd /usr/src/advantech/libEAPI/example
# make testdl_gpio
```
- To open LED(output high):
```
# ./testdl_gpio 3 7 1
# ./testdl_gpio 5 7 1
```
- To close LED(output low):
```
# ./testdl_gpio 3 7 1
# ./testdl_gpio 5 7 0
```

### Enabling TCO Timer for Watchdog EAPI
For UNO-137_V2 and UNO-2372G_V2, the TCO timer is disabled by default in BIOS
settings. To utilize the watchdog EAPI, follow these steps to access BIOS and
enable the TCO timer.
```
1. Reference user manual of your device to enter BIOS
2. In BIOS: [Chipset] -> [PCH-IO Configuration] -> [Enable TCO Timer] -> [Enabled]
```


-----------------------------------------------------------------------------
# Known issue
### UPS

Current UPS library only supports PCB version 01-2(including) or above version.

PCB version 01-1 (inclusive) may print "unknown reply" frequently.

-----------------------------------------------------------------------------

