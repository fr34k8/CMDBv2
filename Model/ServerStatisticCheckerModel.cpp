#include "ServerStatisticCheckerModel.h"

CServerStatisticCheckerModel::CServerStatisticCheckerModel(void)
{
	m_iSnSVirtual = 0;
	m_iSnSPhysical = 0;
	m_iCMDBVirtual = 0;
	m_iCMDBU = 0;
	m_iCMDBChassis = 0;
	m_iCMDBUnknown = 0;
	m_iClock = 0;
}

CServerStatisticCheckerModel::~CServerStatisticCheckerModel(void)
{
}

BSONObj CServerStatisticCheckerModel::GetServerStatisticCheckerInfo()
{
	BSONObj boDataInfo = BSON("sns_virtual" << m_iSnSVirtual << "sns_physical" << m_iSnSPhysical << 
							  "cmdb_virtual" << m_iCMDBVirtual << "cmdb_u" << m_iCMDBU <<
							  "cmdb_chassis" << m_iCMDBChassis << "cmdb_unknown" << m_iCMDBUnknown <<
							  "clock" << m_iClock);
	return boDataInfo;
}