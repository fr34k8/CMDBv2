#include "CMDBController.h"
#include "../Common/DBCommon.h"

CCMDBController::CCMDBController(void)
{
}

CCMDBController::~CCMDBController(void)
{
}

auto_ptr<DBClientCursor> CCMDBController::LoadData()
{
}

bool CCMDBController::FindSendMailConfig(BSONObj &boConfigRecord, BSONObj boNewCIInfo, string strApp)
{
	string strField, strValue, strCIValue;
	auto_ptr<DBClientCursor> ptrConfigCursor = auto_ptr<DBClientCursor>();
	bool bResult = Find(TBL_MAIL_CONFIG, ptrConfigCursor,
		QUERY(
		"ci" << m_strTableName << "type" << strApp
		));

	if (bResult)
	{
		bResult = false;
		while (ptrConfigCursor->more())
		{
			boConfigRecord = ptrConfigCursor->nextSafe();
			strField = boConfigRecord.hasField("field") ? boConfigRecord.getStringField("field") : "";
			strValue = boConfigRecord.hasField("value") ? boConfigRecord.getStringField("value") : "";
			if (strField.empty() && strValue.empty())
			{
				return true;
			}
			if (boNewCIInfo.hasField(strField))
			{
				strCIValue = boNewCIInfo.getStringField(strField.c_str());
				if (strCIValue.compare(strValue) == 0)
				{
					bResult = true;
				}
			}
		}
	}
	return bResult;
}

bool CCMDBController::FindServerU(auto_ptr<DBClientCursor>& ptrCursor)
{
	bool bResult = Find(TBL_SERVER, ptrCursor,
		QUERY(
		"status" << BSON("$in" << BSON_ARRAY(SERVER_IN_USED << SERVER_BORROW << SERVER_TRANSFER)) <<
		"server_type" << SERVER_U << "deleted" << 0
		));
	return bResult;
}

bool CCMDBController::FindOperatingPhysicalServer(auto_ptr<DBClientCursor>& ptrCursor)
{
	bool bResult = Find(TBL_SERVER, ptrCursor, 
		QUERY(
		"status" << BSON("$in" << BSON_ARRAY(SERVER_IN_USED << SERVER_BORROW << SERVER_TRANSFER)) <<
		"server_type" << BSON("$in" << BSON_ARRAY(SERVER_U << SERVER_CHASSIS)) << "deleted" << 0
		));
	return bResult;
}

bool CCMDBController::FindOperatingVirtualServer(auto_ptr<DBClientCursor>& ptrCursor)
{
	bool bResult = Find(TBL_SERVER, ptrCursor, 
		QUERY(
		"status" << BSON("$in" << BSON_ARRAY(SERVER_IN_USED << SERVER_BORROW << SERVER_TRANSFER)) <<
		"server_type" << SERVER_VIRTUAL << "deleted" << 0
		));
	return bResult;
}

bool CCMDBController::FindOperatingAllServer(auto_ptr<DBClientCursor>& ptrCursor)
{
	bool bResult = Find(TBL_SERVER, ptrCursor, 
		QUERY("deleted" << 0)
		);
	return bResult;
}

bool CCMDBController::FindOperatingChassis(auto_ptr<DBClientCursor>& ptrCursor)
{
	bool bResult = Find(TBL_CHASSIS, ptrCursor, QUERY("deleted" << 0));
	return bResult;
}

bool CCMDBController::FindOperatingAccessSwitch(auto_ptr<DBClientCursor>& ptrCursor)
{
	bool bResult = Find(TBL_ACCESS_SWITCH, ptrCursor, QUERY("deleted" << 0));
	return bResult;
}

bool CCMDBController::FindOperatingAggregationSwitch(auto_ptr<DBClientCursor>& ptrCursor)
{
	bool bResult = Find(TBL_AGGREGATION_SWITCH, ptrCursor, QUERY("deleted" << 0));
	return bResult;
}

bool CCMDBController::FindOperatingCoreSwitch(auto_ptr<DBClientCursor>& ptrCursor)
{
	bool bResult = Find(TBL_CORE_SWITCH, ptrCursor, QUERY("deleted" << 0));
	return bResult;
}

bool CCMDBController::FindOperatingPDU(auto_ptr<DBClientCursor>& ptrCursor)
{
	bool bResult = Find(TBL_PDU, ptrCursor, QUERY("deleted" << 0));
	return bResult;
}

bool CCMDBController::FindOperatingRack(auto_ptr<DBClientCursor>& ptrCursor)
{
	bool bResult = Find(TBL_RACK, ptrCursor);
	return bResult;
}