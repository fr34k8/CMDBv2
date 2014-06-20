#include "DivisionDefenseInfoModel.h"

CDivisionDefenseInfoModel::CDivisionDefenseInfoModel(void)
{
	m_strHRId = "";
	m_strHRCode = "";
	m_strAlias = "";
	m_strCode = "";
	m_strChangeBy = "";
	m_iStatus = -1;
	m_iDeleted = 0;
	m_iActionType = -1;
	m_iClock = 0;
}

CDivisionDefenseInfoModel::~CDivisionDefenseInfoModel(void)
{
}

BSONObj CDivisionDefenseInfoModel::GetDivisionDefenseInfo()
{
	BSONObj boDataInfo = BSON("ci_id" << m_beCIId << "hr_id" << m_strHRId << "hr_code" << m_strHRCode <<
								"code" << m_strCode << "alias" << m_strAlias << "change_by" << m_strChangeBy <<
								"status" << m_iStatus << "deleted" << m_iDeleted << "action_type" << m_iActionType <<
								"clock" << m_iClock);
	return boDataInfo.copy();
}

