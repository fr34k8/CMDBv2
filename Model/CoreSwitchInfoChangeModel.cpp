#include "CoreSwitchInfoChangeModel.h"

CCoreSwitchInfoChangeModel::CCoreSwitchInfoChangeModel(void)
{
	InitLookUpMap();
}

CCoreSwitchInfoChangeModel::~CCoreSwitchInfoChangeModel(void)
{
}

void CCoreSwitchInfoChangeModel::InitLookUpByPass()
{
	m_mapLookUpByPass["core_switch_id"] = true;
}
