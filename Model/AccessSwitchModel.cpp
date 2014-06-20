#include "AccessSwitchModel.h"
#include "../Common/DBCommon.h"

#define INDEX_VLAN_INFO		0

CAccessSwitchModel::CAccessSwitchModel(void)
{
	m_iCIType = CI_TYPE_ACCESS_SWITCH;
	m_mapFieldIndex[FIELD_VLAN_INFO] = INDEX_VLAN_INFO;
	m_mapFieldType[FIELD_VLAN_INFO] = BSON_ARRAY_TYPE;
}

CAccessSwitchModel::~CAccessSwitchModel(void)
{
}

CAccessSwitchModel::operator BSONArray()
{
	BSONArray boArray;
	switch (m_iFieldIndex)
	{
	case INDEX_VLAN_INFO:
		boArray = m_barrVlanInfo;		
		break;
	}

	return boArray;
}

CMongodbModel& CAccessSwitchModel::operator=(BSONArray boValue)
{
	switch (m_iFieldIndex)
	{
	case INDEX_VLAN_INFO:
		m_barrVlanInfo = boValue;
		break;
	}

	CMongodbModel::operator=(boValue);
}

void CAccessSwitchModel::VlanRange2VlanInfo(int nStartVlan, int nEndVlan, 
											BSONArrayBuilder& arrBuilderVlanInfo)
{
	for (int iVlan = nStartVlan; iVlan <= nEndVlan; iVlan++)
	{
		arrBuilderVlanInfo << iVlan;		
	}
}

void CAccessSwitchModel::AllowVlan2VlanInfo(string strAllowVlan)
{
	BSONArrayBuilder arrBuilderVlanInfo;
	string strToken = "";	
	int iIndex = 0;
	bool bRange = false;
	int nStartVlan;
	int nEndVlan;
	while (iIndex < strAllowVlan.length())
	{
		switch (strAllowVlan[iIndex])
		{
		case ' ':
			break;
		case ',':
			if (bRange)
			{
				nEndVlan = atoi(strToken.c_str());
				bRange = false;
				VlanRange2VlanInfo(nStartVlan, nEndVlan, arrBuilderVlanInfo);				
			}
			else
			{
				if (strToken != "")
				{
					arrBuilderVlanInfo << atoi(strToken.c_str());
				}
			}		
			strToken = "";
			break;
		case '-':
			nStartVlan = atoi(strToken.c_str());
			bRange = true;
			strToken = "";
			break;
		default:
			if ((strAllowVlan[iIndex] >= '0') && (strAllowVlan[iIndex] <= '9'))
			{
				strToken += strAllowVlan[iIndex];
			}
		}

		iIndex++;
	}

	if (bRange)
	{
		nEndVlan = atoi(strToken.c_str());
		VlanRange2VlanInfo(nStartVlan, nEndVlan, arrBuilderVlanInfo);		
	}
	else
	{
		if (strToken != "")
		{
			arrBuilderVlanInfo << atoi(strToken.c_str());
		}
	}

	// Assign vlan info
	m_barrVlanInfo = arrBuilderVlanInfo.arr();
	m_mapFieldSet[FIELD_VLAN_INFO] = true;	
}