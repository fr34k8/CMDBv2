#include "ChassisModel.h"

#define FIELD_IP_ADDRESS "ip_address"
#define FIELD_MODEL "model"
#define FIELD_FLOOR "floor_layer"

CChassisModel::CChassisModel(void)
{
}

CChassisModel::~CChassisModel(void)
{
}

string CChassisModel::GetIPAddress(BSONObj boCIInfo)
{
	string strIPAddress = boCIInfo.hasField(FIELD_IP_ADDRESS) ? boCIInfo.getStringField(FIELD_IP_ADDRESS) : "";	

	return strIPAddress;
}

string CChassisModel::GetModel(BSONObj boCIInfo)
{
	string strModel = boCIInfo.hasField(FIELD_MODEL) ? boCIInfo.getStringField(FIELD_MODEL) : "";	

	return strModel;
}

int CChassisModel::GetFloor(BSONObj boCIInfo)
{
	int iFloor = boCIInfo.hasField(FIELD_FLOOR) ? boCIInfo.getIntField(FIELD_FLOOR) : 0;

	return iFloor;
}