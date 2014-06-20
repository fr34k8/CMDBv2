#include "BaseChecker.h"
#include "../Model/CollectorModel.h"
#include "../Common/DBCommon.h"
#include <dlfcn.h>

CBaseChecker::CBaseChecker(void)
{
	m_pSerialNumber = NULL;
}

CBaseChecker::~CBaseChecker(void)
{
}

char* CBaseChecker::CallSnSService(CCollectorModel* pData)
{
	char* pResult;
	pResult = NULL;

	stringstream ssErrorMsg;
	string strLog = "";
	string strWSMsgError = "";

	string strAPIName;
	strAPIName = pData->GetAPIName();

	// open the library
	void* handle = dlopen((const char*)pData->GetLibraryName().c_str(), RTLD_LAZY);
	HardwareInfo apiHardwareInfo;
	CollectorInfo apiCollectorInfo;

	if (!handle) 
	{		
		ssErrorMsg << "Cannot open library: " << dlerror() << __FILE__ << "|" << __LINE__;		
		strLog = CUtilities::FormatLog(ERROR_MSG, "CBaseChecker", "CallSnSService","error:" + ssErrorMsg.str());
		CUtilities::WriteErrorLog(strLog);
		return false;
	}
	// reset errors
	dlerror();

	if (strAPIName == API_GET_HARDWARE_BY_SERIALNUMBER)
	{
		apiHardwareInfo = (HardwareInfo)dlsym(handle, (const char*)strAPIName.c_str());
	}
	else
	{
		apiCollectorInfo = (CollectorInfo)dlsym(handle, (const char*)strAPIName.c_str());
	}

	const char *dlsym_error = dlerror();
	if (dlsym_error) {
		ssErrorMsg << "Cannot load symbol " << strAPIName.c_str() << ":" << dlsym_error;
		strLog = CUtilities::FormatLog(ERROR_MSG, "CBaseChecker", "Synchronize","error:" + ssErrorMsg.str());
		CUtilities::WriteErrorLog(strLog);

		// close the library
		dlclose(handle);
	}
	
	if (strAPIName == API_GET_HARDWARE_BY_SERIALNUMBER)
	{
		pResult = apiHardwareInfo(strWSMsgError, m_pSerialNumber);
	}
	else
	{
		pResult = apiCollectorInfo(strWSMsgError);
	}

	if (strWSMsgError != "")
	{
		strLog = CUtilities::FormatLog(ERROR_MSG, "CBaseChecker", "CallSnSService","error:" + strWSMsgError);
		CUtilities::WriteErrorLog(strLog);
	}
	// close the library
	dlclose(handle);

	return pResult;
}
