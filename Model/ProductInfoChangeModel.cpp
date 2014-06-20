#include "ProductInfoChangeModel.h"

CProductInfoChangeModel::CProductInfoChangeModel(void)
{
	InitLookUpMap();
}

CProductInfoChangeModel::~CProductInfoChangeModel(void)
{
}

void CProductInfoChangeModel::InitLookUpFieldValue()
{
	m_bIsValueMapping = true;
	m_mapLookUpFieldValue["status"]["0"] = "New";
	m_mapLookUpFieldValue["status"]["1"] = "In Used";
	m_mapLookUpFieldValue["status"]["2"] = "Transferring";
	m_mapLookUpFieldValue["status"]["3"] = "Remove";
	m_mapLookUpFieldValue["status"]["4"] = "Close";	
}

void CProductInfoChangeModel::InitLookUpByPass()
{
	m_mapLookUpByPass["cb_date"] = true;
	m_mapLookUpByPass["closed_date"] = true;
	m_mapLookUpByPass["deleted"] = true;
	m_mapLookUpByPass["department_code"] = true;
	m_mapLookUpByPass["department_fa_alias"] = true;
	m_mapLookUpByPass["department_hr_code"] = true;
	m_mapLookUpByPass["department_id"] = true;
	m_mapLookUpByPass["division_hr_code"] = true;
	m_mapLookUpByPass["division_id"] = true;
	m_mapLookUpByPass["fa_alias"] = true;
	m_mapLookUpByPass["fa_code"] = true;
	m_mapLookUpByPass["fa_status"] = true;
	m_mapLookUpByPass["group_code"] = true;
	m_mapLookUpByPass["ob_date"] = true;
	m_mapLookUpByPass["owner_department_code"] = true;
	m_mapLookUpByPass["owner_department_id"] = true;
	m_mapLookUpByPass["owner_division_hr_code"] = true;
	m_mapLookUpByPass["owner_division_id"] = true;
	m_mapLookUpByPass["request_code"] = true;
	m_mapLookUpByPass["vlan_info"] = true;
	m_mapLookUpByPass["vlan_type"] = true;
	m_mapLookUpByPass["ip_range"] = true;
	m_mapLookUpByPass["vlan_id"] = true;
	m_mapLookUpByPass["site"] = true;
}