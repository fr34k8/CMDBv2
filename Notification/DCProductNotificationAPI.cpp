#include "DCProductNotificationAPI.h"
#include "../Controller/MailboxController.h"
#include "../Model/NotificationModel.h"
#include "../Model/MailboxModel.h"

#define CMDB_UPDATE_PRODUCT_URL "https://cmdbv2.vng.com.vn/product/index/update?cid="
#define APPLICATION_DC_PRODUCT "dc_product"
#define FUNCTION_NOTI_PRODUCT "dc_noti_product"
#define DEPARTMENT_SDK "SDK"
#define LOCATION_QTSC "QTSC"

CDCProductNotificationAPI::CDCProductNotificationAPI(void)
{
}

CDCProductNotificationAPI::~CDCProductNotificationAPI(void)
{
}

void CDCProductNotificationAPI::Convert2JSON(CNotificationModel* pData, BSONObj &boRecord)
{
	BSONObj boConverted;
	map<string, string>::iterator mit;
	map<string, string> mapAPIField;
	mapAPIField["action_type"] = "action_type";
	mapAPIField["code"] = "code";
	mapAPIField["status"] = "status";
	mapAPIField["alias"] = "alias";
	mapAPIField["department_alias"] = "department_alias";
	mapAPIField["division_alias"] = "division_alias";

	BSONObj boTemp = *pData;
	boConverted = CMongodbModel::ConvertBSONObj(boTemp, mapAPIField);
	try{
		boRecord =
			BSON(
			"action_type" << boConverted["action_type"] <<
			"serial" << boConverted["code"] <<
			"status" << boConverted["status"] <<
			"product_info" << BSON(
			"ProductCode" << boConverted["code"] <<
			"ProductName" << boConverted["alias"] <<
			"ProductAlias" << boConverted["alias"] <<
			"ProductDepartment" << boConverted["department_alias"] <<
			"ProductDivision" << boConverted["division_alias"]
				)
			);
	}
	catch (exception &ex)
	{
		stringstream strErrorMess;
		string strLog;
		strErrorMess << ex.what() << "][" << __FILE__ << "|" << __LINE__;
		strLog = CUtilities::FormatLog(ERROR_MSG, "CDCProductNotificationAPI", "Convert2JSON", "exception:" + strErrorMess.str() + "|boTemp" + boTemp.toString());
		CUtilities::WriteErrorLog(ERROR_MSG, strLog);
	}
}
//
//void CDCProductNotificationAPI::CreateMailInfo(CNotificationModel* pData)
//{
//	Connect();
//	BSONObj boMailInfo, boResult;
//	BSONObj boTemp;
//	Convert2JSON(pData, boTemp);
//	boMailInfo = boTemp["product_info"].Obj();
//	CMailboxModel *pMailboxModel = new CMailboxModel();
//	pMailboxModel->SetApplication(APPLICATION_DC_PRODUCT);
//	pMailboxModel->SetClock(atoll(CUtilities::GetCurrTimeStamp().c_str()));
//	pMailboxModel->SetFunction(FUNCTION_NOTI_PRODUCT);
//	pMailboxModel->SetSourceFrom(DEPARTMENT_SDK);
//	pMailboxModel->SetData(boMailInfo);
//	boResult = pMailboxModel->GetBSONModel();
//	cout << "CreateMailInfo :" << boResult << endl;
//	m_pMailboxController->Insert(boResult);
//	delete pMailboxModel;
//}