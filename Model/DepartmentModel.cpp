#include "DepartmentModel.h"

CDepartmentModel::CDepartmentModel(void)
{
	m_strCode = "";
	m_strAlias = "";
	m_strName = "";
	m_strDivisionAlias = "";
	m_strDivisionHRCode = "";
	m_strHRId = "";
	m_strHRCode = "";
	m_iStatus = -1;
	m_iDeleted = 0;	
}

CDepartmentModel::~CDepartmentModel(void)
{
}

BSONObj CDepartmentModel::GetDepartmentInfo()
{
	BSONObj boDataInfo = BSON("name" << m_strName << "code" << m_strCode << "alias" << m_strAlias <<
							  "hr_id" << m_strHRId << "hr_code" << m_strHRCode <<
							  "status" << m_iStatus << "deleted" << m_iDeleted <<
							  "division_id" << m_beDivisionId << "division_alias" << m_strDivisionAlias <<
							  "division_hr_code" << m_strDivisionHRCode);
	
	return boDataInfo;
}