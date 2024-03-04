#!/bin/bash

GEN_ROOT_PATH=gen_root
DISCOVERT_PATH=$GEN_ROOT_PATH/onvif_ws_discovery
ONVIF_CTX_PATH=$GEN_ROOT_PATH/dev_interfaces
COMON_PATH=$GEN_ROOT_PATH/common

if [ ! -d $DISCOVERT_PATH ]; then
    mkdir -p $DISCOVERT_PATH
fi
if [ ! -d $ONVIF_CTX_PATH ]; then
    mkdir -p $ONVIF_CTX_PATH
fi

if [ ! -d $COMON_PATH ]; then
    mkdir -p $COMON_PATH
		cp ./others/[st]* $COMON_PATH
fi

if [ ! -f $GEN_ROOT_PATH/ws_discovery.h ]; then
    ./wsdl2h.exe -P -x -o $GEN_ROOT_PATH/ws_discovery.h -s -t typemap.dat https://www.onvif.org/ver10/network/wsdl/remotediscovery.wsdl
fi

if [ ! -f $DISCOVERT_PATH/RemoteDiscoveryBinding.nsmap ]; then
    ./soapcpp2.exe $GEN_ROOT_PATH/ws_discovery.h -I ./import -d $DISCOVERT_PATH -x -L
    rm $DISCOVERT_PATH/wsdd.nsmap
    
    if [ ! -f $DISCOVERT_PATH/wsddapi.h ]; then
        cp ./others/ws* $DISCOVERT_PATH
    fi
fi

# ./soapcpp2.exe -S -I ./import $DISCOVERT_PATH/ws_discovery.h -d $DISCOVERT_PATH -x
# cp ./others/stdsoap2.h $DISCOVERT_PATH
# cp ./others/stdsoap2.cpp $DISCOVERT_PATH
# cp ./others/smdevp.h $DISCOVERT_PATH
# cp ./others/smdevp.cpp $DISCOVERT_PATH
# cp ./others/threads.h $DISCOVERT_PATH
# cp ./others/threads.cpp $DISCOVERT_PATH
# cp ./others/wsaapi.h $DISCOVERT_PATH
# cp ./others/wsaapi.cpp $DISCOVERT_PATH
# cp ./others/wsddapi.h $DISCOVERT_PATH
# cp ./others/wsddapi.cpp $DISCOVERT_PATH
# rm $DISCOVERT_PATH/soapServerLib.cpp
