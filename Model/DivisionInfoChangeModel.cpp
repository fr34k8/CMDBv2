#include "DivisionInfoChangeModel.h"

CDivisionInfoChangeModel::CDivisionInfoChangeModel(void)
{
	InitLookUpMap();
}

CDivisionInfoChangeModel::~CDivisionInfoChangeModel(void)
{
}

void CDivisionInfoChangeModel::InitLookUpFieldValue()
{
	m_bIsValueMapping = true;
	m_mapLookUpFieldValue["chassis"][""] = ""; //0: InActive, 1: Active
	m_mapLookUpFieldValue["status"]["0"] = "InActive";
	m_mapLookUpFieldValue["status"]["1"] = "Active";
}

void CDivisionInfoChangeModel::InitLookUpByPass()
{
	m_mapLookUpByPass["code"] = true;
	m_mapLookUpByPass["hr_code"] = true;
	m_mapLookUpByPass["hr_created_at"] = true;
	m_mapLookUpByPass["hr_id"] = true;
	m_mapLookUpByPass["hr_last_updated"] = true;
	m_mapLookUpByPass["hr_parent_code"] = true;
	m_mapLookUpByPass["is_virtual"] = true;
	m_mapLookUpByPass["mis_alias"] = true;
	m_mapLookUpByPass["deleted"] = true;
}