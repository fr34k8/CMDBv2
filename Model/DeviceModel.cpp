#include "DeviceModel.h"

#define FIELD_FROM_U		"from_u"
#define FIELD_TO_U			"to_u"

CDeviceModel::CDeviceModel(void)
{
}

CDeviceModel::~CDeviceModel(void)
{
}


BSONObj CDeviceModel::GetModelMappingRecord(BSONObj boRecord)
{
	BSONObj boMappingRecord;
	if (boRecord.hasField("model"))
	{
		boMappingRecord = BSON(
			"model" << boRecord["model"]
			<< "type" << m_iCIType
			<< "u_space" << 0
			);
	}
	return boMappingRecord;
}

BSONObj CDeviceModel::GetModelMappingCondition(BSONObj boRecord)
{
	BSONObj boMappingCondition;
	if (boRecord.hasField("model"))
	{
		boMappingCondition = BSON(
			"model" << boRecord["model"]
			);
	}
	return boMappingCondition;
}

void CDeviceModel::BuildBSONObj(BSONObjBuilder& boBuilder, int iFormat)
{
	switch (iFormat)
	{
	case SAVE_RACK_MAP:
		boBuilder.append(FIELD_FROM_U, m_iU);
		boBuilder.append(FIELD_TO_U, m_nToU);
		break;
	}
}

void CDeviceModel::Load(const BSONObj& boRecord)
{
	bool bHasU		= boRecord.hasField("u");
	bool bHasUSpace = boRecord.hasField("u_space");

	m_iU			= bHasU ? boRecord.getIntField("u") : U_DEFAULT;
	m_iSpace		= bHasUSpace ? boRecord.getIntField("u_space") : U_SPACE_DEFAULT;

	if (bHasU && bHasUSpace)
	{
		if (m_iSpace < U_SPACE_DEFAULT)
		{
			m_iSpace = U_SPACE_DEFAULT;
		}

		m_nToU = m_iU + m_iSpace - 1;
	}
}