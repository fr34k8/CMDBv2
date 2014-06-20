#include "ServerInfoChangeModel.h"

CServerInfoChangeModel::CServerInfoChangeModel(void)
{
	InitLookUpMap();
}

CServerInfoChangeModel::~CServerInfoChangeModel(void)
{
}

void CServerInfoChangeModel::InitLookUpFieldValue()
{
	m_bIsValueMapping = true;
	m_mapLookUpFieldValue["status"]["0"] = "Unused";
	m_mapLookUpFieldValue["status"]["1"] = "In Used";
	m_mapLookUpFieldValue["status"]["2"] = "Borrow";
	m_mapLookUpFieldValue["status"]["3"] = "Transfer";
	m_mapLookUpFieldValue["status"]["4"] = "Error";
	m_mapLookUpFieldValue["power_status"]["0"] = "Off";
	m_mapLookUpFieldValue["power_status"]["1"] = "On";
	m_mapLookUpFieldValue["power_status"]["2"] = "Unknown";
	m_mapLookUpFieldValue["server_type"]["-1"] = "Unknown";
	m_mapLookUpFieldValue["server_type"]["1"] = "Virtual";
	m_mapLookUpFieldValue["server_type"]["2"] = "Server U";
	m_mapLookUpFieldValue["server_type"]["3"] = "Server Chassis";
}

void CServerInfoChangeModel::InitLookUpByPass()
{
	m_mapLookUpByPass["chassis_id"] = true;
	m_mapLookUpByPass["deleted"] = true;
	m_mapLookUpByPass["department_code"] = true;
	m_mapLookUpByPass["department_hr_code"] = true;
	m_mapLookUpByPass["division_hr_code"] = true;
	m_mapLookUpByPass["technical_group_id"] = true;
	m_mapLookUpByPass["technical_owner"] = true;
	m_mapLookUpByPass["u_space"] = true;
	m_mapLookUpByPass["product_status"] = true;
	m_mapLookUpByPass["auto_update"] = true;
	m_mapLookUpByPass["zabbix_os_info_last_update"] = true;
	m_mapLookUpByPass["zabbix_system_info_last_updated"] = true;
	m_mapLookUpByPass["installed_date"] = true;
	m_mapLookUpByPass["uuid"] = true;
}