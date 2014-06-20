#include "RackServerUModel.h"
#include "ServerModel.h"

#define INDEX_FROM_U		0
#define INDEX_TO_U			1
#define INDEX_SERVER_SERIAL 2
#define INDEX_SERVER_NAME	3
#define INDEX_PRODUCT_ALIAS 4
#define INDEX_PRODUCT_CODE	5

#define FIELD_FROM_U		"from_u"
#define FIELD_TO_U			"to_u"
#define FIELD_SERVER_SERIAL "server_serial"
#define FIELD_SERVER_NAME	"server_name"
#define FIELD_PRODUCT_ALIAS "product_alias"
#define FIELD_PRODUCT_CODE	"product_code"

CRackServerUModel::CRackServerUModel(void)
{
	m_mapFieldIndex[FIELD_FROM_U]		 = INDEX_FROM_U;
	m_mapFieldIndex[FIELD_TO_U]			 = INDEX_TO_U;
	m_mapFieldIndex[FIELD_SERVER_SERIAL] = INDEX_SERVER_SERIAL;
	m_mapFieldIndex[FIELD_SERVER_NAME]   = INDEX_SERVER_NAME;
	m_mapFieldIndex[FIELD_PRODUCT_ALIAS] = INDEX_PRODUCT_ALIAS;
	m_mapFieldIndex[FIELD_PRODUCT_CODE]  = INDEX_PRODUCT_CODE;

	m_mapFieldType[FIELD_FROM_U]		 = BSON_INT_TYPE;
	m_mapFieldType[FIELD_TO_U]			 = BSON_INT_TYPE;
	m_mapFieldType[FIELD_SERVER_SERIAL] = BSON_STRING_TYPE;
	m_mapFieldType[FIELD_SERVER_NAME]	 = BSON_STRING_TYPE;
	m_mapFieldType[FIELD_PRODUCT_ALIAS]	 = BSON_STRING_TYPE;
	m_mapFieldType[FIELD_PRODUCT_CODE]	 = BSON_STRING_TYPE;
}
CRackServerUModel::~CRackServerUModel(void)
{
}

void CRackServerUModel::Load(const BSONObj& boRecord)
{
	(*this)[FIELD_SERVER_SERIAL] = boRecord.hasField("code") ? boRecord.getStringField("code") : "";
	(*this)[FIELD_SERVER_NAME]		= boRecord.hasField("server_name") ? boRecord.getStringField("server_name") : "";
	(*this)[FIELD_PRODUCT_ALIAS]	= boRecord.hasField("product_alias") ? boRecord.getStringField("product_alias") : "";
	(*this)[FIELD_PRODUCT_CODE]		= boRecord.hasField("product_code") ? boRecord.getStringField("product_code") : "";	

	/*(*this)[FIELD_FROM_U]			= boRecord.hasField("u") ? boRecord.getIntField("u") : 0;
	m_iSpace = boRecord.hasField("u_space") ? boRecord.getIntField("u_space") : 0;	
	(*this)[FIELD_TO_U]				= m_iU + m_iSpace - 1;*/
	CDeviceModel::Load(boRecord);
}

void CRackServerUModel::BuildBSONObj(BSONObjBuilder& boBuilder, int iFormat)
{
	switch (iFormat)
	{
	case SAVE_RACK_MAP:
		boBuilder.append(FIELD_SERVER_SERIAL, m_strServerSerial);
		boBuilder.append(FIELD_SERVER_NAME, m_strServerName);
		boBuilder.append(FIELD_PRODUCT_ALIAS, m_strProductAlias);		
		boBuilder.append(FIELD_PRODUCT_CODE, m_strProductCode);
		break;
	}

	CDeviceModel::BuildBSONObj(boBuilder, iFormat);
}

CRackServerUModel::operator int()
{
	int iValue;

	switch (m_iFieldIndex)
	{
	case INDEX_FROM_U:
		iValue = m_iU;
		break;
	case INDEX_TO_U:
		iValue = m_nToU;
		break;
	}

	return iValue;
}

CRackServerUModel::operator std::string()
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
CMongodbModel& CRackServerUModel::operator=(int iValue)
{
	switch (m_iFieldIndex)
	{
	case INDEX_FROM_U:
		m_iU = iValue;
		break;
	case INDEX_TO_U:
		m_nToU = iValue;
		break;
	}

	CMongodbModel::operator=(iValue);
}
CMongodbModel& CRackServerUModel::operator=(string strValue)
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