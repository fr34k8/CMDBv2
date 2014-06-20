#include "SDKService.h"
#include "../Config/md5.h"
#include <dlfcn.h>

CSDKService::CSDKService(void)
{
	m_pClientId = NULL;
	m_strPasswd = "";
	m_pOperation = NULL;
	m_pRequestData = NULL;
}

CSDKService::~CSDKService(void)
{
}

string CSDKService::GetChecksum(unsigned int iTime)
{
	string strRequestTime = CUtilities::ConvertIntToString(iTime);
	string strCheckSum = strRequestTime + m_strPasswd;
	strCheckSum = md5(strCheckSum);
	return strCheckSum;
}
char* CSDKService::CallService()
{
	// Get request time
	unsigned int iTime;

	time_t ltime;
	time(&ltime); 
	iTime = (unsigned int)ltime;

	char* pResult;
	pResult = NULL;

	string strLibName;
	string strApiName;
	
	stringstream ssErrorMsg;
	string strLog = "";
	string strWSMsgError = "";

	strLibName = "libSKDWSService-1.0.so";
	strApiName = "CallSDKService";

	// open the library
	void* handle = dlopen((const char*)strLibName.c_str(), RTLD_LAZY);
	if (!handle) 
	{		
		ssErrorMsg << "Cannot open library: " << dlerror() << __FILE__ << "|" << __LINE__;		
		strLog = CUtilities::FormatLog(ERROR_MSG, "CBaseChecker", "CallSnSService","error:" + ssErrorMsg.str());
		CUtilities::WriteErrorLog(strLog);
		return NULL;
	}
	// reset errors
	dlerror();
	SDKServiceInfo apiSDKServiceInfo = (SDKServiceInfo)dlsym(handle, (const char*)strApiName.c_str());
	const char *dlsym_error = dlerror();
	if (dlsym_error) {
		ssErrorMsg << "Cannot load symbol " << strApiName.c_str() << ":" << dlsym_error;
		strLog = CUtilities::FormatLog(ERROR_MSG, "CSDKService", "Call","error:" + ssErrorMsg.str());
		CUtilities::WriteErrorLog(strLog);
		// close the library
		dlclose(handle);
	}
	string strChecksum = GetChecksum(iTime);

	char* pChecksum = (char*)strChecksum.c_str();
	pResult = apiSDKServiceInfo(strWSMsgError, m_pClientId, pChecksum, m_pOperation, iTime, m_pRequestData);
	if (strWSMsgError != "")
	{
		strLog = CUtilities::FormatLog(ERROR_MSG, "CSDKService", "Call","error:" + strWSMsgError);
		CUtilities::WriteErrorLog(strLog);
	}
	// close the library
	dlclose(handle);

	return pResult;	
}