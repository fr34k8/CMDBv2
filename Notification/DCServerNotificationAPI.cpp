#include "DCServerNotificationAPI.h"
#include "../Model/NotificationModel.h"
#include "../Model/MailboxModel.h"
#include "../Common/DBCommon.h"

CDCServerNotificationAPI::CDCServerNotificationAPI(void)
{
}

CDCServerNotificationAPI::~CDCServerNotificationAPI(void)
{
}

void CDCServerNotificationAPI::Convert2JSON(CNotificationModel* pData, BSONObj &boRecord)
{
	BSONObj boData, boTemp, boMac, boTechnicalOwner, boConverted;
	BSONElement beTemp;
	vector<BSONElement> vbePriInterface, vbePubInterface, vbeTechnicalOwner;
	vector<BSONElement>::iterator it;
	BSONArrayBuilder babInterface;
	BSONArrayBuilder babTechnicalOwner;
	BSONObjBuilder bobServerInfo;
	BSONObjBuilder bobTechnicalOwnerInfo;
	map<string, string>::iterator mit;
	map<string, string> mapServerAPIField;
	mapServerAPIField["SerialNumber"] = "code";
	mapServerAPIField["ServerName"] = "server_name";
	mapServerAPIField["Model"] = "server_model";
	mapServerAPIField["Site"] = "site";
	mapServerAPIField["Rack"] = "rack";
	mapServerAPIField["RackUnit"] = "u";
	mapServerAPIField["Size"] = "u_space";
	mapServerAPIField["IPChassis"] = "chassis";
	mapServerAPIField["Bay"] = "bay";
	mapServerAPIField["IPConsole"] = "ip_console";
	mapServerAPIField["ProductCode"] = "product_code";
	mapServerAPIField["Department"] = "department_alias";
	mapServerAPIField["Division"] = "division_alias";
	try{
		boData = *pData;

		/*
		*	Interface Builder
		*/
		if (boData.hasField("private_interface"))
		{
			if (boData["private_interface"].type() == BSON_ARRAY_TYPE)
			{
				vbePriInterface = boData["private_interface"].Array();
				for (it = vbePriInterface.begin(); it != vbePriInterface.end(); it++)
				{
					beTemp = *it;
					boTemp = beTemp.Obj();
					if (boTemp.hasField("mac_address")){
						babInterface << boTemp["mac_address"];
					}
				}
			}
		}
		if (boData.hasField("public_interface"))
		{
			if (boData["public_interface"].type() == BSON_ARRAY_TYPE)
			{
				vbePubInterface = boData["public_interface"].Array();
				for (it = vbePubInterface.begin(); it != vbePubInterface.end(); it++)
				{
					beTemp = *it;
					boTemp = beTemp.Obj();
					if (boTemp.hasField("mac_address")){
						babInterface << boTemp["mac_address"];
					}
				}
			}
		}
		boMac = BSON("MacAddress" << babInterface.arr());

		CMailboxModel::CreateTechnicalOwnerUserName(boData, boTemp);
		vector<BSONElement> vbeTechOwner;
		vector<BSONElement>::iterator itTechOwner;
		string strTechOwnerList;

		vbeTechOwner = boTemp["technical_owner"].Array();
		itTechOwner = vbeTechOwner.begin();
		while (itTechOwner != vbeTechOwner.end())
		{
			strTechOwnerList += CUtilities::RemoveBraces((*itTechOwner).toString(false)) + ";";
			itTechOwner++;
		}
		boTechnicalOwner = BSON("TechnicalOwner" << strTechOwnerList);
		/*
		*	Server Info Builder
		*/
		boConverted = CMongodbModel::ConvertBSONObj(boData, mapServerAPIField);
		boConverted = CMongodbModel::MergeBSONObj(&boConverted, &boMac);
		boConverted = CMongodbModel::MergeBSONObj(&boConverted, &boTechnicalOwner);

		/*
		*	Notification BSONObj
		*/
		boRecord = BSON(
			"serial" << boConverted.getField("SerialNumber") <<
			"action_type" << boData.getField("action_type") <<
			"server_info" << boConverted
			);
	}
	catch (exception &ex)
	{
		stringstream strErrorMess;
		string strLog;
		strErrorMess << ex.what() << "][" << __FILE__ << "|" << __LINE__;
		strLog = CUtilities::FormatLog(ERROR_MSG, "CDCServerNotificationAPI", "Convert2JSON", "exception:" + strErrorMess.str() + "|boData" + boData.toString());
		CUtilities::WriteErrorLog(ERROR_MSG, strLog);
	}
}
