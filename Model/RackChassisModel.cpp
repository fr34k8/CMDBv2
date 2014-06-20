#include "RackChassisModel.h"
#include "RackBayChassisModel.h"
#include "RackSwitchChassisModel.h"
#include "ChassisModel.h"

#define INDEX_FROM_U		0
#define INDEX_TO_U			1
#define INDEX_MODEL			2
#define INDEX_IP			3
#define INDEX_BAY			4
#define INDEX_FLOOR			5

CRackChassisModel::CRackChassisModel(void)
{
	m_bHasBay = false;
	m_bHasSwitch = false;
	m_mapFieldIndex[FIELD_FROM_U]			= INDEX_FROM_U;
	m_mapFieldIndex[FIELD_TO_U]				= INDEX_TO_U;
	m_mapFieldIndex[FIELD_MODEL]			= INDEX_MODEL;
	m_mapFieldIndex[FIELD_IP]				= INDEX_IP;
	m_mapFieldIndex[FIELD_BAY]				= INDEX_BAY;
	m_mapFieldIndex[FIELD_FLOOR]			= INDEX_FLOOR;
	
	m_mapFieldType[FIELD_FROM_U]			= BSON_INT_TYPE;
	m_mapFieldType[FIELD_TO_U]				= BSON_INT_TYPE;
	m_mapFieldType[FIELD_MODEL]				= BSON_STRING_TYPE;
	m_mapFieldType[FIELD_IP]				= BSON_STRING_TYPE;
	m_mapFieldType[FIELD_BAY]				= BSON_ARRAY_TYPE;
	m_mapFieldType[FIELD_FLOOR]				= BSON_INT_TYPE;
}

CRackChassisModel::~CRackChassisModel(void)
{
}

CRackChassisModel::operator int()
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
	case INDEX_FLOOR:
		iValue = m_iFloor;
		break;
	}
	return iValue;
}

CRackChassisModel::operator std::string()
{
	string strValue;

	switch (m_iFieldIndex)
	{
	case INDEX_MODEL:
		strValue = m_strModel;
		break;
	case INDEX_IP:
		strValue = m_strIP;
		break;
	}

	return strValue;
}
CMongodbModel& CRackChassisModel::operator=(int iValue)
{
	switch (m_iFieldIndex)
	{
	case INDEX_FROM_U:
		m_iU = iValue;
		break;
	case INDEX_TO_U:
		m_nToU = iValue;
		break;
	case INDEX_FLOOR:
		m_iFloor = iValue;
		break;
	}

	CMongodbModel::operator=(iValue);
}
CMongodbModel& CRackChassisModel::operator=(string strValue)
{
	switch (m_iFieldIndex)
	{
	case INDEX_MODEL:
		m_strModel = strValue;
		break;
	case INDEX_IP:
		m_strIP = strValue;
		break;
	}

	CMongodbModel::operator=(strValue);
}

CRackChassisModel::operator BSONArray()
{
	BSONArray boArray;
	switch (m_iFieldIndex)
	{
	case INDEX_BAY:
		boArray = m_barrBay;		
		break;
	}

	return boArray;
}

CMongodbModel& CRackChassisModel::operator=(BSONArray boValue)
{
	switch (m_iFieldIndex)
	{
	case INDEX_BAY:
		m_barrBay = boValue;
		break;
	}

	CMongodbModel::operator=(boValue);
}


void CRackChassisModel::AddRackBayChassisModel(RackBayChassisModelArray* pRackChassisModelArray)
{
	BSONObj boDevice;
	CDeviceModel *pRackChassisModel;
	RackBayChassisModelArray::iterator it;
	it = pRackChassisModelArray->begin();
	while (it != pRackChassisModelArray->end())
	{
		pRackChassisModel = *it;
		pRackChassisModel->Save(boDevice);
		m_babBayOfChassis.append(boDevice);
		it++;
	}
	m_bHasBay = true;
}

void CRackChassisModel::AddRackSwitchChassisModel(RackSwitchChassisModelArray* pRackChassisModelArray)
{
	BSONObj boDevice;
	CDeviceModel *pRackChassisModel;
	RackSwitchChassisModelArray::iterator it;
	it = pRackChassisModelArray->begin();
	while (it != pRackChassisModelArray->end())
	{
		pRackChassisModel = *it;
		pRackChassisModel->Save(boDevice);
		m_babSwitchOfChassis.append(boDevice);
		it++;
	}
	m_bHasSwitch = true;
}

void CRackChassisModel::Load(const BSONObj& boRecord)
{	
	(*this)[FIELD_IP] = CChassisModel::GetIPAddress(boRecord);
	(*this)[FIELD_MODEL] = CChassisModel::GetModel(boRecord);
	(*this)[FIELD_FLOOR] = CChassisModel::GetFloor(boRecord);
	/*(*this)[FIELD_FROM_U]			= boRecord.hasField("u") ? boRecord.getIntField("u") : 0;

	m_iSpace						= boRecord.hasField("u_space") ? boRecord.getIntField("u_space") : 0;	
	(*this)[FIELD_TO_U]				= m_iU + m_iSpace - 1;*/

	CDeviceModel::Load(boRecord);
}

bool CRackChassisModel::ToBSONObj(BSONObj& boRecord)
{		
	if (m_bHasBay)
	{		
		(*this)[FIELD_BAY] = m_babBayOfChassis.arr();				
	}
	if (m_bHasSwitch)
	{
		(*this)[FIELD_SWITCH] = m_babSwitchOfChassis.arr();
	}
	CDeviceModel::ToBSONObj(boRecord);
}

void CRackChassisModel::BuildBSONObj(BSONObjBuilder& boBuilder, int iFormat)
{
	switch (iFormat)
	{
	case SAVE_RACK_MAP:
		boBuilder.append(FIELD_IP, m_strIP);
		boBuilder.append(FIELD_MODEL, m_strModel);
		boBuilder.append(FIELD_BAY, m_babBayOfChassis.arr());
		boBuilder.append(FIELD_SWITCH, m_babSwitchOfChassis.arr());
		boBuilder.append(FIELD_FLOOR, m_iFloor);
		break;
	}

	CDeviceModel::BuildBSONObj(boBuilder, iFormat);
}