#include "MailboxController.h"
#include "../Common/DBCommon.h"
#include "../Model/MailboxModel.h"

CMailboxController::CMailboxController(void)
{
	m_strTableName = TBL_MAIL_BOX;
}

CMailboxController::~CMailboxController(void)
{

}

void CMailboxController::NotifyServerLocation(const BSONObj& boServerInfo)
{
	BSONObj boMailInfo;
	CMailboxModel::CreateServerLocationMailInfo(boServerInfo, boMailInfo);

	Insert(boMailInfo);
}

void CMailboxController::NotifyServerNetwork(const BSONObj& boServerInfo)
{
	BSONObj boMailInfo;
	CMailboxModel::CreateServerNetworkMailInfo(boServerInfo, boMailInfo);

	Insert(boMailInfo);
}

void CMailboxController::NotifySwitchLocation(const BSONObj &boSwitchInfo)
{
	BSONObj boMailInfo;
	CMailboxModel::CreateSwitchChassisLocationMailInfo(boSwitchInfo, boMailInfo);

	Insert(boMailInfo);
}

void CMailboxController::NotifyMISServiceProblem(const mongo::BSONObj &boProblemInfo)
{
	BSONObj boMailInfo;
	CMailboxModel::CreateNotifyMISServiceMailInfo(boProblemInfo, boMailInfo);

	Insert(boMailInfo);
}