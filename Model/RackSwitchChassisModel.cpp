#include "RackSwitchChassisModel.h"
#include "ServerModel.h"
#include "MongodbModel.h"

#define FIELD_SWITCH_SERIAL "switch_serial"
#define FIELD_SWITCH_NAME	"switch_name"
#define FIELD_SWITCH_TYPE	"switch_type"

CRackSwitchChassisModel::CRackSwitchChassisModel(void)
{
}

CRackSwitchChassisModel::~CRackSwitchChassisModel(void)
{
}

void CRackSwitchChassisModel::Load(const BSONObj& boRecord)
{
	m_strSwitchSerial = CMongodbModel::GetStringFieldValue(boRecord, "serial", "");
	m_strSwitchName = CMongodbModel::GetStringFieldValue(boRecord, "name", "");
	CDeviceModel::Load(boRecord);
}


void CRackSwitchChassisModel::BuildBSONObj(BSONObjBuilder& boBuilder, int iFormat)
{
	switch (iFormat)
	{
	case SAVE_RACK_MAP:
		boBuilder.append(FIELD_SWITCH_SERIAL, m_strSwitchSerial);
		boBuilder.append(FIELD_SWITCH_NAME, m_strSwitchName);
		boBuilder.append(FIELD_SWITCH_TYPE, m_iCIType);
		break;
	}

}
