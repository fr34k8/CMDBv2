#include "HardwareCheckerController.h"
#include "../Common/DBCommon.h"
#include "../Model/CollectorModel.h"
#include "../Model/JsonModel.h"
#include "../Model/HardwareCheckerModel.h"
#include "../DataChecker/HardwareChecker.h"

CHardwareCheckerController::CHardwareCheckerController(void)
{
}


CHardwareCheckerController::~CHardwareCheckerController(void)
{
	ClearMapHardwareInfo();
}

/*============= ClearMapHardwareInfo ========================
 * Function: ClearMapHardwareInfo
 * Description: Clear HardwareCheckerModel in memory
 * Return: void
 *========================================================================
 */
void CHardwareCheckerController::ClearMapHardwareInfo()
{
	SerialNumber2HardwareInfoMap::iterator it = m_mapSerialNumber2DHardwareInfoMap.begin();
	while(it != m_mapSerialNumber2DHardwareInfoMap.end())
	{
		delete (*it).second;
		it++;
	}
}

/*============= GetHardwareCheckerInfoBySerialNumber ========================
 * Function: GetHardwareCheckerInfoBySerialNumber
 * Description: Get HardwareCheckerModel in memory
 * Return: CHardwareCheckerModel
 *========================================================================
 */
CHardwareCheckerModel* CHardwareCheckerController::GetHardwareCheckerInfoBySerialNumber(const string& strSerialNumber)
{
	CHardwareCheckerModel* pHardwareCheckerModel = NULL;

	SerialNumber2HardwareInfoMap::iterator it = m_mapSerialNumber2DHardwareInfoMap.find(strSerialNumber);
	
	if (it != m_mapSerialNumber2DHardwareInfoMap.end())
	{
		pHardwareCheckerModel = (*it).second;
	}
	else
	{
		pHardwareCheckerModel = new CHardwareCheckerModel();		
		m_mapSerialNumber2DHardwareInfoMap[strSerialNumber] = pHardwareCheckerModel;
	}

	return pHardwareCheckerModel;
}

/*============= Get list serial number physical========================
 * Function: GetListSerialNumber
 * Description: Get list serial number of physical server
 * Return: vector<char*>
 *========================================================================
 */
void CHardwareCheckerController::LoadCMDBHardwareInfo(auto_ptr<DBClientCursor> &ptrServerResultCursor)
{
	CHardwareCheckerModel *pHardwareCheckerModel;
	BSONObj oServerInfo;
	string strSerialNumber;
	string strCpuCfg;
	string strServerModelCfg;
	BSONArrayBuilder baServerType;
	baServerType.append(SERVER_U);
	baServerType.append(SERVER_CHASSIS);
	baServerType.append(UNKNOWN);
	Query qCondition = QUERY("server_type" << BSON("$in" << baServerType.arr()));
					
	//ptrServerResultCursor = Find(TBL_SERVER, qCondition);
	if (!Find(TBL_SERVER, ptrServerResultCursor, qCondition))
	{
		return;
	}	

	try
	{		
		while(ptrServerResultCursor->more())
		{
			strSerialNumber = strCpuCfg = strServerModelCfg = "";
			oServerInfo = ptrServerResultCursor->nextSafe();

			strSerialNumber = oServerInfo.getStringField("code");
			strCpuCfg = oServerInfo.getStringField("cpu_config");
			strServerModelCfg = oServerInfo.getStringField("server_model");

			pHardwareCheckerModel = GetHardwareCheckerInfoBySerialNumber(strSerialNumber);
			pHardwareCheckerModel->SetSerialNumber(strSerialNumber);
			pHardwareCheckerModel->SetCmdbCpuInfo(strCpuCfg);
			pHardwareCheckerModel->SetCmdbModelInfo(strServerModelCfg);
		}		
	}
	catch(exception& ex)
	{	
		stringstream ssErrorMsg;
		string strLog;
		ssErrorMsg << ex.what() << "][" << __FILE__ << "|" << __LINE__ ;
		strLog = CUtilities::FormatLog(ERROR_MSG, "CCheckerController", "LoadCMDBHardwareInfo","exception:" + ssErrorMsg.str());
		CUtilities::WriteErrorLog(ERROR_MSG, strLog);
	}
}

/*============= Compare hardware info with SnS ========================
 * Function: CompareHardwareWithSnS
 * Description: Compare hardware info with SnS
 * Return: void
 *========================================================================
 */
void CHardwareCheckerController::CompareHardwareWithSnS(CCollectorModel *pCollectorInfo, CHardwareChecker *pHardwareChecker)
{
	auto_ptr<DBClientCursor> ptrServerResultCursor = auto_ptr<DBClientCursor>();
	LoadCMDBHardwareInfo(ptrServerResultCursor);

	if (ptrServerResultCursor.get() == NULL)
	{
		return;
	}
	
	string strSerialNumber;
	string strCpuInfo;
	string strServerModelInfo;
	
	string strSnSCpuInfo;
	string strSnSModelInfo;
	string strDirtyTable;

	CHardwareCheckerModel *pHardwareCheckerModel;

	strDirtyTable = pCollectorInfo->GetDirtyTableName();
	
	try
	{
		BSONObj boCondition;
		Remove(strDirtyTable, boCondition);

		for( SerialNumber2HardwareInfoMap::iterator it = m_mapSerialNumber2DHardwareInfoMap.begin(); it!=m_mapSerialNumber2DHardwareInfoMap.end(); ++it)
		{
			char *pData;
			pData = NULL;
			strSerialNumber = strCpuInfo = strServerModelInfo = "";
			
			strSerialNumber = (*it).first;
			pHardwareCheckerModel = (*it).second;
		
			strCpuInfo = pHardwareCheckerModel->GetCmdbCpuInfo();
			strServerModelInfo = pHardwareCheckerModel->GetCmdbModelInfo();
			
			//Call API
			pHardwareChecker->SetSerialNumber((char*)strSerialNumber.c_str());
			pData = pHardwareChecker->CallSnSService(pCollectorInfo);
			
			if (NULL != pData)
			{
				//cout << "Data" << pData << endl;
				strSnSCpuInfo = GetSnSCpuInfo(pData);
				strSnSModelInfo = GetSnSServerModelInfo(pData);

				if (!CUtilities::IsMatch2String(strCpuInfo, strSnSCpuInfo) ||
					!CUtilities::IsMatch2String(strServerModelInfo, strSnSModelInfo))
				{
					pHardwareCheckerModel->SetIsMatch(0);
				}
				else
				{
					pHardwareCheckerModel->SetIsMatch(1);
				}
				pHardwareCheckerModel->SetSnSCpuInfo(strSnSCpuInfo);
				pHardwareCheckerModel->SetSnSModelInfo(strSnSModelInfo);
				SaveHardwareCheckerInfo(strDirtyTable, pHardwareCheckerModel);
				
				delete pData;
			}
		}
		ptrServerResultCursor.reset();
	}
	catch(exception& ex)
	{	
		stringstream ssErrorMsg;
		string strLog;
		ssErrorMsg << ex.what() << "][" << __FILE__ << "|" << __LINE__ ;
		strLog = CUtilities::FormatLog(ERROR_MSG, "CCheckerController", "LoadCMDBHardwareInfo","exception:" + ssErrorMsg.str());
		CUtilities::WriteErrorLog(strLog);
	}
	cout << "Finished" << endl;
}

/*============= Get SnS Cpu info from API ========================
 * Function: GetSnSCpuInfo
 * Description: Get SnS Cpu Info from API
 * Return: string
 *========================================================================
 */
string CHardwareCheckerController::GetSnSCpuInfo(char* pData)
{
	string strCpuInfo = "";

	CJsonModel objJsonModel; 
	string strDataInfo;
	int iTotalCPU;

	strDataInfo = pData;

	Json::Value jRootValue;
	jRootValue = objJsonModel.parseValueRootJson(strDataInfo);
	
	if (!jRootValue.isNull())
	{
		try
		{
			if (!jRootValue["Data"]["Processor"].isNull() && 
				jRootValue["Data"]["Processor"].isArray())
			{
				Json::Value joProcessor;
				joProcessor = jRootValue["Data"]["Processor"];
				
				//cout << "processor:" << joProcessor << endl;
				iTotalCPU = joProcessor.size();

				for(Json::Value::UInt index = 0 ; index < iTotalCPU; index ++)
				{
					if (!joProcessor[index]["name"].isNull())
					{
						strCpuInfo = joProcessor[index]["name"].asString();
					}
				}
			}
		}
		catch(exception& ex)
		{
		}
	}

	if (strCpuInfo != "")
	{
		strCpuInfo = strCpuInfo + " x " + CUtilities::ConvertIntToString(iTotalCPU);
	}

	return strCpuInfo;
}

/*============= Get SnS Cpu info from API ========================
 * Function: GetSnSServerModelInfo
 * Description: Get SnS Server Model Info from API
 * Return: string
 *========================================================================
 */
string CHardwareCheckerController::GetSnSServerModelInfo(char* pData)
{
	string strServerModel = "";
	string strManufacture = "";
	string strManufactureLower = "";

	CJsonModel objJsonModel; 
	string strDataInfo;

	strDataInfo = pData;

	Json::Value jRootValue;
	jRootValue = objJsonModel.parseValueRootJson(strDataInfo);
	
	if (!jRootValue.isNull())
	{
		try
		{
			if (!jRootValue["Data"]["General"]["manufacture"].isNull())
			{
				strManufacture = jRootValue["Data"]["General"]["manufacture"].asString();
				strManufactureLower = CUtilities::ToLowerString(strManufacture);

				if (strManufactureLower == DELL_INC)
				{
					strManufacture = DELL;
				}
				else if ((strManufactureLower == IBM) || (strManufactureLower == INTEL))
				{
					strManufacture = "";
				}

				strServerModel += strManufacture;
			}
			if (!jRootValue["Data"]["General"]["model"].isNull())
			{
				if (strServerModel != "")
					strServerModel = strServerModel + " " + jRootValue["Data"]["General"]["model"].asString();
				else
					strServerModel = jRootValue["Data"]["General"]["model"].asString();
			}
		}
		catch(exception& ex)
		{
		}
	}
	return strServerModel;
}

/*============= SaveHardwareCheckerInfo ========================
 * Function: SaveHardwareCheckerInfo
 * Description: Save Hardware checker info in db
 * Return: void
 *========================================================================
 */
void CHardwareCheckerController::SaveHardwareCheckerInfo(const string& strTableName, CHardwareCheckerModel *pHardwareCheckerModel)
{
	BSONObj boHardwareInfo;
	BSONObj boCondition;

	boHardwareInfo = pHardwareCheckerModel->GetHardwareCheckerInfo();
	boCondition = BSON("serial_number" << pHardwareCheckerModel->GetSerialNumber());
	
	//cout << "Data:" << boHardwareInfo.toString() << endl;
	Insert(strTableName, boHardwareInfo, boCondition);
}
