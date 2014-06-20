#include "MailboxModel.h"
#include "ServerModel.h"
#include "RackModel.h"
#include "../Common/DBCommon.h"

#define APPLICATION_DC_LOCATION "dc_location"
#define FUNCTION_NOTI_SERVER_LOCATION "dc_noti_server_location"
#define DEPARTMENT_SNS "SnS"
#define DEPARTMENT_DC "DC"
#define DEPARTMENT_MIS "MIS"

CMailboxModel::CMailboxModel(void)
{
	m_strApplication = m_strFunction = m_strSourceFrom = m_strTechOwner = "";
	m_lClock = 0;
}

CMailboxModel::~CMailboxModel(void)
{
}

BSONObj CMailboxModel::GetBSONModel()
{
	BSONObj boModel = BSON(
		"application"	<<	m_strApplication	<<
		"clock"			<<	m_lClock			<<
		"function"		<<	m_strFunction		<<
		"source_from"	<< m_strSourceFrom		<<
		"to"			<< m_strTechOwner		<<
		"data"			<<  m_boData
		);
	return boModel.copy();
}

void CMailboxModel::CreateServerLocationMailInfo(const BSONObj& boServerInfo, 
												 BSONObj& boMailInfo)
{
	BSONObj boServerData;
	CServerModel::CreateLocationMailInfo(boServerInfo, boServerData);

	boMailInfo = BSON(
		"application"	<<	APPLICATION_DC_LOCATION	<<
		"clock"			<<	atoll(CUtilities::GetCurrTimeStamp().c_str())	<<
		"function"		<<	FUNCTION_NOTI_SERVER_LOCATION	<<
		"source_from"	<<	DEPARTMENT_SNS	<<
		"data"			<<  boServerData);
}

void CMailboxModel::CreateServerNetworkMailInfo(const BSONObj& boServerInfo, 
												BSONObj& boMailInfo)
{
}

void CMailboxModel::CreateSwitchChassisLocationMailInfo(const BSONObj &boSwitchChassisInfo, 
														BSONObj &boMailInfo)
{
	BSONObj boSwitchData;
	CRackModel::CreateSwitchChassisMailInfo(boSwitchChassisInfo, boSwitchData);

	boMailInfo = BSON(
		"application"	<<	APP_BACKEND_HANDEL_ACCESS_SWITCH	<<
		"clock"			<<	atoll(CUtilities::GetCurrTimeStamp().c_str())	<<
		"function"		<<	FUNCTION_GRAPHIC_SWITCH_CHASSIS	<<
		"source_from"	<<	DEPARTMENT_DC	<<
		"data"			<<  boSwitchData);
}

void CMailboxModel::CreateTechnicalOwnerUserName(const BSONObj& boServerInfo, BSONObj& boUserArray)
{
	vector<BSONElement> vbeTechnicalOwner, vbeUsers;
	vector<BSONElement>::iterator it, uit;
	BSONObj boTechnicalOwner;
	BSONArrayBuilder babUserArray;
	map<BSONElement, bool> mapTechnicalOwner;
	if (boServerInfo.hasField("technical_owner"))// && boServerInfo["technical_owner"].type() == BSON_ARRAY_TYPE)
	{
		if (boServerInfo["technical_owner"].type() != BSON_ARRAY_TYPE){ return; }
		vbeTechnicalOwner = boServerInfo["technical_owner"].Array();
		for (it = vbeTechnicalOwner.begin(); it != vbeTechnicalOwner.end(); it++)
		{
			boTechnicalOwner = (*it).Obj();
			if (boTechnicalOwner.hasField("users"))// && boTechnicalOwner["users"].type() == BSON_ARRAY_TYPE)
			{
				if (boTechnicalOwner["users"].type() != BSON_ARRAY_TYPE){ return; }
				vbeUsers = boTechnicalOwner["users"].Array();
				for (uit = vbeUsers.begin(); uit != vbeUsers.end(); uit++)
				{
					if (mapTechnicalOwner.find(*uit) == mapTechnicalOwner.end())
					{
						mapTechnicalOwner[*uit] = true;
						babUserArray << *uit;
					}
				}
			}
		}
	}
	boUserArray = BSON("technical_owner" << babUserArray.arr());
}

void CMailboxModel::CreateNotifyMISServiceMailInfo(const mongo::BSONObj &boDataNotiInfo, mongo::BSONObj &boMailInfo)
{
	boMailInfo = BSON(
		"application"	<<	APP_BACKEND_HANDLE_DATA_MIS	<<
		"clock"			<<	atoll(CUtilities::GetCurrTimeStamp().c_str())	<<
		"function"		<<	FUNCTION_NOTIFY_LOST_DATA_SERVICE	<<
		"source_from"	<<	DEPARTMENT_MIS	<<
		"data"			<<  boDataNotiInfo);
}