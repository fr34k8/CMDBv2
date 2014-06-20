#include "InterfaceCheckerModel.h"
#include "../Common/DBCommon.h"

CInterfaceCheckerModel::CInterfaceCheckerModel(void)
{
	m_strCode = "";
	m_strVID = "";
	m_strCMDBServerName = "";
	m_strODAServerName = "";
	m_baPublicInterface = BSONArray();
	m_baPrivateInterface = BSONArray();
	m_baODAPublicInterface = BSONArray();
	m_baODAPrivateInterface = BSONArray();
	m_nServerType = -1;
	m_nServerStatus = -1;
	m_nIsMatch = 0;

}

CInterfaceCheckerModel::~CInterfaceCheckerModel(void)
{
}

BSONObj CInterfaceCheckerModel::GetInterfaceCheckerInfo()
{
	BSONObj boDataInfo = BSON("code" << m_strCode << "vid" << m_strVID << 
							  "cmdb_server_name" << m_strCMDBServerName << "oda_server_name" << m_strODAServerName <<
							  "cmdb_public_interface" << m_baPublicInterface << "oda_public_interface" << m_baODAPublicInterface <<
							  "cmdb_private_interface" << m_baPrivateInterface << "oda_private_interface" << m_baODAPrivateInterface <<
							  "server_type" << m_nServerType << "server_status" << m_nServerStatus << "is_match" << m_nIsMatch);

	return boDataInfo;
}