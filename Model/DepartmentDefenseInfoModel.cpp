#include "DepartmentDefenseInfoModel.h"

CDepartmentDefenseInfoModel::CDepartmentDefenseInfoModel(void)
{
	m_strHRId = "";
	m_strHRCode = "";
	m_strAlias = "";
	m_strCode = "";
	m_strDivisionAlias = "";
	m_strDivisionHRCode = "";
	m_strChangeBy = "";
	m_iStatus = -1;
	m_iDeleted = 0;
	m_iActionType = -1;
	m_iClock = 0;
}

CDepartmentDefenseInfoModel::~CDepartmentDefenseInfoModel(void)
{
}

BSONObj CDepartmentDefenseInfoModel::GetDepartmentDefenseInfo()
{
	BSONObj boDataInfo = BSON("ci_id" << m_beCIId << "hr_id" << m_strHRId << "hr_code" << m_strHRCode <<
								"code" << m_strCode << "alias" << m_strAlias << 
								"division_id" << m_beDivisionId << "division_alias" << m_strDivisionAlias << 
								"division_hr_code" << m_strDivisionHRCode << 
								"status" << m_iStatus << "deleted" << m_iDeleted << "action_type" << m_iActionType <<
								"change_by" << m_strChangeBy << "clock" << m_iClock
								);
	return boDataInfo;
}

