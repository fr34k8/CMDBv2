#include "AccessSwitchInfoChangeModel.h"

CAccessSwitchInfoChangeModel::CAccessSwitchInfoChangeModel(void)
{
	InitLookUpMap();
}

CAccessSwitchInfoChangeModel::~CAccessSwitchInfoChangeModel(void)
{
}

void CAccessSwitchInfoChangeModel::InitLookUpByPass()
{
	m_mapLookUpByPass["access_switch_id"] = true;
}
