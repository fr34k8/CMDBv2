#include "RackController.h"
#include "../Common/DBCommon.h"
#include "../Model/RackSwitchModel.h"
#include "../Model/RackModel.h"
#include "../Model/RackSwitchChassisModel.h"
#include "../Model/RackPDUModel.h"
#include "../Model/MongodbModel.h"
#include "MailboxController.h"

CRackController::CRackController(void)
{
	m_strTableName = TBL_RACK;
}

CRackController::~CRackController(void)
{
}

bool CRackController::FindRackByNameAndSite(const string& strRack, 
											const string& strSite, 
											auto_ptr<DBClientCursor>& ptrResultCursor)
{
	CRackModel objRackModel;	
	//auto_ptr<DBClientCursor> ptrResultCursor = auto_ptr<DBClientCursor>();
	Query qCond = objRackModel.IsExistsRackQuery(strRack, strSite);

	cout << strRack << " - " << strSite << endl;

	if (!Find(ptrResultCursor, qCond))
	{
		return false;
	}


	if (!ptrResultCursor->more())
	{
		return false;
	}

	//boRackInfo = ptrResultCursor->nextSafe();

	return true;
}

void CRackController::RemoveAvailableU(const string& strRack, const string& strSite, 
									   int nFromU, int nToU)
{	
	CRackModel objRackModel;
	BSONObj boRackInfo;
	auto_ptr<DBClientCursor> ptrResultCursor = auto_ptr<DBClientCursor>();

	if (!FindRackByNameAndSite(strRack, strSite, ptrResultCursor))
	{
		return;
	}

	boRackInfo = ptrResultCursor->nextSafe();
	objRackModel.RemoveAvailableU(boRackInfo, nFromU, nToU);	
	//Save to do
	Query qCond = objRackModel.IsExistsRackQuery(strRack, strSite);
	Update(BSON("$set" << boRackInfo), qCond);
}

void CRackController::AddAvailableU(const string& strRack, const string& strSite, 
									int nFromU, int nToU)
{	
	CRackModel objRackModel;
	BSONObj boRackInfo;
	BSONObj boUpdatedRackInfo;
	auto_ptr<DBClientCursor> ptrResultCursor = auto_ptr<DBClientCursor>();

	if (!FindRackByNameAndSite(strRack, strSite, ptrResultCursor))
	{
		return;
	}
	boRackInfo = ptrResultCursor->nextSafe();
	objRackModel.AddAvailableU(boRackInfo, nFromU, nToU);	
	//Save to do
	Query qCond = objRackModel.IsExistsRackQuery(strRack, strSite);
	Update(BSON("$set" << boRackInfo), qCond);
}

void CRackController::AddRackSwitch(const BSONObj& boSwitchInfo)
{
	CRackSwitchModel objSwitchModel;
	CRackModel objRackModel;
	BSONObj boRackSwitchInfo;
	BSONObj boPushSwitch;
	BSONObj boPullSwitch;

	string strRack, strSite, strSwitchSerial;	
	int iSwitchType;

	try
	{
		strRack			= CMongodbModel::GetStringFieldValue(boSwitchInfo, "rack", "");
		strSite			= CMongodbModel::GetStringFieldValue(boSwitchInfo, "site", "");
		iSwitchType		= CMongodbModel::GetIntFieldValue(boSwitchInfo, FIELD_RACK_SWITCH_TYPE, UNKNOWN);

		if (strRack != "" && strSite != "")
		{
			// Load switch info into RackSwitchModel
			objSwitchModel.SetCIType(iSwitchType);
			objSwitchModel.Load(boSwitchInfo);
			strSwitchSerial	= CMongodbModel::GetStringFieldValue(boSwitchInfo, "serial", "");
			
			objSwitchModel.Save(boRackSwitchInfo);	

			boPushSwitch = objRackModel.GetAddSwitchRecord(boRackSwitchInfo);
			boPullSwitch = objRackModel.GetDeleteSwitchRecord(strSwitchSerial);
			Query qCond = objRackModel.IsExistsRackQuery(strRack, strSite);
			
			//Pull old Switch serial in rack
			Update(boPullSwitch, qCond);
			//Push new Switch serial in rack
			Update(boPushSwitch, qCond);
			// Remove available U on the Rack
			RemoveAvailableU(strRack, strSite, objSwitchModel.GetU(), objSwitchModel.GetToU());	
		}
	}
	catch(exception& ex)
	{	
		stringstream strErrorMess;
		string strLog;
		strErrorMess << ex.what() << "][" << __FILE__ << "|" << __LINE__ ;
		strLog = CUtilities::FormatLog(ERROR_MSG, "CRackController", "AddRackSwitch","Exception:" + strErrorMess.str());
		CUtilities::WriteErrorLog(ERROR_MSG, strLog);
	}
}

void CRackController::RemoveRackSwitch(const BSONObj& boSwitchInfo)
{
	CRackSwitchModel objSwitchModel;
	CRackModel objRackModel;
	BSONObj boPullSwitch;
	string strRack, strSite, strSwitchSerial;	

	try
	{
		strRack			= boSwitchInfo.hasField("rack") ? boSwitchInfo.getStringField("rack") : "";
		strSite			= boSwitchInfo.hasField("site") ? boSwitchInfo.getStringField("site") : "";
		strSwitchSerial	= boSwitchInfo.hasField("serial") ? boSwitchInfo.getStringField("serial") : "";
		
		if (strRack != "" && strSite != "")
		{		
			objSwitchModel.Load(boSwitchInfo);		
			boPullSwitch = objRackModel.GetDeleteSwitchRecord(strSwitchSerial);
			Query qCond = objRackModel.IsExistsRackQuery(strRack, strSite);
			cout << "query:" << qCond.toString();
			cout << "pull:" << boPullSwitch.toString();
			//Pull old Switch serial in rack
			Update(boPullSwitch, qCond);
			// Add available U on Rack
			AddAvailableU(strRack, strSite, objSwitchModel.GetU(), objSwitchModel.GetToU());				
		}
	}
	catch(exception& ex)
	{	
		stringstream strErrorMess;
		string strLog;
		strErrorMess << ex.what() << "][" << __FILE__ << "|" << __LINE__ ;
		strLog = CUtilities::FormatLog(ERROR_MSG, "CRackController", "RemoveRackSwitch","Exception:" + strErrorMess.str());
		CUtilities::WriteErrorLog(ERROR_MSG, strLog);
	}
}


void CRackController::UpdateRackSwitch(const BSONObj& boOldCIInfo, const BSONObj& boNewCIInfo, const BSONObj& boChangedFields)
{
	CRackSwitchModel objSwitchModel;
	CRackModel objRackModel;
	BSONObj boRackSwitchInfo;
	BSONObj boPushSwitch;
	BSONObj boPullSwitch;

	Query qCond;

	string strOldRack, strOldSite, strNewRack, strNewSite;
	string strSwitchSerial;
	
	int nOldFromU, nOldToU, nOldUSpace;
	int iSwitchType;

	try
	{
		if (boChangedFields.hasField("rack") || boChangedFields.hasField("site") 
			|| boChangedFields.hasField("u") || boChangedFields.hasField("name") 
			|| boChangedFields.hasField("model"))
		{
			strOldRack		= CMongodbModel::GetStringFieldValue(boOldCIInfo, "rack", ""); 
			strOldSite		= CMongodbModel::GetStringFieldValue(boOldCIInfo, "site", ""); 
			strNewRack		= CMongodbModel::GetStringFieldValue(boNewCIInfo, "rack", ""); 
			strNewSite		= CMongodbModel::GetStringFieldValue(boNewCIInfo, "site", ""); 
			iSwitchType		= CMongodbModel::GetIntFieldValue(boNewCIInfo, FIELD_RACK_SWITCH_TYPE, UNKNOWN);
			cout << "switch type:" << iSwitchType << endl;

			objSwitchModel.SetCIType(iSwitchType);
			objSwitchModel.Load(boNewCIInfo);
			objSwitchModel.Save(boRackSwitchInfo);

			strSwitchSerial	= boNewCIInfo.hasField("serial") ? boNewCIInfo.getStringField("serial") : "";

			if (strOldRack != "" && strOldSite != "")
			{
				boPullSwitch = objRackModel.GetDeleteSwitchRecord(strSwitchSerial);
				qCond = objRackModel.IsExistsRackQuery(strOldRack, strOldSite);
				cout << "query:" << qCond.toString();
				cout << "pull:" << boPullSwitch.toString();
				//Pull old Switch serial in rack
				Update(boPullSwitch, qCond);
				// Add available U on the Rack		
				if(boOldCIInfo.hasField("u"))
				{
					nOldFromU = boOldCIInfo.getIntField("u");
					nOldUSpace = boOldCIInfo.hasField("u_space") ? boOldCIInfo.getIntField("u_space") : U_SPACE_DEFAULT;
					
					if (nOldUSpace < U_SPACE_DEFAULT)
						nOldUSpace = U_SPACE_DEFAULT;

					nOldToU = nOldFromU + nOldUSpace - 1;
					AddAvailableU(strOldRack, strOldSite, nOldFromU, nOldToU);		
				}
			}
			
			if (strNewRack != "" && strNewSite != "")
			{
				boPushSwitch = objRackModel.GetAddSwitchRecord(boRackSwitchInfo);
				qCond = objRackModel.IsExistsRackQuery(strNewRack, strNewSite);
				cout << "Query switch:" << qCond.toString() << endl;
				cout << "Push switch:" << boPushSwitch.toString() << endl;
				//Push new Switch serial in rack
				Update(boPushSwitch, qCond);
				// Remove available U on Rack
				RemoveAvailableU(strNewRack, strNewSite, objSwitchModel.GetU(), objSwitchModel.GetToU());		
			}
		}
	}
	catch(exception& ex)
	{	
		stringstream strErrorMess;
		string strLog;
		strErrorMess << ex.what() << "][" << __FILE__ << "|" << __LINE__ ;
		strLog = CUtilities::FormatLog(ERROR_MSG, "CRackController", "UpdateRackSwitch","Exception:" + strErrorMess.str());
		CUtilities::WriteErrorLog(ERROR_MSG, strLog);
	}
}

void CRackController::AddRackSwitchChassis(const BSONObj &boSwitchInfo, CMailboxController* ptrMailboxController)
{
	CRackSwitchChassisModel objSwitchChassisModel;
	CRackModel objRackModel;

	BSONObj boPushSwitchChassis;
	BSONObj boPullSwitchChassis;
	BSONObj boSwitchChassisInfo;

	string strRack, strSite, strIPChassis;
	//Atribute Switch Chassis
	string strSwitchSerial;
	int nBay;
	int iSwitchType;

	try
	{	strRack		 = CMongodbModel::GetStringFieldValue(boSwitchInfo, "rack", "");
		strSite		 = CMongodbModel::GetStringFieldValue(boSwitchInfo, "site", "");
		strIPChassis = CMongodbModel::GetStringFieldValue(boSwitchInfo, "ip_chassis", "");
		iSwitchType  = CMongodbModel::GetIntFieldValue(boSwitchInfo, FIELD_RACK_SWITCH_TYPE, UNKNOWN);
		cout << "switch type:" << iSwitchType << endl;

		//Found chassis in rack
		Query qRackChassisCond = objRackModel.IsExistsChassisQuery(strRack, strSite, strIPChassis);

		if(IsExisted(qRackChassisCond))
		{
			objSwitchChassisModel.SetCIType(iSwitchType);
			objSwitchChassisModel.Load(boSwitchInfo);
			objSwitchChassisModel.Save(boSwitchChassisInfo);
			strSwitchSerial = CMongodbModel::GetStringFieldValue(boSwitchInfo, "serial", "");
			
			//Pull Switch Chassis If Exists
			boPullSwitchChassis = objRackModel.GetDeleteSwitchChassisRecord(strSwitchSerial);
			Update(boPullSwitchChassis, qRackChassisCond);

			//Push New Switch Chassis
			boPushSwitchChassis = objRackModel.GetAddSwitchChassisRecord(boSwitchChassisInfo);
			Update(boPushSwitchChassis, qRackChassisCond);
		}
		else
		{
			//NOTIFY THROUGH EMAIL
			ptrMailboxController->NotifySwitchLocation(boSwitchInfo);
		}
	}
	catch(exception& ex)
	{	
		stringstream strErrorMess;
		string strLog;
		strErrorMess << ex.what() << "][" << __FILE__ << "|" << __LINE__ ;
		strLog = CUtilities::FormatLog(ERROR_MSG, "CRackController", "AddRackSwitchChassis","Exception:" + strErrorMess.str());
		CUtilities::WriteErrorLog(ERROR_MSG, strLog);
	}
}

void CRackController::RemoveRackSwitchChassis(const BSONObj &boSwitchInfo)
{
	CRackSwitchChassisModel objSwitchChassisModel;
	CRackModel objRackModel;

	BSONObj boPushSwitchChassis;
	BSONObj boPullSwitchChassis;
	BSONObj boSwitchChassisInfo;

	string strRack, strSite, strIPChassis;
	//Atribute Switch Chassis
	string strSwitchSerial;
	int nBay;

	try
	{	strRack		 = CMongodbModel::GetStringFieldValue(boSwitchInfo, "rack", "");
		strSite		 = CMongodbModel::GetStringFieldValue(boSwitchInfo, "site", "");
		strIPChassis = CMongodbModel::GetStringFieldValue(boSwitchInfo, "ip_chassis", "");
		
		//Found chassis in rack
		Query qRackChassisCond = objRackModel.IsExistsChassisQuery(strRack, strSite, strIPChassis);
		strSwitchSerial = CMongodbModel::GetStringFieldValue(boSwitchInfo, "serial", "");
		
		//Pull Switch Chassis If Exists
		boPullSwitchChassis = objRackModel.GetDeleteSwitchChassisRecord(strSwitchSerial);
		Update(boPullSwitchChassis, qRackChassisCond);		
	}
	catch(exception& ex)
	{	
		stringstream strErrorMess;
		string strLog;
		strErrorMess << ex.what() << "][" << __FILE__ << "|" << __LINE__ ;
		strLog = CUtilities::FormatLog(ERROR_MSG, "CRackController", "RemoveRackSwitchChassis","Exception:" + strErrorMess.str());
		CUtilities::WriteErrorLog(ERROR_MSG, strLog);
	}
}

void CRackController::UpdateRackSwitchChassis(const BSONObj &boOldCIInfo, 
											  const BSONObj &boNewCIInfo, 
											  const BSONObj &boChangedFields,
											  CMailboxController* ptrMailboxController)
{
	CRackSwitchChassisModel objSwitchChassisModel;
	CRackModel objRackModel;

	BSONObj boPushNewSwitchChassis;
	BSONObj boPullOldSwitchChassis;
	BSONObj boSwitchChassisInfo;

	Query qOldRackChassis;
	Query qNewRackChassis;

	string strOldRack, strOldSite, strOldIPChassis;
	string strNewRack, strNewSite, strNewIPChassis;

	string strSwitchSerial;
	int iSwitchType;

	try
	{
		strSwitchSerial	= CMongodbModel::GetStringFieldValue(boNewCIInfo, "serial", "");
		if (strSwitchSerial != "")
		{
			if (boChangedFields.hasField("rack")
				|| boChangedFields.hasField("site")
				|| boChangedFields.hasField("ip_chassis")
				|| boChangedFields.hasField("name"))

			{
				//Pull Old Bay Chassis out of Chassis
				strOldRack		= CMongodbModel::GetStringFieldValue(boOldCIInfo, "rack", "");
				strOldSite		= CMongodbModel::GetStringFieldValue(boOldCIInfo, "site", "");
				strOldIPChassis = CMongodbModel::GetStringFieldValue(boOldCIInfo, "ip_chassis", "");
				
				qOldRackChassis		= objRackModel.IsExistsChassisQuery(strOldRack, strOldSite, strOldIPChassis);
				boPullOldSwitchChassis = objRackModel.GetDeleteSwitchChassisRecord(strSwitchSerial);

				//Push New Bay Chassis into Chassis of Rack
				strNewRack		= CMongodbModel::GetStringFieldValue(boNewCIInfo, "rack", ""); 
				strNewSite		= CMongodbModel::GetStringFieldValue(boNewCIInfo, "site", "");
				strNewIPChassis = CMongodbModel::GetStringFieldValue(boNewCIInfo, "ip_chassis", ""); 
				iSwitchType		= CMongodbModel::GetIntFieldValue(boNewCIInfo, FIELD_RACK_SWITCH_TYPE, UNKNOWN);
				cout << "switch type:" << iSwitchType << endl;

				qNewRackChassis	= objRackModel.IsExistsChassisQuery(strNewRack, strNewSite, strNewIPChassis);
				cout << "Query:" << qNewRackChassis.toString() << endl;
				//If new Rack Chassis exists 
				//then will remove server in old rack chassis
				if (IsExisted(qNewRackChassis))
				{
					//Remove Old Switch in Chassis
					Update(boPullOldSwitchChassis, qOldRackChassis);
					
					objSwitchChassisModel.SetCIType(iSwitchType);
					objSwitchChassisModel.Load(boNewCIInfo);
					objSwitchChassisModel.Save(boSwitchChassisInfo);

					//Push New Switch Chassis
					boPushNewSwitchChassis = objRackModel.GetAddSwitchChassisRecord(boSwitchChassisInfo);
					Update(boPushNewSwitchChassis, qNewRackChassis);
				}
				else
				{
					//NOTIFY THROUGH EMAIL
					cout << "Notify email switch chassis" << endl;
					ptrMailboxController->NotifySwitchLocation(boNewCIInfo);
				}
			}
		}
	}
	catch(exception& ex)
	{
		stringstream strErrorMess;
		string strLog;
		strErrorMess << ex.what() << "][" << __FILE__ << "|" << __LINE__ ;
		strLog = CUtilities::FormatLog(ERROR_MSG, "CRackController", "UpdateRackSwitchChassis","Exception:" + strErrorMess.str());
		CUtilities::WriteErrorLog(ERROR_MSG, strLog);
	}
}

void CRackController::AddRackPDU(const mongo::BSONObj &boPDUInfo)
{
	CRackPDUModel objPDUModel;
	CRackModel objRackModel;
	BSONObj boRackPDUInfo;
	BSONObj boPushPDU;
	BSONObj boPullPDU;

	string strRack, strSite, strName, strPMM;
	Query qCond;

	try
	{	
		strRack		= CMongodbModel::GetStringFieldValue(boPDUInfo, "rack", "");
		strSite		= CMongodbModel::GetStringFieldValue(boPDUInfo, "site", "");
		strName		= CMongodbModel::GetStringFieldValue(boPDUInfo, "name", "");
		strPMM		= CMongodbModel::GetStringFieldValue(boPDUInfo, "pmm", "");

		if (strRack != "" && strSite != "")
		{
			// Load PDU info into CRackPDUModel
			objPDUModel.Load(boPDUInfo);
			cout << "To BSONObj" << endl;
			objPDUModel.Save(boRackPDUInfo);		
			cout << "TO okie" << endl;

			boPushPDU = objRackModel.GetAddPDURecord(boRackPDUInfo);
			boPullPDU = objRackModel.GetDeletePDURecord(strName, strPMM);

			qCond = objRackModel.IsExistsRackQuery(strRack, strSite);
			cout << "query:" << qCond.toString() << endl;
			cout << "pull:" << boPullPDU.toString() << endl;
			cout << "push:" << boPushPDU.toString() << endl;
			//Pull old Switch serial in rack
			Update(boPullPDU, qCond);
			//Push new Switch serial in rack
			Update(boPushPDU, qCond);
		}
	}
	catch(exception& ex)
	{	
		stringstream strErrorMess;
		string strLog;
		strErrorMess << ex.what() << "][" << __FILE__ << "|" << __LINE__ ;
		strLog = CUtilities::FormatLog(ERROR_MSG, "CRackController", "AddRackPDU","Exception:" + strErrorMess.str());
		CUtilities::WriteErrorLog(ERROR_MSG, strLog);
	}
}

void CRackController::RemoveRackPDU(const mongo::BSONObj &boPDUInfo)
{
	CRackPDUModel objPDUModel;
	CRackModel objRackModel;
	BSONObj boRackPDUInfo;
	BSONObj boPullPDU;

	string strRack, strSite, strName, strPMM;
	Query qCond;
	try
	{	
		strRack		= CMongodbModel::GetStringFieldValue(boPDUInfo, "rack", "");
		strSite		= CMongodbModel::GetStringFieldValue(boPDUInfo, "site", "");
		strName		= CMongodbModel::GetStringFieldValue(boPDUInfo, "name", "");
		strPMM		= CMongodbModel::GetStringFieldValue(boPDUInfo, "pmm", "");


		//Found rack
		qCond		= objRackModel.IsExistsRackQuery(strRack, strSite);
		
		//Pull PDU If Exists
		boPullPDU = objRackModel.GetDeletePDURecord(strName, strPMM);
		Update(boPullPDU, qCond);
	}
	catch(exception& ex)
	{	
		stringstream strErrorMess;
		string strLog;
		strErrorMess << ex.what() << "][" << __FILE__ << "|" << __LINE__ ;
		strLog = CUtilities::FormatLog(ERROR_MSG, "CRackController", "RemoveRackPDU","Exception:" + strErrorMess.str());
		CUtilities::WriteErrorLog(ERROR_MSG, strLog);
	}
}

void CRackController::UpdateRackPDU(const mongo::BSONObj &boOldCIInfo, const mongo::BSONObj &boNewCIInfo, const mongo::BSONObj &boChangedFields)
{
	CRackPDUModel objPDUModel;
	CRackModel objRackModel;
	BSONObj boRackPDUInfo;
	BSONObj boPushPDU;
	BSONObj boPullPDU;

	string strOldRack, strOldSite, strNewRack, strNewSite;
	string strOldName, strOldPMM;

	Query qCond;

	try
	{	
		if (boChangedFields.hasField("rack") || boChangedFields.hasField("site")
			|| boChangedFields.hasField("current")
			|| boChangedFields.hasField("pmm")
			|| boChangedFields.hasField("unit")
			|| boChangedFields.hasField("name"))
		{
			strOldRack	= CMongodbModel::GetStringFieldValue(boOldCIInfo, "rack", "");
			strOldSite	= CMongodbModel::GetStringFieldValue(boOldCIInfo, "site", "");
			strOldName	= CMongodbModel::GetStringFieldValue(boOldCIInfo, "name", "");
			strOldPMM	= CMongodbModel::GetStringFieldValue(boOldCIInfo, "pmm", "");

			strNewRack	= CMongodbModel::GetStringFieldValue(boNewCIInfo, "rack", "");
			strNewSite	= CMongodbModel::GetStringFieldValue(boNewCIInfo, "site", "");
			
			// Load PDU info into CRackPDUModel
			objPDUModel.Load(boNewCIInfo);
			objPDUModel.Save(boRackPDUInfo);

			if (strOldRack != "" && strOldSite != "")
			{
				
				boPullPDU = objRackModel.GetDeletePDURecord(strOldName, strOldPMM);
				qCond = objRackModel.IsExistsRackQuery(strOldRack, strOldSite);
				
				cout << "query:" << qCond.toString() << endl;
				cout << "pull:" << boPullPDU.toString() << endl;
				//Pull old Switch serial in rack
				Update(boPullPDU, qCond);
			}

			if (strNewRack != "" && strNewRack != "")
			{
				boPushPDU = objRackModel.GetAddPDURecord(boRackPDUInfo);
				qCond = objRackModel.IsExistsRackQuery(strNewRack, strNewSite);
				
				cout << "query:" << qCond.toString() << endl;
				cout << "push:" << boPushPDU.toString() << endl;
				Update(boPushPDU, qCond);
			}
		}
	}
	catch(exception& ex)
	{	
		stringstream strErrorMess;
		string strLog;
		strErrorMess << ex.what() << "][" << __FILE__ << "|" << __LINE__ ;
		strLog = CUtilities::FormatLog(ERROR_MSG, "CRackController", "UpdateRackPDU","Exception:" + strErrorMess.str());
		CUtilities::WriteErrorLog(ERROR_MSG, strLog);
	}
}