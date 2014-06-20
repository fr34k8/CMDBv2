#include "RackSwitchModel.h"

#define FIELD_FROM_U		"from_u"
#define FIELD_TO_U			"to_u"
#define FIELD_SWITCH_NAME	"switch_name"
#define FIELD_SWITCH_SERIAL "switch_serial"
#define FIELD_SWITCH_MODEL	"model"
#define FIELD_SWITCH_TYPE	"switch_type"

#define INDEX_FROM_U		0
#define INDEX_TO_U			1
#define INDEX_SWITCH_NAME	2
#define INDEX_SWITCH_SERIAL	3
#define INDEX_SWITCH_MODEL	4

CRackSwitchModel::CRackSwitchModel(void)
{
	m_mapFieldIndex[FIELD_FROM_U]		 = INDEX_FROM_U;
	m_mapFieldIndex[FIELD_TO_U]			 = INDEX_TO_U;
	m_mapFieldIndex[FIELD_SWITCH_NAME]	 = INDEX_SWITCH_NAME;
	m_mapFieldIndex[FIELD_SWITCH_SERIAL] = INDEX_SWITCH_SERIAL;
	m_mapFieldIndex[FIELD_SWITCH_MODEL]  = INDEX_SWITCH_MODEL;

	m_mapFieldType[FIELD_FROM_U]		 = BSON_INT_TYPE;
	m_mapFieldType[FIELD_TO_U]			 = BSON_INT_TYPE;
	m_mapFieldType[FIELD_SWITCH_NAME]	 = BSON_STRING_TYPE;
	m_mapFieldType[FIELD_SWITCH_SERIAL]	 = BSON_STRING_TYPE;
	m_mapFieldType[FIELD_SWITCH_MODEL]	 = BSON_STRING_TYPE;
	
	m_strSwitchName		= "";
	m_strSwitchSerial	= "";
	m_strSwitchModel	= "";
}

CRackSwitchModel::~CRackSwitchModel(void)
{
}

CRackSwitchModel::operator int()
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

CRackSwitchModel::operator std::string()
{
	string strValue;

	switch (m_iFieldIndex)
	{
	case INDEX_SWITCH_NAME:
		strValue = m_strSwitchName;
		break;
	case INDEX_SWITCH_SERIAL:
		strValue = m_strSwitchSerial;
		break;
	case INDEX_SWITCH_MODEL:
		strValue = m_strSwitchModel;
		break;
	}

	return strValue;
}
CMongodbModel& CRackSwitchModel::operator=(int iValue)
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
CMongodbModel& CRackSwitchModel::operator=(string strValue)
{
	switch (m_iFieldIndex)
	{
	case INDEX_SWITCH_NAME:
		m_strSwitchName = strValue;
		break;
	case INDEX_SWITCH_SERIAL:
		m_strSwitchSerial = strValue;
		break;
	case INDEX_SWITCH_MODEL:
		m_strSwitchModel = strValue;
		break;
	}

	CMongodbModel::operator=(strValue);
}

void CRackSwitchModel::Load(const BSONObj& boSwitchInfo)
{	
	m_strSwitchName		= boSwitchInfo.hasField("name") ? boSwitchInfo.getStringField("name") : "";
	m_strSwitchSerial	= boSwitchInfo.hasField("serial") ? boSwitchInfo.getStringField("serial") : "";
	m_strSwitchModel	= boSwitchInfo.hasField("model") ? boSwitchInfo.getStringField("model") : "";
	
	if (boSwitchInfo.hasField("vlan_info"))
	{
		m_boSwitchInfo = boSwitchInfo.copy();
	}
	CDeviceModel::Load(boSwitchInfo);
}

void CRackSwitchModel::BuildBSONObj(BSONObjBuilder& boBuilder, int iFormat)
{
	boBuilder.append(FIELD_SWITCH_NAME, m_strSwitchName);
	boBuilder.append(FIELD_SWITCH_SERIAL, m_strSwitchSerial);
	boBuilder.append(FIELD_SWITCH_MODEL, m_strSwitchModel);
	boBuilder.append(FIELD_SWITCH_TYPE, m_iCIType);

	CDeviceModel::BuildBSONObj(boBuilder, iFormat);
}

void CRackSwitchModel::BuildArrayVlan(map<int, bool> &mapArrayVlan, BSONArrayBuilder &babArrayVlan)
{
	int iVlan;
	BSONObj boTemp;
	vector<BSONElement> vbeVlanArray;
	vector<BSONElement>::iterator vit;
	if (m_boSwitchInfo.isEmpty())
	{
		return;
	}
	vbeVlanArray = m_boSwitchInfo["vlan_info"].Array();
	vit = vbeVlanArray.begin();
	while (vit != vbeVlanArray.end())
	{
		iVlan = (*vit)._numberInt();
		if (mapArrayVlan.find(iVlan) == mapArrayVlan.end())
		{
			mapArrayVlan[iVlan] = true;
			babArrayVlan << iVlan;
		}
		vit++;
	}
	//cout << boTemp.toString() << endl;
}