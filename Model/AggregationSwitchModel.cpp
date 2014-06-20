#include "AggregationSwitchModel.h"

#define INDEX_RACK_INFO 0
CAggregationSwitchModel::CAggregationSwitchModel(void)
{
	m_iCIType = CI_TYPE_AGGREGATION_SWITCH;
	m_mapFieldIndex[FIELD_RACK_INFO] = INDEX_RACK_INFO;
	m_mapFieldType[FIELD_RACK_INFO] = BSON_ARRAY_TYPE;
}

CAggregationSwitchModel::~CAggregationSwitchModel(void)
{
}

CAggregationSwitchModel::operator BSONArray()
{
	BSONArray boArray;
	switch (m_iFieldIndex)
	{
	case INDEX_RACK_INFO:
		boArray = m_barrRackInfo;		
		break;
	}

	return boArray;
}

CMongodbModel& CAggregationSwitchModel::operator=(BSONArray boValue)
{
	switch (m_iFieldIndex)
	{
	case INDEX_RACK_INFO:
		m_barrRackInfo = boValue;
		break;
	}

	CMongodbModel::operator=(boValue);
}

void CAggregationSwitchModel::AccessRack2RackInfo(string strAccessRack)
{
	BSONArrayBuilder arrBuilderRackInfo;
	string strToken = "";	
	int iIndex = 0;

	while (iIndex < strAccessRack.length())
	{
		switch (strAccessRack[iIndex])
		{
		case ',':
		case ';':
			arrBuilderRackInfo << strToken;			
			strToken = "";
			break;		
		default:
			strToken += strAccessRack[iIndex];
		}

		iIndex++;
	}

	if (strToken != "")
	{
		arrBuilderRackInfo << strToken;
	}

	// Assign rack info
	m_barrRackInfo = arrBuilderRackInfo.arr();
	m_mapFieldSet[FIELD_RACK_INFO] = true;	
}