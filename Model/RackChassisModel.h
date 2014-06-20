#pragma once
#include "DeviceModel.h"

#define FIELD_FROM_U "from_u"
#define FIELD_TO_U "to_u"
#define FIELD_MODEL "model"
#define FIELD_FLOOR "floor_layer"
#define FIELD_IP "ip"
#define FIELD_BAY "bay"
#define FIELD_SWITCH "switch"

class CRackBayChassisModel;
class CRackSwitchChassisModel;
typedef vector<CDeviceModel*> RackChassisModelArray;
typedef vector<CRackBayChassisModel*> RackBayChassisModelArray;
typedef vector<CRackSwitchChassisModel*> RackSwitchChassisModelArray;
class CRackChassisModel:
	public CDeviceModel
{
public:
	CRackChassisModel(void);
	~CRackChassisModel(void);

	operator int();
	operator string();
	operator BSONArray();

	CMongodbModel& operator=(BSONArray boValue);
	CMongodbModel& operator=(int iValue);
	CMongodbModel& operator=(string strValue);

	void Load(const BSONObj& boRecord);
	bool ToBSONObj(BSONObj& boRecord);
	void AddRackBayChassisModel(RackBayChassisModelArray* pRackChassisModelArray);
	void AddRackSwitchChassisModel(RackSwitchChassisModelArray* pRackChassisModelArray);
protected:
	void BuildBSONObj(BSONObjBuilder& boBuilder, int iFormat = 0);
private:	
	string m_strModel;
	string m_strIP;
	int m_iFloor;
	BSONArray m_barrBay;
	BSONArrayBuilder m_babBayOfChassis;
	BSONArrayBuilder m_babSwitchOfChassis;
	bool m_bHasBay;
	bool m_bHasSwitch;
};