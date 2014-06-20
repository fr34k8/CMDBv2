#include "stdio.h"
#include <iostream>
#include <string.h>
#include <unistd.h>		/* defines _POSIX_THREADS if pthreads are available */
#if defined(_POSIX_THREADS) || defined(_SC_THREADS)
#include <pthread.h>
#endif
#include <signal.h>		/* defines SIGPIPE */
#include "soapH.h"
#include "BasicHttpBinding_USCOREISDKService.nsmap"

using namespace std;

#define MSG_ERROR_INIT "Cannot soap init"
#define MSG_ERROR_CALL_SERVICE "Cannot call sdk web service"

void InitSDKRequest(struct ns4__SDKRequest &request)
{
	//*********************************************************
	//Assign NULL for attributes not necessary
	//*********************************************************
	request.GetHostInfoRequest = NULL;
	request.theCMDBV2_USCOREGetServerDetailRequest = NULL;	/* optional element of type ns4:CMDBV2_GetServerDetailRequest */
	request.theCMDBV2_USCOREHandleServerVMInfoRequest = NULL;	/* optional element of type ns4:CMDBV2_HandleServerVMInfoRequest */
	request.theCMDBV2_USCORESDKUpdateIpMacRequest = NULL;	/* optional element of type ns4:CMDBv2_SDKUpdateIpMacRequest */
	request.theGetCCUByProductCodeRequest = NULL;	/* optional element of type ns4:GetCCUByProductCodeRequest */
	request.theGetIRDServerVMInfoRequest = NULL;	/* optional element of type ns4:GetIRDServerVMInfoRequest */
	request.theGetIRDTechnicalOwnerInfoRequest = NULL;	/* optional element of type ns4:GetIRDTechnicalOwnerInfoRequest */
	request.theGetListAllServerRequest = NULL;	/* optional element of type ns4:GetListAllServerRequest */
	request.theGetODAHostInfoListRequest = NULL;	/* optional element of type ns4:GetODAHostInfoListRequest */
	request.theGetODAServerInfoListRequest = NULL;	/* optional element of type ns4:GetODAServerInfoListRequest */
	request.theGetProductInfoByIPRequest = NULL;	/* optional element of type ns4:GetProductInfoByIPRequest */
	request.theGetSDKServerInfoListRequest = NULL;	/* optional element of type ns4:GetSDKServerInfoListRequest */
	request.theGetSO6InfoServerRequest = NULL;	/* optional element of type ns4:GetSO6InfoServerRequest */
	request.theGetServerNameBySerialRequest = NULL;	/* optional element of type ns4:GetServerNameBySerialNumberRequest */
	request.theGetSnSInfoTechnicalOwnerRequest = NULL;	/* optional element of type ns4:GetSnSInfoTechnicalOwnerRequest */
	request.theHandleServerVMInfoRequest = NULL;	/* optional element of type ns4:HandleServerVMInfoRequest */
	request.theHostInfoRequest = NULL;	/* optional element of type ns4:GetHostsInfoRequest */
	request.theInsertDataServerVMRequest = NULL;	/* optional element of type ns4:InsertDataServerVMRequest */
	request.theInsertMeasuredDataRequest = NULL;	/* optional element of type ns4:InsertMeasuredDataRequest */
	request.theItemValueRequest = NULL;	/* optional element of type ns4:GetItemValueListRequest */
	request.theMacAddressRequest = NULL;	/* optional element of type ns4:GetHostInfoByIPRequest */
	request.theOpenIncidentByCSRequest = NULL;	/* optional element of type ns4:OpenIncidentByCSRequest */
	request.theOpenIncidentByDCRequest = NULL;	/* optional element of type ns4:OpenIncidentByDCRequest */
	request.theOpenIncidentByG8Request = NULL;	/* optional element of type ns4:OpenIncidentByG8Request */
	request.theRemoveDataServerVMRequest = NULL;	/* optional element of type ns4:RemoveDataServerVMRequest */
	request.theSDKPostRequest = NULL;	/* optional element of type ns4:SDKPostRequest */
	request.theSDKUpdateIpMacRequest = NULL;	/* optional element of type ns4:SDKUpdateIpMacRequest */
	request.theServerInfo = NULL;	/* optional element of type ns4:ServerInfo */
	request.theUpdateDataServerPhysicalRequest = NULL;	/* optional element of type ns4:HandleServerPhysicalInfoRequest */
	request.theUpdateDataServerVMRequest = NULL;	/* optional element of type ns4:UpdateDataServerVMRequest */
	request.theUpdateInfoRequest = NULL;	/* optional element of type ns4:UpdateInfoRequest */
	request.theUpdateServerStatusRequest = NULL;	/* optional element of type ns4:UpdateServerStatusRequest */
	//*********************************************************
}

extern "C" char* CallSDKService(string& strError, char* pClientId, char* pChecksum, char* pOperation, unsigned int iTime, char* pRequestData)
{	
	struct soap soap;	
	try
	{
		soap_init(&soap);
	}
	catch(exception& ex)
	{
		strError = MSG_ERROR_INIT;
		return NULL;
	}
	
	soap.connect_timeout = 60;	/* try to connect for 1 minute */
	soap.send_timeout = soap.recv_timeout = 60;	/* if I/O stalls, then timeout after 30 seconds */
	
	struct _ns1__Call tagCallRequest;
	struct _ns1__CallResponse tagCallResponse;
	char* pResponse = NULL;
	char* pTmpResponse = NULL;
	int nDataLength = 0;
		
	//*********************************************************
	//Init request
	//*********************************************************
	struct ns4__SDKRequest request;
	InitSDKRequest(request);
	request.ClientId	= pClientId;
	request.Checksum	= pChecksum;
	request.Operation	= pOperation; 
	request.RequestTime = &iTime;
	request.RequestData = pRequestData;
	//*********************************************************
	// JSON Format
	//*********************************************************
	ns4__DataFormatEnum eDataFormat = ns4__DataFormatEnum__JSON;
	request.DataFormat = &eDataFormat;
	
	tagCallRequest.request = &request;
	
	cout << "Operation:" << pOperation << endl;
	cout << "ClientId:" << pClientId << endl;
	cout << "Checksum:" << pChecksum << endl;
	cout << "Time:" << iTime << endl;
	cout << "RequestData:" << pRequestData << endl;
	if(soap_call___ns1__Call(&soap, 
							NULL  /*endpoint address*/, 
							NULL  /*soapAction*/, 
							&tagCallRequest, 
							&tagCallResponse
						   )== SOAP_OK)
	{
		pTmpResponse = (char*)tagCallResponse.CallResult->ResponseData;	

		if (NULL != pTmpResponse)
		{
			// Allocate memory to store result
			nDataLength = strlen(pTmpResponse);
			pResponse = new char[nDataLength + 1];
			pResponse[nDataLength] = '\0';

			// Copy result to memory
			strcpy(pResponse, pTmpResponse);
		}
	}
	else
	{
		strError = MSG_ERROR_CALL_SERVICE;
	}

	soap_destroy(&soap); 
	soap_end(&soap); 
	soap_done(&soap);
	return pResponse;
}