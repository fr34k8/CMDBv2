#include "MISProductNotificationAPI.h"
#include "../Controller/MailboxController.h"
#include "../Model/NotificationModel.h"
#include "../Model/MailboxModel.h"

#define APPLICATION_MIS_LOCATION "mis_operation_department"
#define FUNCTION_NOTI_PRODUCT_OPERATION "mis_noti_operation_department"
#define DEPARTMENT_SDK "SDK"
#define LOCATION_QTSC "QTSC"

CMISProductNotificationAPI::CMISProductNotificationAPI(void)
{
}

CMISProductNotificationAPI::~CMISProductNotificationAPI(void)
{
}

void CMISProductNotificationAPI::Convert2JSON(CNotificationModel* pData, BSONObj &boRecord)
{
	//{"data":[{"request_code":"RP130314/004","operation_department":"BO6"}],"source":"SDK"}
	BSONArrayBuilder babElement;
	BSONObjBuilder bobProductInfo;
	map<string, string>::iterator mit;
	map<string, string> mapAPIField;
	mapAPIField["department_alias"] = "operation_department";
	mapAPIField["request_code"] = "request_code";

	BSONObj boTemp = *pData;
	for (mit = mapAPIField.begin(); mit != mapAPIField.end(); mit++)
	{
		if (boTemp.hasField(mit->first)){
			bobProductInfo.append(mit->second, boTemp.getStringField(mit->first.c_str()));
		}
		else{
			bobProductInfo.append(mit->second, "");
		}
	}

	babElement << bobProductInfo.obj();
	boRecord = BSON(
		"data" << babElement.arr() <<
		"source" << "SDK"
		);
}

//void CMISProductNotificationAPI::CreateMailInfo(CNotificationModel* pData)
//{
//	Connect();
//	vector<BSONElement> vbeMailInfo;
//	BSONObj boMailInfo, boResult, boTemp;
//	Convert2JSON(pData, boTemp);
//	vbeMailInfo = boTemp["data"].Array();
//	boMailInfo = vbeMailInfo[0].Obj();
//	CMailboxModel *pMailboxModel = new CMailboxModel();
//	pMailboxModel->SetApplication(APPLICATION_MIS_LOCATION);
//	pMailboxModel->SetClock(atoll(CUtilities::GetCurrTimeStamp().c_str()));
//	pMailboxModel->SetFunction(FUNCTION_NOTI_PRODUCT_OPERATION);
//	pMailboxModel->SetSourceFrom(DEPARTMENT_SDK);
//	pMailboxModel->SetData(boMailInfo);
//	boResult = pMailboxModel->GetBSONModel();
//	cout << "CreateMailInfo :" << boResult << endl;
//	m_pMailboxController->Insert(boResult);
//	delete pMailboxModel;
//}