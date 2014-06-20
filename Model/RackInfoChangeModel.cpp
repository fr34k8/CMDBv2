#include "RackInfoChangeModel.h"

CRackInfoChangeModel::CRackInfoChangeModel(void)
{
	InitLookUpMap();
}

CRackInfoChangeModel::~CRackInfoChangeModel(void)
{
}

void CRackInfoChangeModel::InitLookUpByPass()
{
	m_mapLookUpByPass["chassis"] = true;
	m_mapLookUpByPass["available_u"] = true;
	m_mapLookUpByPass["server_u"] = true;
	m_mapLookUpByPass["switch"] = true;
	m_mapLookUpByPass["api_id"] = true;
	m_mapLookUpByPass["vlan"] = true;
	m_mapLookUpByPass["deleted"] = true;
}
