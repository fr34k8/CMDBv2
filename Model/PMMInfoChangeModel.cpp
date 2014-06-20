#include "PMMInfoChangeModel.h"

CPMMInfoChangeModel::CPMMInfoChangeModel(void)
{
	InitLookUpMap();
}

CPMMInfoChangeModel::~CPMMInfoChangeModel(void)
{
}

void CPMMInfoChangeModel::InitLookUpByPass()
{
	m_mapLookUpByPass["pmm_id"] = true;
}
