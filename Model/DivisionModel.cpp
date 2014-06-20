#include "DivisionModel.h"

CDivisionModel::CDivisionModel(void)
{
	m_strName = "";
	m_strCode = "";
	m_strAlias = "";
	m_strMisAlias = "";
	m_strHRId = "";
	m_strHRCode = "";
	m_strHRParentCode = "";
	m_strHRCreatedAt = "";
	m_strHRLastUpdated = "";

	m_iStatus = -1;
	m_iDeleted = 0;	
	m_nIsVirtual = 0;
}

CDivisionModel::~CDivisionModel(void)
{
}

BSONObj CDivisionModel::GetDivisionInfo()
{
	BSONObj boDataInfo = BSON("name" << m_strName << "code" << m_strCode << "alias" << m_strAlias <<
							  "hr_id" << m_strHRId << "hr_code" << m_strHRCode <<
							  "mis_alias" << m_strMisAlias << "hr_parent_code" << m_strHRParentCode << 
							  "hr_created_at" << m_strHRCreatedAt << "hr_last_updated" << m_strHRLastUpdated <<
							  "status" << m_iStatus << "deleted" << m_iDeleted << "is_virtual" << m_nIsVirtual);
	return boDataInfo.copy();
}