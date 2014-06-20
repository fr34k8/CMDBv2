#include "RackBayChassisModel.h"
#include "ServerModel.h"

#define INDEX_BAY_ID		1
#define INDEX_SERVER_SERIAL 2
#define INDEX_SERVER_NAME	3
#define INDEX_PRODUCT_ALIAS 4
#define INDEX_PRODUCT_CODE	5

#define FIELD_BAY_ID		"bay_id"
#define FIELD_SERVER_SERIAL "server_serial"
#define FIELD_SERVER_NAME	"server_name"
#define FIELD_PRODUCT_ALIAS "product_alias"
#define FIELD_PRODUCT_CODE	"product_code"

CRackBayChassisModel::CRackBayChassisModel(void)
{	
	m_mapFieldIndex[FIELD_BAY_ID]		 = INDEX_BAY_ID;
	m_mapFieldIndex[FIELD_SERVER_SERIAL] = INDEX_SERVER_SERIAL;
	m_mapFieldIndex[FIELD_SERVER_NAME]   = INDEX_SERVER_NAME;
	m_mapFieldIndex[FIELD_PRODUCT_ALIAS] = INDEX_PRODUCT_ALIAS;
	m_mapFieldIndex[FIELD_PRODUCT_CODE]  = INDEX_PRODUCT_CODE;
	
	m_mapFieldType[FIELD_BAY_ID]		 = BSON_INT_TYPE;
	m_mapFieldType[FIELD_SERVER_SERIAL]	 = BSON_STRING_TYPE;
	m_mapFieldType[FIELD_SERVER_NAME]	 = BSON_STRING_TYPE;
	m_mapFieldType[FIELD_PRODUCT_ALIAS]	 = BSON_STRING_TYPE;
	m_mapFieldType[FIELD_PRODUCT_CODE]	 = BSON_STRING_TYPE;
}
CRackBayChassisModel::~CRackBayChassisModel(void)
{
}

CRackBayChassisModel::operator int()
{
	int iValue;

	switch (m_iFieldIndex)
	{	
	case INDEX_BAY_ID:
		iValue = m_nBayId;
		break;
	}

	return iValue;
}

CRackBayChassisModel::operator std::string()
{
	string strValue;

	switch (m_iFieldIndex)
	{
	case INDEX_SERVER_SERIAL:
		strValue = m_strServerSerial;
		break;
	case INDEX_SERVER_NAME:
		strValue = m_strServerName;
		break;
	case INDEX_PRODUCT_ALIAS:
		strValue = m_strProductAlias;
		break;
	case INDEX_PRODUCT_CODE:
		strValue = m_strProductCode;
		break;
	}

	return strValue;
}
CMongodbModel& CRackBayChassisModel::operator=(int iValue)
{
	switch (m_iFieldIndex)
	{	
	case INDEX_BAY_ID:
		m_nBayId = iValue;
		break;
	}

	CMongodbModel::operator=(iValue);
}
CMongodbModel& CRackBayChassisModel::operator=(string strValue)
{
	switch (m_iFieldIndex)
	{
	case INDEX_SERVER_SERIAL:
		m_strServerSerial = strValue;
		break;
	case INDEX_SERVER_NAME:
		m_strServerName = strValue;
		break;
	case INDEX_PRODUCT_ALIAS:
		m_strProductAlias = strValue;
		break;
	case INDEX_PRODUCT_CODE:
		m_strProductCode = strValue;
		break;
	}

	CMongodbModel::operator=(strValue);
}

void CRackBayChassisModel::Load(const BSONObj& boRecord)
{
	(*this)[FIELD_SERVER_SERIAL]	= boRecord.hasField("code") ? boRecord.getStringField("code") : "";		
	(*this)[FIELD_SERVER_NAME]		= boRecord.hasField("server_name") ? boRecord.getStringField("server_name") : "";
	(*this)[FIELD_PRODUCT_ALIAS]	= boRecord.hasField("product_alias") ? boRecord.getStringField("product_alias") : "";
	(*this)[FIELD_PRODUCT_CODE]		= boRecord.hasField("product_code") ? boRecord.getStringField("product_code") : "";
	(*this)[FIELD_BAY_ID] = boRecord.hasField("bay") ? boRecord.getIntField("bay") : 0;
	CDeviceModel::Load(boRecord);
}


void CRackBayChassisModel::BuildBSONObj(BSONObjBuilder& boBuilder, int iFormat)
{
	switch (iFormat)
	{
	case SAVE_RACK_MAP:
		boBuilder.append(FIELD_SERVER_SERIAL, m_strServerSerial);
		boBuilder.append(FIELD_SERVER_NAME, m_strServerName);
		boBuilder.append(FIELD_PRODUCT_ALIAS, m_strProductAlias);		
		boBuilder.append(FIELD_PRODUCT_CODE, m_strProductCode);
		boBuilder.append(FIELD_BAY_ID, m_nBayId);
		break;
	}
}
