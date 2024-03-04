#!/bin/bash

GEN_ROOT_PATH=gen_root
DISCOVERT_PATH=$GEN_ROOT_PATH/onvif_ws_discovery
ONVIF_CTX_PATH=$GEN_ROOT_PATH/dev_interfaces
COMON_PATH=$GEN_ROOT_PATH/common

declare -A wsdls=(['Access_Control']=/ver10/pacs/accesscontrol.wsdl
	['Access_Rules']=/ver10/accessrules/wsdl/accessrules.wsdl
	['Action_Engine']=/ver10/actionengine.wsdl
	['Analytics']=/ver20/analytics/wsdl/analytics.wsdl
	['App_Management']=/ver10/appmgmt/wsdl/appmgmt.wsdl
	['Authentication_Behavior']=/ver10/authenticationbehavior/wsdl/authenticationbehavior.wsdl
	['Credential']=/ver10/credential/wsdl/credential.wsdl
	['Device_IO']=/ver10/deviceio.wsdl
	['Display']=/ver10/display.wsdl
	['Door_Control']=/ver10/pacs/doorcontrol.wsdl
	['Imaging']=/ver20/imaging/wsdl/imaging.wsdl
	['Media']=/ver10/media/wsdl/media.wsdl
	['Provisioning']=/ver10/provisioning/wsdl/provisioning.wsdl
	['PTZ']=/ver20/ptz/wsdl/ptz.wsdl
	['Receiver']=/ver10/receiver.wsdl
	['Recording']=/ver10/recording.wsdl
	['Search']=/ver10/search.wsdl
	['Replay']=/ver10/replay.wsdl
	['Schedule']=/ver10/schedule/wsdl/schedule.wsdl
	['Advanced_Security']=/ver10/advancedsecurity/wsdl/advancedsecurity.wsdl
	['Thermal']=/ver10/thermal/wsdl/thermal.wsdl
	['Uplink']=/ver10/uplink/wsdl/uplink.wsdl
	['Media2']=/ver20/media/wsdl/media.wsdl
	['Remote_Discovery']=/ver10/network/wsdl/remotediscovery.wsdl
)

if [ $# -eq 0 ]; then
	echo "Usage: $0 <common,ws-directory,onvif-interface>"
	exit 0
fi

if [ $1 == "common" ]; then
	echo "Start generating common files..."
	
	if [ ! -d $COMON_PATH ]; then
		echo "Generating common path"
		mkdir -p $COMON_PATH
		echo "Generating common path success"
		
		cp ./others/[st]* $COMON_PATH
		echo "Copying common files success"
	else
		echo "Common path already exists"
	fi
	
	echo "Generating common files end"
	exit 0
fi

if [ $1 == "ws-directory" ]; then
	echo "Generating ws-directory files..."
	
	if [ ! -d $DISCOVERT_PATH ]; then
		mkdir -p $DISCOVERT_PATH
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
	
	exit 0
fi

if [ $1 == "onvif-interface" ]; then
	echo "Generating onvif-interface files..."
	
	if [ ! -f $GEN_ROOT_PATH/dev_interfaces.h ]; then
		
		command_list=()
		
		for key in ${!wsdls[@]}; do
			printf "Add $key(${wsdls[$key]})? [Y/n] default n. "
			read answer
			if [ ${#answer} -eq 0 ] || [ 'n' == "$answer" ] || [ 'N' == '$answer' ]; then
				echo "Skip $key module"
				continue
				elif [ 'y' == "$answer" ] || [ 'Y' == "$answer" ]; then
				echo "Add generating of $key"
				command_list+=( "https://www.onvif.org/${wsdls[$key]}" )
				#echo ${command_list[@]}
			fi
		done
		
		command_ctx="./wsdl2h.exe -P -x -o $GEN_ROOT_PATH/dev_interfaces.h -s -t typemap.dat ${command_list[@]}"
		${command_ctx}
	fi
	
	if [ ! -d $ONVIF_CTX_PATH ]; then
		mkdir -p $ONVIF_CTX_PATH
	fi
	
	file_count=`ls ${ONVIF_CTX_PATH} -l | grep "^-" | wc -l`;
	
	if [ $file_count -le 4 ]; then
		./soapcpp2.exe $GEN_ROOT_PATH/dev_interfaces.h -I ./import -d $ONVIF_CTX_PATH -x -S -L -q onvif_api
	fi
	
	exit 0
fi

echo "Usage: $0 <common,ws-directory,onvif-interface>"
