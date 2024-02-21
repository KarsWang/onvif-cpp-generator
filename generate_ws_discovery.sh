DISCOVERT_PATH=ws_discovery

if [ ! -d $DISCOVERT_PATH ]; then
	mkdir $DISCOVERT_PATH
fi

if [ ! -f $DISCOVERT_PATH/ws_discovery.h ]; then
	./wsdl2h.exe -P -x -o $DISCOVERT_PATH/ws_discovery.h -s -t typemap.dat https://www.onvif.org/ver10/network/wsdl/remotediscovery.wsdl
fi

./soapcpp2.exe -S -I ./import $DISCOVERT_PATH/ws_discovery.h -d $DISCOVERT_PATH -x

cp ./others/stdsoap2.h $DISCOVERT_PATH
cp ./others/stdsoap2.cpp $DISCOVERT_PATH

cp ./others/smdevp.h $DISCOVERT_PATH
cp ./others/smdevp.cpp $DISCOVERT_PATH

cp ./others/threads.h $DISCOVERT_PATH
cp ./others/threads.cpp $DISCOVERT_PATH

cp ./others/wsaapi.h $DISCOVERT_PATH
cp ./others/wsaapi.cpp $DISCOVERT_PATH

cp ./others/wsddapi.h $DISCOVERT_PATH
cp ./others/wsddapi.cpp $DISCOVERT_PATH

rm $DISCOVERT_PATH/soapServerLib.cpp