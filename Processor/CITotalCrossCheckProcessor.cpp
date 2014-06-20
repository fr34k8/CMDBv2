#include "CITotalCrossCheckProcessor.h"
#include "../Config/ConfigFile.h"
#include "../Common/DBCommon.h"
#include <dlfcn.h>

CCITotalCrossCheckProcessor::CCITotalCrossCheckProcessor(const string& strFileName)
:CProcessor(strFileName)
{
}

CCITotalCrossCheckProcessor::~CCITotalCrossCheckProcessor(void)
{
}

void CCITotalCrossCheckProcessor::ComparationProceed()
{
	string strBuffer;
	strBuffer = GetDataAPI();
	cout << strBuffer;
}

string CCITotalCrossCheckProcessor::GetDataAPI()
{
	string strBuffer = "";
	stringstream strErrorMess;
	string strLog;
	try{
		// open the library
		void* handle = dlopen((const char*)m_strLibName.c_str(), RTLD_LAZY);
		if (!handle)
		{
			strErrorMess << "Cannot open library: " << dlerror() << __FILE__ << "|" << __LINE__;
			strLog = CUtilities::FormatLog(ERROR_MSG, "CCITotalCrossCheckProcessor", "GetDataAPI", "error:" + strErrorMess.str());
			CUtilities::WriteErrorLog(ERROR_MSG, strLog);
			return strBuffer;
		}

		// reset errors
		dlerror();
		dataAPI apiNotifyInfo = (dataAPI)dlsym(handle, (const char*)m_strAPIName.c_str());
		const char *dlsym_error = dlerror();
		if (dlsym_error) {
			strErrorMess << "Cannot load symbol " << m_strAPIName.c_str() << ":" << dlsym_error;
			strLog = CUtilities::FormatLog(ERROR_MSG, "CCITotalCrossCheckProcessor", "GetDataAPI", "error:" + strErrorMess.str());
			CUtilities::WriteErrorLog(ERROR_MSG, strLog);

			// close the library
			dlclose(handle);
			return strBuffer;
		}
		strBuffer = apiNotifyInfo();
	}
	catch (exception& ex)
	{
		strErrorMess << ex.what() << "][" << __FILE__ << "|" << __LINE__;
		strLog = CUtilities::FormatLog(ERROR_MSG, "CCITotalCrossCheckProcessor", "GetDataAPI", "Exception:" + strErrorMess.str());
		CUtilities::WriteErrorLog(ERROR_MSG, strLog);
	}
	return strBuffer;
}