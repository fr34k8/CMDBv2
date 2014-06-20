#include "NotificationAPI.h"
#include "../Model/NotificationModel.h"
#include "../Controller/MailboxController.h"
#include "../Config/ConfigFile.h"
#include "../Common/DBCommon.h"
#include <dlfcn.h>

CNotificationAPI::CNotificationAPI(void)
{
	//m_pMailboxController = new CMailboxController();
	CConfigFile::GetInstance("Config.ini");
}

CNotificationAPI::~CNotificationAPI(void)
{
	/*if (NULL != m_pMailboxController)
	{
		delete m_pMailboxController;
	}*/
}

int CNotificationAPI::Notify(CNotificationModel* pData)
{
	int iResponse = API_ACTION_ERROR;
	BSONObj boData;
	stringstream strErrorMess;
	string strLog, strData, strResponse;
	int iActionType;
	try{
		Convert2JSON(pData, boData);
		strData = boData.jsonString();
		//cout << "JSON Convert API : " << strData << endl;
		// open the library
		void* handle = dlopen((const char*)pData->GetLibraryName().c_str(), RTLD_LAZY);
		if (!handle)
		{
			strErrorMess << "Cannot open library: " << dlerror() << __FILE__ << "|" << __LINE__;
			strLog = CUtilities::FormatLog(ERROR_MSG, "CNotificationAPI", "Notify", "error:" + strErrorMess.str());
			CUtilities::WriteErrorLog(ERROR_MSG, strLog);
			return API_ACTION_ERROR;
		}

		// reset errors
		dlerror();
		NotifyInfoChange apiNotifyInfo = (NotifyInfoChange)dlsym(handle, (const char*)pData->GetAPIName().c_str());
		const char *dlsym_error = dlerror();
		if (dlsym_error) {
			strErrorMess << "Cannot load symbol " << pData->GetAPIName().c_str() << ":" << dlsym_error;
			strLog = CUtilities::FormatLog(ERROR_MSG, "CNotificationAPI", "Notify", "error:" + strErrorMess.str());
			CUtilities::WriteErrorLog(ERROR_MSG, strLog);

			// close the library
			dlclose(handle);
		}
		iResponse = apiNotifyInfo(strData, strResponse);
		cout << "strResponse : " << strResponse << endl << endl;
		pData->SetResponse(strResponse); // set response to insert history
		if (iResponse == API_ACTION_SUCCESS){
			strLog = CUtilities::FormatLog(INFO_MSG, "CNotificationAPI", "Notify", "APIName:" + pData->GetAPIName() + "|Notified:" + strData + "|Response:" + strResponse);
			CUtilities::WriteErrorLog(INFO_MSG, strLog);
		}
		else
		{

			strLog = CUtilities::FormatLog(ERROR_MSG, "CNotificationAPI", "Notify", "APIName:" + pData->GetAPIName() + "|" + "Notified:" + strData + "|Response:" + strResponse);
			CUtilities::WriteErrorLog(ERROR_MSG, strLog);
		}
		// close the library
		dlclose(handle);
	}
	catch (exception &ex)
	{
		strErrorMess << ex.what() << "][" << __FILE__ << "|" << __LINE__;
		strLog = CUtilities::FormatLog(ERROR_MSG, "CNotificationAPI", "Notify", "exception:" + strErrorMess.str() + "|strData" + strData + "|Response:" + strResponse);
		CUtilities::WriteErrorLog(ERROR_MSG, strLog);
	}
	return iResponse;
}

//bool CNotificationAPI::Connect()
//{
//	// Register controllers before connecting to database
//	RegisterController(m_pMailboxController, MONGODB_MAILBOX_GROUP);
//
//	return CProcessor::Connect();
//}
