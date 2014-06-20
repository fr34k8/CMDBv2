#include "SynchronizationData.h"
#include "../Model/CollectorModel.h"
#include <dlfcn.h>

CSynchronizationData::CSynchronizationData(void)
{
}

CSynchronizationData::~CSynchronizationData(void)
{
}

bool CSynchronizationData::Synchronize(char* pUrlParameter, CCollectorModel* pData, char** _pResult)
{
	bool bResult = true;
	
	stringstream strErrorMess;
	string strLog;

	// open the library
	void* handle = dlopen((const char*)pData->GetLibraryName().c_str(), RTLD_LAZY);
	
	if (!handle) 
	{		
		strErrorMess << "Cannot open library: " << dlerror() << __FILE__ << "|" << __LINE__;		
		strLog = CUtilities::FormatLog(ERROR_MSG, "CSynchronizationData", "Synchronize","error:" + strErrorMess.str());
		CUtilities::WriteErrorLog(ERROR_MSG, strLog);
		return false;
	}

	// reset errors
	dlerror();
	CollectorInfoChange apiCollectorInfo = (CollectorInfoChange)dlsym(handle, (const char*)pData->GetAPIName().c_str());
	const char *dlsym_error = dlerror();
	if (dlsym_error) {
		strErrorMess << "Cannot load symbol " << pData->GetAPIName().c_str() << ":" << dlsym_error;
		strLog = CUtilities::FormatLog(ERROR_MSG, "CSynchronizationData", "Synchronize","error:" + strErrorMess.str());
		CUtilities::WriteErrorLog(ERROR_MSG, strLog);

		// close the library
		dlclose(handle);
	}

	*_pResult = apiCollectorInfo(pUrlParameter);
	// close the library
	dlclose(handle);

	return bResult;
}
