#include "SnSServerNotificationAPI.h"
#include "../Model/NotificationModel.h"
#include "../Common/DBCommon.h"

CSnSServerNotificationAPI::CSnSServerNotificationAPI(void)
{
}

CSnSServerNotificationAPI::~CSnSServerNotificationAPI(void)
{
}

void CSnSServerNotificationAPI::Convert2JSON(CNotificationModel* pData, BSONObj &boRecord)
{
	BSONObj boData, boTemp;
	BSONObjBuilder bobServerInfo;
	map<string, string>::iterator mit;
	map<string, string> mapServerAPIField;
	mapServerAPIField["code"] = "code";
	mapServerAPIField["server_name"] = "server_name";
	boData = *pData;
	try{
		/*
		*	Server Info Builder
		*/
		for (mit = mapServerAPIField.begin(); mit != mapServerAPIField.end(); mit++)
		{
			if (boData.hasField(mit->first)){
				bobServerInfo.append(mit->second, boData.getStringField(mit->first.c_str()));
			}
			else{
				bobServerInfo.append(mit->second, "");
			}
		}

		boTemp = bobServerInfo.obj();
		boRecord = BSON(
			"serial" << boTemp["code"] <<
			"server_name" << boTemp["server_name"]
			);
	}
	catch (exception &ex)
	{
		stringstream strErrorMess;
		string strLog;
		strErrorMess << ex.what() << "][" << __FILE__ << "|" << __LINE__;
		strLog = CUtilities::FormatLog(ERROR_MSG, "CSnSServerNotificationAPI", "Convert2JSON", "exception:" + strErrorMess.str() + "|boData" + boData.toString());
		CUtilities::WriteErrorLog(ERROR_MSG, strLog);
	}
}
