#include "DepartmentInfoChangeModel.h"

CDepartmentInfoChangeModel::CDepartmentInfoChangeModel(void)
{
	InitLookUpMap();
}

CDepartmentInfoChangeModel::~CDepartmentInfoChangeModel(void)
{
}

void CDepartmentInfoChangeModel::InitLookUpFieldValue()
{
	m_bIsValueMapping = true;
	m_mapLookUpFieldValue["status"]["0"] = "Inactive";
	m_mapLookUpFieldValue["status"]["1"] = "Active";	
}

void CDepartmentInfoChangeModel::InitLookUpByPass()
{
	m_mapLookUpByPass["division_id"] = true;
	m_mapLookUpByPass["fa_alias"] = true;
	m_mapLookUpByPass["fa_code"] = true;
	m_mapLookUpByPass["hr_id"] = true;
	m_mapLookUpByPass["name"] = true;
	m_mapLookUpByPass["deleted"] = true;
}