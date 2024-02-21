#include "RemoteDiscoveryBinding.nsmap"

#include "soapStub.h"
#include "wsddapi.h"

#define soapWS_new2 soap_new2
#define soapWS_set_namespaces soap_set_namespaces
#define wsdd_namespaces namespaces
#define soapWS_valid_socket soap_valid_socket
#define soapWS_bind soap_bind
#define OnvifLogOutput printf
#define soapWS_wsdd_listen soap_wsdd_listen
#define soapWS_destroy soap_destroy
#define soapWS_end soap_end
#define soapWS_free soap_free

int main(int argc, char* argv[])
{
#ifdef _WIN32
	int iResult;
	WSAData wsaData;
	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
#endif

	int port = 3702;
	constexpr const char* addr = "239.255.255.250";

	struct soap* wsdd_soap = soapWS_new2(SOAP_IO_UDP | SOAP_IO_FLUSH, SOAP_IO_UDP | SOAP_IO_FLUSH);
	soapWS_set_namespaces(wsdd_soap, wsdd_namespaces);
	wsdd_soap->accept_timeout = 10;
	wsdd_soap->recv_timeout = 10;
	wsdd_soap->send_timeout = 10;
	struct ip_mreq mcast;
	int nError = 0;
	nError = soapWS_valid_socket(soapWS_bind(wsdd_soap, NULL, 3702, 100));
	if (!nError)
	{
		printf("---------error ");
		printf("current function:%s line:%d\n", __FUNCTION__, __LINE__);
	}

	mcast.imr_multiaddr.s_addr = inet_addr("239.255.255.250");
	mcast.imr_interface.s_addr = htonl(INADDR_ANY);
	nError = setsockopt(wsdd_soap->master, IPPROTO_IP, IP_ADD_MEMBERSHIP, (char*)&mcast, sizeof(mcast));
	if (nError < 0)
	{
		int error = nError;
		OnvifLogOutput("setsockopt error! error code = %d,err string = %s\n", error, strerror(error));
		OnvifLogOutput("setsockopt error!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! %d\n", nError);
		return 0;
	}
	for (;;)
	{
		if (SOAP_OK != soapWS_wsdd_listen(wsdd_soap, 100))
		{
			if (-1 != wsdd_soap->error)
			{
				OnvifLogOutput("soapWS_wsdd_listen return error!\n");
			}
		}
	}
	soapWS_destroy(wsdd_soap);
	soapWS_end(wsdd_soap);
	soapWS_free(wsdd_soap);

	getchar();
	return 0;
}


SOAP_FMAC5 int SOAP_FMAC6 SOAP_ENV__Fault(soap*, char* faultcode,
	char* faultstring, char* faultactor,
	SOAP_ENV__Detail* detail,
	SOAP_ENV__Code* SOAP_ENV__Code,
	SOAP_ENV__Reason* SOAP_ENV__Reason,
	char* SOAP_ENV__Node, char* SOAP_ENV__Role,
	SOAP_ENV__Detail* SOAP_ENV__Detail)
{
	printf("current function:%s line:%d\n", __FUNCTION__, __LINE__);
	return SOAP_OK;
}


SOAP_FMAC5 int SOAP_FMAC6 __tdn__Hello(soap*, wsdd__HelloType tdn__Hello, wsdd__ResolveType& tdn__HelloResponse)
{
	printf("current function:%s line:%d\n", __FUNCTION__, __LINE__);
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __tdn__Bye(soap*, wsdd__ByeType tdn__Bye, wsdd__ResolveType& tdn__ByeResponse)
{
	printf("current function:%s line:%d\n", __FUNCTION__, __LINE__);
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __tdn__Probe(soap*, wsdd__ProbeType tdn__Probe, wsdd__ProbeMatchesType& tdn__ProbeResponse)
{
	printf("current function:%s line:%d\n", __FUNCTION__, __LINE__);
	return SOAP_OK;
}



SOAP_FMAC5 int SOAP_FMAC6 soap_send___wsdd__Hello(soap* soap, const char* soap_endpoint, const char* soap_action, wsdd__HelloType* wsdd__Hello)
{
	printf("current function:%s line:%d\n", __FUNCTION__, __LINE__);
	return SOAP_FMAC5 int SOAP_FMAC6();
}

SOAP_FMAC5 int SOAP_FMAC6 soap_recv___wsdd__Hello(soap* soap, struct __wsdd__Hello*)
{
	printf("current function:%s line:%d\n", __FUNCTION__, __LINE__);
	return SOAP_FMAC5 int SOAP_FMAC6();
}

SOAP_FMAC5 int SOAP_FMAC6 soap_send___wsdd__Bye(soap* soap, const char* soap_endpoint, const char* soap_action, wsdd__ByeType* wsdd__Bye)
{
	printf("current function:%s line:%d\n", __FUNCTION__, __LINE__);
	return SOAP_FMAC5 int SOAP_FMAC6();
}

SOAP_FMAC5 int SOAP_FMAC6 soap_recv___wsdd__Bye(soap* soap, struct __wsdd__Bye*)
{
	printf("current function:%s line:%d\n", __FUNCTION__, __LINE__);
	return SOAP_FMAC5 int SOAP_FMAC6();
}

SOAP_FMAC5 int SOAP_FMAC6 soap_send___wsdd__Probe(soap* soap, const char* soap_endpoint, const char* soap_action, wsdd__ProbeType* wsdd__Probe)
{
	printf("current function:%s line:%d\n", __FUNCTION__, __LINE__);
	return SOAP_FMAC5 int SOAP_FMAC6();
}

SOAP_FMAC5 int SOAP_FMAC6 soap_recv___wsdd__Probe(soap* soap, struct __wsdd__Probe*)
{
	printf("current function:%s line:%d\n", __FUNCTION__, __LINE__);
	return SOAP_FMAC5 int SOAP_FMAC6();
}

SOAP_FMAC5 int SOAP_FMAC6 soap_send___wsdd__ProbeMatches(soap* soap, const char* soap_endpoint, const char* soap_action, wsdd__ProbeMatchesType* wsdd__ProbeMatches)
{
	printf("current function:%s line:%d\n", __FUNCTION__, __LINE__);
	return SOAP_FMAC5 int SOAP_FMAC6();
}

SOAP_FMAC5 int SOAP_FMAC6 soap_recv___wsdd__ProbeMatches(soap* soap, struct __wsdd__ProbeMatches*)
{
	printf("current function:%s line:%d\n", __FUNCTION__, __LINE__);
	return SOAP_FMAC5 int SOAP_FMAC6();
}

SOAP_FMAC5 int SOAP_FMAC6 soap_send___wsdd__Resolve(soap* soap, const char* soap_endpoint, const char* soap_action, wsdd__ResolveType* wsdd__Resolve)
{
	printf("current function:%s line:%d\n", __FUNCTION__, __LINE__);
	return SOAP_FMAC5 int SOAP_FMAC6();
}

SOAP_FMAC5 int SOAP_FMAC6 soap_recv___wsdd__Resolve(soap* soap, struct __wsdd__Resolve*)
{
	printf("current function:%s line:%d\n", __FUNCTION__, __LINE__);
	return SOAP_FMAC5 int SOAP_FMAC6();
}

SOAP_FMAC5 int SOAP_FMAC6 soap_send___wsdd__ResolveMatches(soap* soap, const char* soap_endpoint, const char* soap_action, wsdd__ResolveMatchesType* wsdd__ResolveMatches)
{
	printf("current function:%s line:%d\n", __FUNCTION__, __LINE__);
	return SOAP_FMAC5 int SOAP_FMAC6();
}

SOAP_FMAC5 int SOAP_FMAC6 soap_recv___wsdd__ResolveMatches(soap* soap, struct __wsdd__ResolveMatches* rm)
{
	printf("current function:%s line:%d\n", __FUNCTION__, __LINE__);
	return SOAP_FMAC5 int SOAP_FMAC6();
}


void wsdd_event_Hello(soap* soap, unsigned int InstanceId, const char* SequenceId, unsigned int MessageNumber, const char* MessageID, const char* RelatesTo, const char* EndpointReference, const char* Types, const char* Scopes, const char* MatchBy, const char* XAddrs, unsigned int MetadataVersion)
{
	printf("current function:%s line:%d\n", __FUNCTION__, __LINE__);
}

void wsdd_event_Bye(soap* soap, unsigned int InstanceId, const char* SequenceId, unsigned int MessageNumber, const char* MessageID, const char* RelatesTo, const char* EndpointReference, const char* Types, const char* Scopes, const char* MatchBy, const char* XAddrs, unsigned int* MetadataVersion)
{
	printf("current function:%s line:%d\n", __FUNCTION__, __LINE__);
}

soap_wsdd_mode wsdd_event_Probe(soap* soap, const char* MessageID,
	const char* ReplyTo, const char* Types, const char* Scopes,
	const char* MatchBy, wsdd__ProbeMatchesType* matches)
{

	static struct wsdd__ScopesType scopes;

	matches->ProbeMatch->wsa__EndpointReference.Address = "urn:uuid:464A4854-4656-5242-4530-313035394100";
	matches->ProbeMatch->Types = "tdn:NetworkVideoTransmitter";
	matches->ProbeMatch->Scopes = NULL;
	matches->ProbeMatch->XAddrs = "http://192.168.100.9/onvif/device_service";
	matches->ProbeMatch->MetadataVersion = 10;

	matches->__sizeProbeMatch = 1;

	printf("current function:%s line:%d\n", __FUNCTION__, __LINE__);
	return soap_wsdd_mode();
}

void wsdd_event_ProbeMatches(soap* soap, unsigned int InstanceId, const char* SequenceId, unsigned int MessageNumber, const char* MessageID, const char* RelatesTo, wsdd__ProbeMatchesType* matches)
{
	printf("current function:%s line:%d\n", __FUNCTION__, __LINE__);
}

soap_wsdd_mode wsdd_event_Resolve(soap* soap, const char* MessageID, const char* ReplyTo, const char* EndpointReference, wsdd__ResolveMatchType* match)
{
	printf("current function:%s line:%d\n", __FUNCTION__, __LINE__);
	return soap_wsdd_mode();
}

void wsdd_event_ResolveMatches(soap* soap, unsigned int InstanceId, const char* SequenceId, unsigned int MessageNumber, const char* MessageID, const char* RelatesTo, wsdd__ResolveMatchType* match)
{
	printf("current function:%s line:%d\n", __FUNCTION__, __LINE__);
}
