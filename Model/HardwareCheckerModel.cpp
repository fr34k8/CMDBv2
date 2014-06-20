#include "HardwareCheckerModel.h"

CHardwareCheckerModel::CHardwareCheckerModel(void)
{
	m_strSerialNumber = "";
	m_strSnSCpuInfo = "" ;
	m_strSnSModelInfo = "";
	m_strCmdbCpuInfo = "";
	m_strCmdbModelInfo = "";
	m_nIsMatch = 1;
}

CHardwareCheckerModel::~CHardwareCheckerModel(void)
{
}

BSONObj CHardwareCheckerModel::GetHardwareCheckerInfo()
{
	BSONObj boDataInfo = BSON("serial_number" << m_strSerialNumber << "sns_cpu_info" << m_strSnSCpuInfo << 
							  "cmdb_cpu_info" << m_strCmdbCpuInfo << "sns_model_info" << m_strSnSModelInfo <<
							  "cmdb_model_info" << m_strCmdbModelInfo << "is_match" << m_nIsMatch);
	return boDataInfo;
}