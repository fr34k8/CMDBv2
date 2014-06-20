#include "PhysicalServerInfoUpdateProcessor.h"
#include "../Controller/ServerController.h"
#include "../Controller/ServerInfoChangeController.h"
#include "../Controller/PhysicalServerInfoUpdateController.h"
#include "../Controller/ServerHistoryLogController.h"
#include "../Controller/PhysicalServerNotificationController.h"
#include "../Controller/MailboxController.h"
#include "../Controller/RackController.h"
#include "../Model/ServerInfoChangeModel.h"
#include "../Model/CIHistoryLogModel.h"
#include "../Model/ServerHistoryLogModel.h"
#include "../Model/ServerNotificationModel.h"
#include "../Model/MailboxModel.h"
#include "../Model/RackModel.h"
#include "../Model/RackServerUModel.h"
#include "../Model/RackBayChassisModel.h"
#include "../Model/MongodbModel.h"
#include "../Common/DBCommon.h"
#include "ComputeServerDataProcessor.h"

//#define CMDB_UPDATE_SERVER_URL "https://cmdbv2.vng.com.vn/server/index/update?cid="
#define CMDB_UPDATE_SERVER_URL "https://ip.vng.com.vn/cmdb/server/index/update?cid="
#define APPLICATION_DC_LOCATION "dc_location"
#define APPLICATION_G2_INTERFACE "g2_interface"
#define APPLICATION_INTERFACE "interface"
#define FUNCTION_NOTI_SERVER_LOCATION "dc_noti_server_location"
#define FUNCTION_G2_NOTI_SERVER_INTERFACE "g2_noti_server_interface"
#define FUNCTION_NOTI_SERVER_INTERFACE "noti_server_interface"
#define DEPARTMENT_SNS "SnS"
#define DEPARTMENT_SDK "SDK"
#define LOCATION_QTSC "QTSC"
#define DIVISION_G2 "G2"

CPhysicalServerInfoUpdateProcessor::CPhysicalServerInfoUpdateProcessor(const string& strCfgFile)
:CCIInfoUpdateProcessor(strCfgFile)
{
	m_pCIInfoUpdateController	= new CPhysicalServerInfoUpdateController();
	m_pCIInfoChangeController	= new CServerInfoChangeController();
	m_pCMDBController			= new CServerController();
	m_pCIHistoryLogController	= new CServerHistoryLogController();	
	m_pNotificationController	= new CPhysicalServerNotificationController();
	m_pMailboxController		= new CMailboxController();
	m_pRackController			= new CRackController();	//Object Rack Controller
	
	m_pCIHistoryLogModel		= new CServerHistoryLogModel();
	m_pCIInfoChangeModel		= new CServerInfoChangeModel();
	m_pNotificationModel		= new CServerNotificationModel();
	m_pRackModel				= new CRackModel();			//Object Rack Model
	
	m_pComputeServerDataProcessor = new CComputeServerDataProcessor(strCfgFile);
	m_bIsNotification = true;
	m_bIsMailNotification = true;
}

CPhysicalServerInfoUpdateProcessor::~CPhysicalServerInfoUpdateProcessor(void)
{
	
	if (NULL != m_pRackController)
	{
		delete m_pRackController;
	}

	if (NULL != m_pRackModel)
	{
		delete m_pRackModel;
	}

	if (NULL != m_pComputeServerDataProcessor)
	{
		delete m_pComputeServerDataProcessor;
	}
}

bool CPhysicalServerInfoUpdateProcessor::Connect()
{
	RegisterController(m_pRackController);	//Register Rack Controller
	m_pComputeServerDataProcessor->Connect(); //Connect to Admin Database

	return CCIInfoUpdateProcessor::Connect();

}

bool CPhysicalServerInfoUpdateProcessor::CreateMailNotification(int iActionType, BSONObj boOldCIInfo, BSONObj boNewCIInfo, BSONObj boChangedFields)
{
	bool bResult = false;
	if (NotifyServerLocation(iActionType, boNewCIInfo, boChangedFields))
	{
		bResult = true;
	}
	if (NotifyServerInterface(iActionType, boOldCIInfo, boNewCIInfo, boChangedFields))
	{
		bResult = true;
	}
	return bResult;
}

void CPhysicalServerInfoUpdateProcessor::BuildNetworkInfo(map<string, BSONArrayBuilder*> &map_strbabNetWork, vector<BSONElement> vbeNetwork, BSONElement beClock, string strType)
{
	BSONObj boNetWork, boAddition;
	BSONArrayBuilder *babNetWork;
	BSONElement beNetWorkInfo;
	string strAdapter;

	vector<BSONElement>::iterator it;
	it = vbeNetwork.begin();
	while (it != vbeNetwork.end())
	{
		beNetWorkInfo = *it;
		if (BSON_OBJECT_TYPE != beNetWorkInfo.type())
		{
			it++;
			continue;
		}
		boNetWork = (*it).Obj();
		strAdapter = boNetWork.hasField("adapter") ? boNetWork.getStringField("adapter") : "";
		boNetWork = boNetWork.removeField("adapter");

		if (boNetWork.isEmpty())
		{
			it++;
			continue;
		}
		if (strType.empty())
		{
			boAddition = BSON(
				"updated_at" << CUtilities::UnixTimeToDateTime(beClock.toString(false)) <<
				"updated_by" << "Zabbix"
				);
		}
		else
		{
			boAddition = BSON(
				"status" << strType <<
				"updated_at" << CUtilities::UnixTimeToDateTime(beClock.toString(false)) <<
				"updated_by" << "Zabbix"
				);
		}

		boNetWork = CMongodbModel::MergeBSONObj(&boNetWork, &boAddition);
		map<string, BSONArrayBuilder*>::iterator itMap = map_strbabNetWork.find(strAdapter);
		if (itMap == map_strbabNetWork.end())
		{
			babNetWork = new BSONArrayBuilder();
			map_strbabNetWork[strAdapter] = babNetWork;
		}
		else
		{
			babNetWork = (*itMap).second;
		}
		babNetWork->append(boNetWork);
		it++;
	}

}

BSONArray CPhysicalServerInfoUpdateProcessor::TrackChangeInterface(BSONElement beOldInterface, BSONElement beNewInterface, BSONElement beClock)
{
	BSONArrayBuilder babInterface;
	BSONArrayBuilder *babNetWork;
	map<string, BSONArrayBuilder*> map_strbabNetWork;
	map<string, BSONArrayBuilder*>::iterator itMap;
	vector<BSONElement> vbeOldInterface, vbeNewInterface, vbeDelInterface;
	vector<BSONElement>::iterator itOld, itNew, itDel;
	BSONObj boNetWork, boAddition, boInterface;
	string strAdapter;
	vbeOldInterface = beOldInterface.Array();
	vbeNewInterface = beNewInterface.Array();
	cout << "TrackChangeInterface Old:" << beOldInterface << endl;
	cout << "TrackChangeInterface New:" << beNewInterface << endl;

	if (vbeNewInterface.empty() && vbeOldInterface.empty())
	{
		return babInterface.arr();
	}

	CMongodbModel::TrackChangeArray(vbeOldInterface, vbeNewInterface, vbeDelInterface);

	BuildNetworkInfo(map_strbabNetWork, vbeOldInterface, beClock);
	BuildNetworkInfo(map_strbabNetWork, vbeNewInterface, beClock,"new");
	BuildNetworkInfo(map_strbabNetWork, vbeDelInterface, beClock,"deleted");

	itMap = map_strbabNetWork.begin();
	while (itMap != map_strbabNetWork.end())
	{
		
		boInterface = BSON(
			"adapter" << itMap->first <<
			"amount" << (itMap->second)->arrSize() <<
			"network" << (itMap->second)->arr()
			);
		babInterface << boInterface;
		cout << "Pizza - boInterface:" << boInterface << endl;
		itMap++;
	}
	return babInterface.arr();
}

bool CPhysicalServerInfoUpdateProcessor::NotifyServerInterface(int iActionType, BSONObj boOldCIInfo, BSONObj boNewCIInfo, BSONObj boChangedFields)
{
	if (iActionType != ACTION_TYPE_UPDATE)
	{
		return true;
	}

	bool bNotification = false;
	StringArray arrFieldName;
	BSONObj boNotiData, boNotiModel, boTechOwner;
	BSONObjBuilder bobNotiData;
	BSONElement beTechOwner;
	vector<BSONElement> vbeTechOwner;
	string strTechOwnerList, strApplication, strFunction, strSourceFrom;
	BSONObj boConfigRecord;
	bool bResult = false;
	int iServerStatus;
	/*-- Read Send Mail Config --*/
	try{
		iServerStatus = CMongodbModel::GetIntFieldValue(boNewCIInfo, "status");
		if (SERVER_UNUSED == iServerStatus || SERVER_ERROR == iServerStatus)
		{
			return bResult;
		}
		if (m_pCMDBController->FindSendMailConfig(boConfigRecord, boNewCIInfo, APPLICATION_INTERFACE))
		{
			strApplication = boConfigRecord.hasField("application") ? boConfigRecord.getStringField("application") : "";
			strFunction = boConfigRecord.hasField("function") ? boConfigRecord.getStringField("function") : "";
			strSourceFrom = boConfigRecord.hasField("source_from") ? boConfigRecord.getStringField("source_from") : "";
		}
		else
		{
			return false;
		}
		/*-------------------------------------------------*/
		if (boChangedFields.hasField("public_interface")
			|| boChangedFields.hasField("private_interface")
			|| boChangedFields.hasField("server_name"))
		{
			BSONObj boPrivateInterface, boPublicInterface;
			BSONArray baTrackedPrivateInterface, baTrackedPublicInterface;

			//Init BSONElement array empty
			string strClock = CUtilities::GetCurrTimeStamp().c_str();
			BSONArrayBuilder babPubEmptyArray, babPriEmptyArray;
			BSONArrayBuilder babPubEmptyTracking, babPriEmptyTracking;
			BSONObj boEmptyInterface = BSON("private_interface" << babPubEmptyArray.arr() <<
											"public_interface" << babPriEmptyArray.arr() << 
											"clock" << strClock);

			BSONElement beOldPrivateInterface, beOldPublicInterface;
			BSONElement beNewPrivateInterface, beNewPublicInterface;
			BSONElement beNewClock;

			beOldPrivateInterface = (boOldCIInfo.hasField("private_interface")) ? boOldCIInfo["private_interface"] : boEmptyInterface["private_interface"];
			beOldPublicInterface  = (boOldCIInfo.hasField("public_interface")) ? boOldCIInfo["public_interface"] : boEmptyInterface["public_interface"];

			beNewPrivateInterface = (boNewCIInfo.hasField("private_interface")) ? boNewCIInfo["private_interface"] : boEmptyInterface["private_interface"];
			beNewPublicInterface  = (boNewCIInfo.hasField("public_interface")) ? boNewCIInfo["public_interface"] : boEmptyInterface["public_interface"];
			beNewClock			  = (boNewCIInfo.hasField("clock")) ? boNewCIInfo["clock"] : boEmptyInterface["clock"];

			baTrackedPrivateInterface = TrackChangeInterface(beOldPrivateInterface, beNewPrivateInterface, beNewClock);
			baTrackedPublicInterface = TrackChangeInterface(beOldPublicInterface, beNewPublicInterface, beNewClock);
			/*if (boChangedFields.hasField("private_interface"))
				baTrackedPrivateInterface = TrackChangeInterface(beOldPrivateInterface, beNewPrivateInterface, beNewClock);
			else
				baTrackedPrivateInterface = babPriEmptyTracking.arr();

			if (boChangedFields.hasField("public_interface"))
				baTrackedPublicInterface = TrackChangeInterface(beOldPublicInterface, beNewPublicInterface, beNewClock);
			else
				baTrackedPublicInterface = babPubEmptyTracking.arr();*/
			
			boPrivateInterface = BSON("private_interface" << baTrackedPrivateInterface);

			boPublicInterface = BSON("public_interface" << baTrackedPublicInterface);

			if (boPrivateInterface["private_interface"].Array().empty() 
				&& boPublicInterface["public_interface"].Array().empty() 
				&& !boChangedFields.hasField("server_name"))
			{
				return false;
			}

			bobNotiData.append(boPrivateInterface["private_interface"]);		
			bobNotiData.append(boPublicInterface["public_interface"]);

			if (boNewCIInfo.hasField("code"))
			{
				bobNotiData.append("server_serial", boNewCIInfo.getStringField("code"));
			}
			if (boNewCIInfo.hasField("product_alias"))
			{
				bobNotiData.append("product_alias", boNewCIInfo.getStringField("product_alias"));
			}
			if (boNewCIInfo.hasField("server_name"))
			{
				bobNotiData.append("new_server_name", boNewCIInfo.getStringField("server_name"));
			}
			if (boOldCIInfo.hasField("server_name"))
			{
				bobNotiData.append("old_server_name", boOldCIInfo.getStringField("server_name"));
			}
			CMailboxModel::CreateTechnicalOwnerUserName(boNewCIInfo, boTechOwner);
			vector<BSONElement>::iterator it;
			vbeTechOwner = boTechOwner["technical_owner"].Array();
			it = vbeTechOwner.begin();
			while (it != vbeTechOwner.end())
			{
				beTechOwner = *it;
				strTechOwnerList += CUtilities::RemoveBraces(beTechOwner.toString(false)) + "@vng.com.vn;";
				it++;
			}
			boNotiData = bobNotiData.obj();
			CMailboxModel *pMailboxModel = new CMailboxModel();

			pMailboxModel->SetApplication(strApplication);
			pMailboxModel->SetClock(atoll(CUtilities::GetCurrTimeStamp().c_str()));
			pMailboxModel->SetFunction(strFunction);
			pMailboxModel->SetSourceFrom(strSourceFrom);
			pMailboxModel->SetTechOwner(strTechOwnerList);
			pMailboxModel->SetData(boNotiData);

			boNotiModel = pMailboxModel->GetBSONModel();
			cout << "boNotiModel:" << boNotiModel.toString() << endl;
			bResult = m_pMailboxController->Insert(boNotiModel);
			if (NULL != pMailboxModel)
				delete pMailboxModel;
		}
	}
	catch (exception &ex)
	{
		stringstream strErrorMess;
		strErrorMess << ex.what() << "][" << __FILE__ << "|" << __LINE__;
		string strLog = CUtilities::FormatLog(ERROR_MSG, "CPhysicalServerInfoUpdateProcessor", "NotifyServerInterface", strErrorMess.str());
		CUtilities::WriteErrorLog(ERROR_MSG, strLog);
	}
	return bResult;
}

bool CPhysicalServerInfoUpdateProcessor::NotifyServerLocation(int iActionType, BSONObj boNewCIInfo, BSONObj boChangedFields)
{
	if (iActionType != ACTION_TYPE_UPDATE)
	{
		return true;
	}

	bool bNotification = false;
	StringArray arrFieldName;
	string strSerial, strSite, strRack, strChassis, strId, strLink;
	int iBay, iU;
	BSONObj boNotiData, boNotiModel;
	bool bResult = false;

	arrFieldName.push_back("site");
	arrFieldName.push_back("rack");
	arrFieldName.push_back("u");
	arrFieldName.push_back("chassis");
	arrFieldName.push_back("bay");

	for (int i = 0; i < arrFieldName.size(); i++)
	{
		if (boChangedFields.hasField(arrFieldName[i]))
		{
			bNotification = true;
		}
	}
	if (bNotification)
	{
		strSerial	= boNewCIInfo.hasField("code") ? boNewCIInfo.getStringField("code") : "";
		strSite		= boNewCIInfo.hasField("site") ? boNewCIInfo.getStringField("site") : "";
		strRack		= boNewCIInfo.hasField("rack") ? boNewCIInfo.getStringField("rack") : "";
		strChassis	= boNewCIInfo.hasField("chassis")	? boNewCIInfo.getStringField("chassis") : "";
		iU			= boNewCIInfo.hasField("u")			? boNewCIInfo.getIntField("u") : 0;
		iBay		= boNewCIInfo.hasField("bay")  ? boNewCIInfo.getIntField("bay") : 0;
		strId		= boNewCIInfo.hasField("_id")  ? CUtilities::GetMongoObjId(boNewCIInfo.getField("ci_id").toString(false)) : "";
		strLink		= CMDB_UPDATE_SERVER_URL + strId;

		if (CUtilities::ToUpperString(strSite) == LOCATION_QTSC)
		{
			boNotiData = BSON(
				"serial"	<< strSerial <<
				"site"		<< strSite <<
				"rack"		<< strRack <<
				"chassis"	<< strChassis <<
				"u"			<< iU <<
				"bay"		<< iBay <<
				"link"		<< strLink
				);
			//cout << "Data send mail: " << boNotiData.toString() << endl;
			CMailboxModel *pMailboxModel = new CMailboxModel();
			pMailboxModel->SetApplication(APPLICATION_DC_LOCATION);
			pMailboxModel->SetClock(atoll(CUtilities::GetCurrTimeStamp().c_str()));
			pMailboxModel->SetFunction(FUNCTION_NOTI_SERVER_LOCATION);
			pMailboxModel->SetSourceFrom(DEPARTMENT_SNS);
			pMailboxModel->SetData(boNotiData);

			boNotiModel = pMailboxModel->GetBSONModel();

			bResult = m_pMailboxController->Insert(boNotiModel);
			delete pMailboxModel;
		}
		else
		{
			//cout << "Not notify: " << CUtilities::ToUpperString(strSite) << endl;
			bResult = true;
		}
	}

	return bResult;
}

void CPhysicalServerInfoUpdateProcessor::InsertData(BSONObj boNewCIInfo)
{
	int iServerType = CMongodbModel::GetIntFieldValue(boNewCIInfo, "server_type", 0);
	switch (iServerType)
	{
	case SERVER_U:
		InsertServerUGraphicData(boNewCIInfo);
		break;
	case SERVER_CHASSIS:
		InsertServerChassisGraphicData(boNewCIInfo);
		break;
	}
}

void CPhysicalServerInfoUpdateProcessor::DeleteData(BSONObj boNewCIInfo)
{
	int iServerType = CMongodbModel::GetIntFieldValue(boNewCIInfo, "server_type", 0);
	switch (iServerType)
	{
	case SERVER_U:
		DeleteServerUGraphicData(boNewCIInfo);
		break;
	case SERVER_CHASSIS:
		DeleteServerChassisGraphicData(boNewCIInfo);
		break;
	}
}

void CPhysicalServerInfoUpdateProcessor::UpdateData(BSONObj boOldCIInfo, 
														   BSONObj boNewCIInfo, 
														   BSONObj boChangedFields)
{
	int iServerType = CMongodbModel::GetIntFieldValue(boNewCIInfo, "server_type", 0);
	switch (iServerType)
	{
	case SERVER_U:
		UpdateServerUGraphicData(boOldCIInfo, boNewCIInfo, boChangedFields);
		break;
	case SERVER_CHASSIS:
		UpdateServerChassisGraphicData(boOldCIInfo, boNewCIInfo, boChangedFields);
		break;
	}
}

void CPhysicalServerInfoUpdateProcessor::InsertServerUGraphicData(BSONObj boNewCIInfo)
{
	CRackServerUModel objServerU;
	BSONObj boServerU;
	BSONObj boPushServerU;

	string strRack, strSite, strServerSerial, strServerName, strProductAlias, strProductCode;
	int nFromU, nToU, nUSpace;

	try
	{
		strRack			= boNewCIInfo.hasField("rack") ? boNewCIInfo.getStringField("rack") : "";
		strSite			= boNewCIInfo.hasField("site") ? boNewCIInfo.getStringField("site") : "";
		strServerSerial	= boNewCIInfo.hasField("code") ? boNewCIInfo.getStringField("code") : "";
		strServerName	= boNewCIInfo.hasField("server_name") ? boNewCIInfo.getStringField("server_name") : "";
		strProductAlias = boNewCIInfo.hasField("product_alias") ? boNewCIInfo.getStringField("product_alias") : "";
		strProductCode	= boNewCIInfo.hasField("product_code") ? boNewCIInfo.getStringField("product_code") : "";
		nFromU			= boNewCIInfo.hasField("u") ? boNewCIInfo.getIntField("u") : 0;
		nUSpace			= boNewCIInfo.hasField("u_space") ? boNewCIInfo.getIntField("u_space") : U_SPACE_DEFAULT;
		if (nUSpace < U_SPACE_DEFAULT)
			nUSpace = U_SPACE_DEFAULT;

		nToU			= nFromU + nUSpace - 1;

		if (strRack != "" && strSite != "")
		{
			objServerU["server_serial"]	= strServerSerial;
			objServerU["server_name"]	= strServerName;
			objServerU["product_alias"]	= strProductAlias;
			objServerU["product_code"]	= strProductCode;
			objServerU["from_u"]		= nFromU;
			objServerU["to_u"]			= nToU;
			
			if (objServerU.ToBSONObj(boServerU))
			{
				boPushServerU = m_pRackModel->GetAddServerURecord(boServerU);
				Query qCond = m_pRackModel->IsExistsRackQuery(strRack, strSite);

				//Push new server serial in rack
				m_pRackController->Update(boPushServerU, qCond);
				// Remove available U on Rack
				m_pRackController->RemoveAvailableU(strRack, strSite, nFromU, nToU);
			}
		}
	}
	catch(exception& ex)
	{	
		stringstream strErrorMess;
		string strLog;
		strErrorMess << ex.what() << "][" << __FILE__ << "|" << __LINE__ ;
		strLog = CUtilities::FormatLog(ERROR_MSG, "CPhysicalServerInfoUpdateProcessor", "InsertServerUGraphicData","Exception:" + strErrorMess.str());
		CUtilities::WriteErrorLog(ERROR_MSG, strLog);
	}
}

void CPhysicalServerInfoUpdateProcessor::DeleteServerUGraphicData(BSONObj boNewCIInfo)
{
	BSONObj boPullServerU;
	string strRack, strSite, strServerSerial;
	int nFromU, nToU, nUSpace;
	
	try
	{
		strRack			= boNewCIInfo.hasField("rack") ? boNewCIInfo.getStringField("rack") : "";
		strSite			= boNewCIInfo.hasField("site") ? boNewCIInfo.getStringField("site") : "";
		strServerSerial	= boNewCIInfo.hasField("code") ? boNewCIInfo.getStringField("code") : "";
		
		if (strRack != "" && strSite != "")
		{		
			nFromU			= boNewCIInfo.hasField("u") ? boNewCIInfo.getIntField("u") : 0;
			nUSpace			= boNewCIInfo.hasField("u_space") ? boNewCIInfo.getIntField("u_space") : U_SPACE_DEFAULT;
			if (nUSpace < U_SPACE_DEFAULT)
				nUSpace = U_SPACE_DEFAULT;

			nToU			= nFromU + nUSpace - 1;

			boPullServerU = m_pRackModel->GetDeleteServerURecord(strServerSerial);
			Query qCond = m_pRackModel->IsExistsRackQuery(strRack, strSite);

			//Pull old server serial in rack
			m_pRackController->Update(boPullServerU, qCond);
			// Add available U on Rack
			m_pRackController->AddAvailableU(strRack, strSite, nFromU, nToU);
		}
	}
	catch(exception& ex)
	{	
		stringstream strErrorMess;
		string strLog;
		strErrorMess << ex.what() << "][" << __FILE__ << "|" << __LINE__ ;
		strLog = CUtilities::FormatLog(ERROR_MSG, "CPhysicalServerInfoUpdateProcessor", "DeleteServerUGraphicData","Exception:" + strErrorMess.str());
		CUtilities::WriteErrorLog(ERROR_MSG, strLog);
	}
}

void CPhysicalServerInfoUpdateProcessor::UpdateServerUGraphicData(BSONObj boOldCIInfo, 
																  BSONObj boNewCIInfo, 
																  BSONObj boChangedFields)
{
	CRackServerUModel objServerU;
	BSONObj boServerU;
	BSONObj boPushServerU;
	BSONObj boPullServerU;
	Query qCond;

	string strOldRack, strOldSite, strNewRack, strNewSite;
	string strServerSerial, strServerName, strProductAlias, strProductCode;

	int nFromU, nToU, nUSpace;
	int nOldFromU, nOldToU, nOldUSpace;
	
	try
	{
		if (boChangedFields.hasField("rack") 
			|| boChangedFields.hasField("site") 
			|| boChangedFields.hasField("u")
			|| boChangedFields.hasField("server_name") 
			|| boChangedFields.hasField("product_alias") 
			|| boChangedFields.hasField("product_code"))
		{
			strOldRack		= boOldCIInfo.hasField("rack") ? boOldCIInfo.getStringField("rack") : "";
			strOldSite		= boOldCIInfo.hasField("site") ? boOldCIInfo.getStringField("site") : "";

			strNewRack		= boNewCIInfo.hasField("rack") ? boNewCIInfo.getStringField("rack") : "";
			strNewSite		= boNewCIInfo.hasField("site") ? boNewCIInfo.getStringField("site") : "";
			
			//************************************************
			//Load Server U Info
			//************************************************
			strServerSerial	= boNewCIInfo.hasField("code") ? boNewCIInfo.getStringField("code") : "";
			strServerName	= boNewCIInfo.hasField("server_name") ? boNewCIInfo.getStringField("server_name") : "";
			strProductAlias = boNewCIInfo.hasField("product_alias") ? boNewCIInfo.getStringField("product_alias") : "";
			strProductCode	= boNewCIInfo.hasField("product_code") ? boNewCIInfo.getStringField("product_code") : "";
			nFromU			= boNewCIInfo.hasField("u") ? boNewCIInfo.getIntField("u") : 0;
			nUSpace			= boNewCIInfo.hasField("u_space") ? boNewCIInfo.getIntField("u_space") : U_SPACE_DEFAULT;


			if (nUSpace < U_SPACE_DEFAULT)
				nUSpace = U_SPACE_DEFAULT;

			nToU			= nFromU + nUSpace - 1;
			//************************************************
			if (strOldRack != "" && strOldSite != "")
			{
				boPullServerU = m_pRackModel->GetDeleteServerURecord(strServerSerial);
				qCond = m_pRackModel->IsExistsRackQuery(strOldRack, strOldSite); 
				//Pull old server serial in rack
				m_pRackController->Update(boPullServerU, qCond);
				
				//********************************************
				// Add available U on the Rack		
				if(boOldCIInfo.hasField("u"))
				{
					nOldFromU = boOldCIInfo.getIntField("u");
					nOldUSpace = boOldCIInfo.hasField("u_space") ? boOldCIInfo.getIntField("u_space") : U_SPACE_DEFAULT;
					
					if (nOldUSpace < U_SPACE_DEFAULT)
						nOldUSpace = U_SPACE_DEFAULT;

					nOldToU = nOldFromU + nOldUSpace - 1;
					m_pRackController->AddAvailableU(strOldRack, strOldSite, nOldFromU, nOldToU);		
				}
				//********************************************
			}

			if (strNewRack != "" && strNewSite != "")
			{
				objServerU["server_serial"]	= strServerSerial;
				objServerU["server_name"]	= strServerName;
				objServerU["product_alias"]	= strProductAlias;
				objServerU["product_code"]	= strProductCode;
				objServerU["from_u"]		= nFromU;
				objServerU["to_u"]			= nToU;

				if (objServerU.ToBSONObj(boServerU))
				{
					boPushServerU = m_pRackModel->GetAddServerURecord(boServerU);
					qCond = m_pRackModel->IsExistsRackQuery(strNewRack, strNewSite);
					//Push new server serial in rack
					m_pRackController->Update(boPushServerU, qCond);
					// Remove available U on Rack
					m_pRackController->RemoveAvailableU(strNewRack, strNewSite, nFromU, nToU);
				}
			}
		}
	}
	catch(exception& ex)
	{	
		stringstream strErrorMess;
		string strLog;
		strErrorMess << ex.what() << "][" << __FILE__ << "|" << __LINE__ ;
		strLog = CUtilities::FormatLog(ERROR_MSG, "CPhysicalServerInfoUpdateProcessor", "UpdateServerUGraphicData","Exception:" + strErrorMess.str());
		CUtilities::WriteErrorLog(ERROR_MSG, strLog);
	}
}

void CPhysicalServerInfoUpdateProcessor::InsertServerChassisGraphicData(BSONObj boNewCIInfo)
{
	CRackBayChassisModel objBayChassisModel;
	BSONObj boPushBayChassis;
	BSONObj boPullBayChassis;
	BSONObj boBayChassisInfo;

	string strRack, strSite, strIPChassis;
	//Atribute BayChassis
	string strServerSerial, strServerName, strProductAlias, strProductCode;
	int nBay;

	try
	{	strRack		 = boNewCIInfo.hasField("rack") ? boNewCIInfo.getStringField("rack") : "";
		strSite		 = boNewCIInfo.hasField("site") ? boNewCIInfo.getStringField("site") : "";
		strIPChassis = boNewCIInfo.hasField("chassis") ? boNewCIInfo.getStringField("chassis") : "";
		//Init Attribute of Bay Chassis
		nBay			= boNewCIInfo.hasField("bay") ? boNewCIInfo.getIntField("bay") : 0;
		strServerSerial = boNewCIInfo.hasField("code") ? boNewCIInfo.getStringField("code") : "";
		strServerName	= boNewCIInfo.hasField("server_name") ? boNewCIInfo.getStringField("server_name") : "";
		strProductAlias = boNewCIInfo.hasField("product_alias") ? boNewCIInfo.getStringField("product_alias") : "";
		strProductCode	= boNewCIInfo.hasField("product_code") ? boNewCIInfo.getStringField("product_code") : "";
		
		//Found chassis in rack
		Query qRackChassisCond = m_pRackModel->IsExistsChassisQuery(strRack, strSite, strIPChassis);

		if(m_pRackController->IsExisted(qRackChassisCond))
		{
			//Assign Value to Rack Bay Chassis Model
			objBayChassisModel["bay_id"]		= nBay;
			objBayChassisModel["server_serial"]	= strServerSerial;
			objBayChassisModel["server_name"]	= strServerName;
			objBayChassisModel["product_alias"]	= strProductAlias;
			objBayChassisModel["product_code"]	= strProductCode;
			
			if(objBayChassisModel.ToBSONObj(boBayChassisInfo))
			{
				//Pull Bay Chassis If Exists
				boPullBayChassis = m_pRackModel->GetDeleteServerChassisRecord(strServerSerial);
				m_pRackController->Update(boPullBayChassis, qRackChassisCond);

				//Push New Bay Chassis 
				boPushBayChassis = m_pRackModel->GetAddServerChassisRecord(boBayChassisInfo);
				m_pRackController->Update(boPushBayChassis, qRackChassisCond);
			}
		}
		else
		{
			//NOTIFY THROUGH EMAIL
			BSONObj boDataInfo, boMailInfo;
			//Get Data to send mail
			boDataInfo = BSON("rack" << strRack <<
							  "site" << strSite <<
							  "chassis" << strIPChassis <<
							  "bay" << nBay <<
							  "server_serial" << strServerSerial <<
							  "server_name" << strServerName << 
							  "product_alias" << strProductAlias <<
							  "product_code" << strProductCode);
			CMailboxModel objMailboxModel;
			objMailboxModel.SetApplication(APP_BACKEND_HANDLE_PHYSICAL_SERVER);
			objMailboxModel.SetFunction(FUNCTION_GRAPHIC_SERVER_CHASSIS);
			objMailboxModel.SetClock(atoll(CUtilities::GetCurrTimeStamp().c_str()));
			objMailboxModel.SetSourceFrom(DEPARTMENT_SNS);
			objMailboxModel.SetData(boDataInfo);
			
			boMailInfo = objMailboxModel.GetBSONModel();
			m_pMailboxController->Insert(boMailInfo);
		}
	}
	catch(exception& ex)
	{	
		stringstream strErrorMess;
		string strLog;
		strErrorMess << ex.what() << "][" << __FILE__ << "|" << __LINE__ ;
		strLog = CUtilities::FormatLog(ERROR_MSG, "CPhysicalServerInfoUpdateProcessor", "InsertServerChassisGraphicData","Exception:" + strErrorMess.str());
		CUtilities::WriteErrorLog(ERROR_MSG, strLog);
	}
}

void CPhysicalServerInfoUpdateProcessor::DeleteServerChassisGraphicData(BSONObj boNewCIInfo)
{
	string strRack, strSite, strIPChassis, strServerSerial;
	BSONObj boPullBayChassis;
	Query qRackChassisCond;

	try
	{
		strRack			= boNewCIInfo.hasField("rack") ? boNewCIInfo.getStringField("rack") : "";
		strSite			= boNewCIInfo.hasField("site") ? boNewCIInfo.getStringField("site") : "";
		strIPChassis	= boNewCIInfo.hasField("chassis") ? boNewCIInfo.getStringField("chassis") : "";
		strServerSerial = boNewCIInfo.hasField("code") ? boNewCIInfo.getStringField("code") : "";
		
		//Get Chassis Condition
		qRackChassisCond = m_pRackModel->IsExistsChassisQuery(strRack, strSite, strIPChassis);
		//Pull Bay Chassis If Exists
		boPullBayChassis = m_pRackModel->GetDeleteServerChassisRecord(strServerSerial);
		m_pRackController->Update(boPullBayChassis, qRackChassisCond);
	}
	catch(exception& ex)
	{
		stringstream strErrorMess;
		string strLog;
		strErrorMess << ex.what() << "][" << __FILE__ << "|" << __LINE__ ;
		strLog = CUtilities::FormatLog(ERROR_MSG, "CPhysicalServerInfoUpdateProcessor", "DeleteServerChassisGraphicData","Exception:" + strErrorMess.str());
		CUtilities::WriteErrorLog(ERROR_MSG, strLog);
	}
}


void CPhysicalServerInfoUpdateProcessor::UpdateServerChassisGraphicData(BSONObj boOldCIInfo, 
																		BSONObj boNewCIInfo, 
																		BSONObj boChangedFields)
{	
	CRackBayChassisModel objBayChassisModel;
	
	BSONObj boPushNewBayChassis;
	BSONObj boPullOldBayChassis;
	BSONObj boNewBayChassisInfo;

	Query qOldRackChassis;
	Query qNewRackChassis;

	string strOldRack, strOldSite, strOldIPChassis;
	string strNewRack, strNewSite, strNewIPChassis;

	string strServerSerial, strServerName, strProductAlias, strProductCode;
	int nBay;
	int iServerStatus;

	try
	{
		strServerSerial	= boNewCIInfo.hasField("code") ? boNewCIInfo.getStringField("code") : "";
		
		if (strServerSerial != "")
		{
			if (boChangedFields.hasField("chassis")
				|| boChangedFields.hasField("bay")
				|| boChangedFields.hasField("server_name")
				|| boChangedFields.hasField("product_alias")
				|| boChangedFields.hasField("product_code")
				|| boChangedFields.hasField("rack")
				|| boChangedFields.hasField("site")
				|| boChangedFields.hasField("status"))

			{
				//Pull Old Bay Chassis out of Chassis
				strOldRack		= boOldCIInfo.hasField("rack") ? boOldCIInfo.getStringField("rack") : "";
				strOldSite		= boOldCIInfo.hasField("site") ? boOldCIInfo.getStringField("site") : "";
				strOldIPChassis = boOldCIInfo.hasField("chassis") ? boOldCIInfo.getStringField("chassis") : "";
				
				qOldRackChassis		= m_pRackModel->IsExistsChassisQuery(strOldRack, strOldSite, strOldIPChassis);
				boPullOldBayChassis = m_pRackModel->GetDeleteServerChassisRecord(strServerSerial);

				//Push New Bay Chassis into Chassis of Rack
				strNewRack		= boNewCIInfo.hasField("rack") ? boNewCIInfo.getStringField("rack") : "";
				strNewSite		= boNewCIInfo.hasField("site") ? boNewCIInfo.getStringField("site") : "";
				strNewIPChassis = boNewCIInfo.hasField("chassis") ? boNewCIInfo.getStringField("chassis") : "";
				//Init Attribute Bay Chassis
				strServerName	= boNewCIInfo.hasField("server_name") ? boNewCIInfo.getStringField("server_name") : "";
				strProductAlias = boNewCIInfo.hasField("product_alias") ? boNewCIInfo.getStringField("product_alias") : "";
				strProductCode	= boNewCIInfo.hasField("product_code") ? boNewCIInfo.getStringField("product_code") : "";
				nBay			= boNewCIInfo.hasField("bay") ? boNewCIInfo.getIntField("bay") : 0;
				
				//Get Server Status
				iServerStatus	= boNewCIInfo.hasField("status") ? boNewCIInfo.getIntField("status") : UNKNOWN;

				qNewRackChassis	= m_pRackModel->IsExistsChassisQuery(strNewRack, strNewSite, strNewIPChassis);
				//If new Rack Chassis exists 
				//then will remove server in old rack chassis
				if (m_pRackController->IsExisted(qNewRackChassis))
				{
					m_pRackController->Update(boPullOldBayChassis, qOldRackChassis);
					objBayChassisModel["bay_id"]		= nBay;
					objBayChassisModel["server_serial"]	= strServerSerial;
					objBayChassisModel["server_name"]	= strServerName;
					objBayChassisModel["product_alias"]	= strProductAlias;
					objBayChassisModel["product_code"]	= strProductCode;

					if (objBayChassisModel.ToBSONObj(boNewBayChassisInfo))
					{
						boPushNewBayChassis = m_pRackModel->GetAddServerChassisRecord(boNewBayChassisInfo);
						m_pRackController->Update(boPushNewBayChassis, qNewRackChassis);
					}
				}
				else
				{
					if (iServerStatus != SERVER_UNUSED && iServerStatus != SERVER_ERROR)
					{
						//NOTIFY THROUGH EMAIL
						BSONObj boDataInfo, boMailInfo;
						//Get Data to send mail
						boDataInfo = BSON("rack" << strNewRack <<
										  "site" << strNewSite <<
										  "chassis" << strNewIPChassis <<
										  "bay" << nBay <<
										  "server_serial" << strServerSerial <<
										  "server_name" << strServerName << 
										  "product_alias" << strProductAlias <<
										  "product_code" << strProductCode);

						CMailboxModel objMailboxModel;
						objMailboxModel.SetApplication(APP_BACKEND_HANDLE_PHYSICAL_SERVER);
						objMailboxModel.SetFunction(FUNCTION_GRAPHIC_SERVER_CHASSIS);
						objMailboxModel.SetClock(atoll(CUtilities::GetCurrTimeStamp().c_str()));
						objMailboxModel.SetSourceFrom(DEPARTMENT_SNS);
						objMailboxModel.SetData(boDataInfo);
						
						boMailInfo = objMailboxModel.GetBSONModel();
						m_pMailboxController->Insert(boMailInfo);
					}
					else
					{
						m_pRackController->Update(boPullOldBayChassis, qOldRackChassis);
					}
				}
			}
		}
	}
	catch(exception& ex)
	{
		stringstream strErrorMess;
		string strLog;
		strErrorMess << ex.what() << "][" << __FILE__ << "|" << __LINE__ ;
		strLog = CUtilities::FormatLog(ERROR_MSG, "CPhysicalServerInfoUpdateProcessor", "UpdateServerChassisGraphicData","Exception:" + strErrorMess.str());
		CUtilities::WriteErrorLog(ERROR_MSG, strLog);
	}
}

void CPhysicalServerInfoUpdateProcessor::UpdateSpecialDataInfo(BSONObj boOldCIInfo, BSONObj boNewCIInfo, BSONObj boChangedFields)
{
	if (boChangedFields.hasField("product_code"))
	{
		m_pComputeServerDataProcessor->ComputeTechnicalOwnerInfo(boNewCIInfo);
	}

}

void CPhysicalServerInfoUpdateProcessor::InsertSpecialDataInfo(mongo::BSONObj boNewCIInfo)
{
	string strProductCode = "";
	strProductCode = CMongodbModel::GetStringFieldValue(boNewCIInfo, "product_code", "");
	if (strProductCode != "" && strProductCode != "NA")
		m_pComputeServerDataProcessor->ComputeTechnicalOwnerInfo(boNewCIInfo);
}