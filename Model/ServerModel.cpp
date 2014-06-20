#include "ServerModel.h"

#define INDEX_U				0
#define INDEX_CODE			1
#define INDEX_SITE			2
#define INDEX_RACK			3
#define INDEX_IP_CHASSIS	4
#define INDEX_BAY			5
#define INDEX_STATUS		6

#define CMDB_UPDATE_SERVER_URL "https://cmdbv2.vng.com.vn/server/index/update?cid="

CServerModel::CServerModel(void)
{
	m_mapFieldIndex[FIELD_U] = INDEX_U;
	m_mapFieldType[FIELD_U] = BSON_INT_TYPE;

	m_mapFieldIndex[FIELD_CODE] = INDEX_CODE;
	m_mapFieldType[FIELD_CODE] = BSON_STRING_TYPE;

	m_mapFieldIndex[FIELD_SITE] = INDEX_SITE;
	m_mapFieldType[FIELD_SITE] = BSON_STRING_TYPE;

	m_mapFieldIndex[FIELD_RACK] = INDEX_RACK;
	m_mapFieldType[FIELD_RACK] = BSON_STRING_TYPE;

	m_mapFieldIndex[FIELD_IP_CHASSIS] = INDEX_IP_CHASSIS;
	m_mapFieldType[FIELD_IP_CHASSIS] = BSON_STRING_TYPE;

	m_mapFieldIndex[FIELD_BAY] = INDEX_BAY;
	m_mapFieldType[FIELD_BAY] = BSON_INT_TYPE;

	m_mapFieldIndex[FIELD_STATUS] = INDEX_STATUS;
	m_mapFieldType[FIELD_STATUS] = BSON_INT_TYPE;
}

CServerModel::~CServerModel(void)
{
}

BSONObj CServerModel::GetModelMappingRecord(BSONObj boRecord)
{
	BSONObj boMappingRecord;
	if (boRecord.hasField("server_model") && boRecord.hasField("server_type"))
	{
		boMappingRecord = BSON(
			"model" << boRecord["server_model"]
			<< "type" << m_iCIType
			<< "u_space" << 0
			);
	}
	return boMappingRecord;
}

BSONObj CServerModel::GetModelMappingCondition(BSONObj boRecord)
{
	BSONObj boMappingCondition;
	if (boRecord.hasField("server_model"))
	{
		boMappingCondition = BSON(
			"model" << boRecord["server_model"]
			);
	}
	return boMappingCondition;
}

CServerModel::operator int()
{
	int iValue;
	switch (m_iFieldIndex)
	{
	case INDEX_U:
		iValue = m_iU;		
		break;
	case INDEX_BAY:
		iValue = m_iBay;		
		break;
	case INDEX_STATUS:
		iValue = m_iStatus;		
		break;
	}

	return iValue;
}

CServerModel::operator string()
{
	string strValue;
	switch (m_iFieldIndex)
	{
	case INDEX_CODE:
		strValue = m_strCode;		
		break;
	case INDEX_SITE:
		strValue = m_strSite;		
		break;
	case INDEX_RACK:
		strValue = m_strRack;		
		break;
	case INDEX_IP_CHASSIS:
		strValue = m_strIPChassis;		
		break;
	}

	return strValue;
}

CMongodbModel& CServerModel::operator=(int iValue)
{
	switch (m_iFieldIndex)
	{
	case INDEX_U:
		m_iU = iValue;
		break;
	case INDEX_BAY:
		m_iBay = iValue;
		break;
	case INDEX_STATUS:
		m_iStatus = iValue;
		break;
	}

	CMongodbModel::operator =(iValue);
}

CMongodbModel& CServerModel::operator=(string strValue)
{
	switch (m_iFieldIndex)
	{
	case INDEX_CODE:
		m_strCode = strValue;
		break;
	case INDEX_SITE:
		m_strSite = strValue;
		break;
	case INDEX_RACK:
		m_strRack = strValue;		
		break;
	case INDEX_IP_CHASSIS:
		m_strIPChassis = strValue;
		break;
	}

	CMongodbModel::operator =(strValue);
}

bool CServerModel::IsEqualLocation(CServerModel* pServerModel)
{	
	string strSite = (*pServerModel)[FIELD_SITE];	
	string strChassis = (*pServerModel)[FIELD_IP_CHASSIS];
	int iU = (*pServerModel)[FIELD_U];
	int iBay = (*pServerModel)[FIELD_BAY];	

	return ((strSite == m_strSite) && 
		(strChassis == m_strIPChassis) && 
		(iU == m_iU) && 
		(iBay == m_iBay));
}

void CServerModel::Print()
{
	cout << "code:" << m_strCode << "site:" << m_strSite << "rack:"  << 
		m_strRack << "chassis:" << m_strIPChassis << "u:" << m_iU << 
		"bay:" << m_iBay << "status:" << m_iStatus << endl;
}

string CServerModel::GetCode(BSONObj boCIInfo)
{
	string strCode = boCIInfo.hasField("code") ? boCIInfo.getStringField("code") : "";

	return strCode;
}

string CServerModel::GetServerName(BSONObj boCIInfo)
{
	string strServerName = boCIInfo.hasField("server_name") ? boCIInfo.getStringField("server_name") : "";

	return strServerName;
}

string CServerModel::GetProductAlias(BSONObj boCIInfo)
{
	string strProductAlias = boCIInfo.hasField("product_alias") ? boCIInfo.getStringField("product_alias") : "";

	return strProductAlias;
}

string CServerModel::GetProductCode(BSONObj boCIInfo)
{
	string strProductCode = boCIInfo.hasField("product_code") ? boCIInfo.getStringField("product_code") : "";

	return strProductCode;
}

int CServerModel::GetBay(BSONObj boCIInfo)
{
	int nBay = boCIInfo.hasField("bay") ? boCIInfo.getIntField("bay") : 0;

	return nBay;
}

void CServerModel::CreateLocationMailInfo(const BSONObj& boServerInfo, 
										  BSONObj& boMailInfo)
{
	string strSerial, strSite, strRack, strChassis, strId, strLink;
	int iBay, iU;
	strSerial	= boServerInfo.hasField("code") ? boServerInfo.getStringField("code") : "";
	strSite		= boServerInfo.hasField("site") ? boServerInfo.getStringField("site") : "";
	strRack		= boServerInfo.hasField("rack") ? boServerInfo.getStringField("rack") : "";
	strChassis	= boServerInfo.hasField("chassis") ? boServerInfo.getStringField("chassis") : "";
	iU			= boServerInfo.hasField("u") ? boServerInfo.getIntField("u") : 0;
	iBay		= boServerInfo.hasField("bay") ? boServerInfo.getIntField("bay") : 0;
	strId		= boServerInfo.hasField("_id") ? CUtilities::GetMongoObjId(boServerInfo.getField("ci_id").toString(false)) : "";
	strLink		= CMDB_UPDATE_SERVER_URL + strId;

	boMailInfo = BSON(
			"serial"	<< strSerial <<
			"site"		<< strSite <<
			"rack"		<< strRack <<
			"chassis"	<< strChassis <<
			"u"			<< iU <<
			"bay"		<< iBay <<
			"link"		<< strLink
			);
}

void CServerModel::CreateNetworkMailInfo(const BSONObj& boServerInfo, 
										 BSONObj& boMailInfo)
{
}