#include "RackPDUModel.h"

#define FIELD_AMPE		"ampe"
#define FIELD_CURRENT	"current"
#define FIELD_NAME		"name"
#define FIELD_UNIT		"unit"
#define FIELD_PMM		"pmm"

CRackPDUModel::CRackPDUModel(void)
{
}

CRackPDUModel::~CRackPDUModel(void)
{
}

void CRackPDUModel::Load(const BSONObj& boPDUInfo)
{
	m_dAmpe = boPDUInfo.hasField(FIELD_CURRENT) ? atof(boPDUInfo.getStringField(FIELD_CURRENT)) : 0;
	m_strName	= boPDUInfo.hasField(FIELD_NAME) ? boPDUInfo.getStringField(FIELD_NAME) : "";
	m_strUnit	= boPDUInfo.hasField(FIELD_UNIT) ? boPDUInfo.getStringField(FIELD_UNIT) : "";
	m_strPMM	= boPDUInfo.hasField(FIELD_PMM) ? boPDUInfo.getStringField(FIELD_PMM) : "";
	CDeviceModel::Load(boPDUInfo);
}

void CRackPDUModel::BuildBSONObj(BSONObjBuilder& boBuilder, int iFormat)
{
	switch (iFormat)
	{
	case SAVE_RACK_MAP:	
		boBuilder.append(FIELD_AMPE, m_dAmpe);
		boBuilder.append(FIELD_NAME, m_strName);
		boBuilder.append(FIELD_UNIT, m_strUnit);
		boBuilder.append(FIELD_PMM, m_strPMM);
		break;
	}
}