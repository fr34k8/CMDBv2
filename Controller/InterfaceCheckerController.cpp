#include "InterfaceCheckerController.h"
#include "../Common/DBCommon.h"
#include "../Model/CollectorModel.h"
#include "../Model/InterfaceCheckerModel.h"

CInterfaceCheckerController::CInterfaceCheckerController(void)
{
}


CInterfaceCheckerController::~CInterfaceCheckerController(void)
{
	ClearMapInterfaceInfo();
}
/*============= ClearMapInterfaceInfo ========================
 * Function: ClearMapInterfaceInfo
 * Description: Clear InterfaceCheckerModel in memory
 * Return: void
 *========================================================================
 */
void CInterfaceCheckerController::ClearMapInterfaceInfo()
{
	Code2InterfaceInfoMap::iterator it = m_mapCode2InterfaceInfoMap.begin();
	while(it != m_mapCode2InterfaceInfoMap.end())
	{
		if (NULL != (*it).second)
			delete (*it).second;
		it++;
	}
	
	m_mapCode2InterfaceInfoMap.clear();
}

/*============= GetInterfaceCheckerInfoByCode ========================
 * Function: GetInterfaceCheckerInfoByCode
 * Description: Get InterfaceCheckerMode in memory
 * Return: CInterfaceCheckerModel
 *========================================================================
 */
CInterfaceCheckerModel* CInterfaceCheckerController::GetInterfaceCheckerInfoByCode(const string& strCode)
{
	CInterfaceCheckerModel* pInterfaceCheckerModel = NULL;

	Code2InterfaceInfoMap::iterator it = m_mapCode2InterfaceInfoMap.find(strCode);
	
	if (it != m_mapCode2InterfaceInfoMap.end())
	{
		pInterfaceCheckerModel = (*it).second;
	}
	else
	{
		pInterfaceCheckerModel = new CInterfaceCheckerModel();		
		m_mapCode2InterfaceInfoMap[strCode] = pInterfaceCheckerModel;
	}

	return pInterfaceCheckerModel;
}

/*============= CompareInterfaceWithODA ========================
 * Function: CompareInterfaceWithODA
 * Description: Compare interface info & server name between ODA & CMDB
 * Return: void
 *========================================================================
 */
void CInterfaceCheckerController::CompareInterfaceWithODA(CCollectorModel *pCollectorInfo, char* pData)
{
	auto_ptr<DBClientCursor> ptrServerResultCursor = auto_ptr<DBClientCursor>();
	CJsonModel objJsonModel;
	//Clear cache
	ClearMapInterfaceInfo();
	//Load data
	LoadCMDBInterfaceInfo(ptrServerResultCursor);

	if (ptrServerResultCursor.get() == NULL)
	{
		return;
	}

	cout << "Load database okie" << endl;
	
	string strDataInfo;
	string strCode;
	string strServerName;
	string strDirtyTable;

	BSONArray baPublicInterface;
	BSONArray baPrivateInterface;
	
	Code2InterfaceInfoMap::iterator itInterface;

	CInterfaceCheckerModel *pInterfaceCheckerModel;
	strDirtyTable = pCollectorInfo->GetDirtyTableName();
	
	try
	{
		strDataInfo = pData;
		
		Json::Value jRootValue;
		jRootValue = objJsonModel.parseValueRootJson(strDataInfo);
		
		cout << "parse okie" << endl;
		if (!jRootValue["SERVERS"].isNull() && jRootValue["SERVERS"].isArray())
		{
			Json::Value joServers;
			joServers = jRootValue["SERVERS"];
			int iTotal = 0;

			for(Json::Value::UInt index = 0 ; index < joServers.size(); index ++)
			{
				iTotal++;

				Json::Value joPrivateInterface;
				Json::Value joPublicInterface;
				
				strCode = strServerName = "";
				
				strCode = joServers[index]["CODE"].asString();
				
				itInterface = m_mapCode2InterfaceInfoMap.find(strCode);
				if (itInterface == m_mapCode2InterfaceInfoMap.end())
					continue;
				
				pInterfaceCheckerModel = GetInterfaceCheckerInfoByCode(strCode);
				
				strServerName = joServers[index]["HOST_NAME"].asString();
				pInterfaceCheckerModel->SetODAServerName(strServerName);
				joPrivateInterface = joServers[index]["PRIVATE_INTERFACE"];
				joPublicInterface = joServers[index]["PUBLIC_INTERFACE"];

				if(strServerName == pInterfaceCheckerModel->GetCMDBServerName()
					&& IsMatchInterface(pInterfaceCheckerModel->GetCMDBPublicInterface(), joPublicInterface)
					&& IsMatchInterface(pInterfaceCheckerModel->GetCMDBPrivateInterface(), joPrivateInterface))
				{
					pInterfaceCheckerModel->SetIsMatch(MATCH);
				}
				else
				{
					pInterfaceCheckerModel->SetIsMatch(NOTMATCH);
				}
				
				baPublicInterface = ConvertJson2BsonArray(joPublicInterface);
				baPrivateInterface = ConvertJson2BsonArray(joPrivateInterface);

				pInterfaceCheckerModel->SetODAPublicInterface(baPublicInterface);
				pInterfaceCheckerModel->SetODAPrivateInterface(baPrivateInterface);
			}
			cout << "Total:" << iTotal << endl;
			SaveAllServerInterfaceInfo(strDirtyTable);
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

/*============= LoadCMDBInterfaceInfo ========================
 * Function: LoadCMDBInterfaceInfo
 * Description: Load Interface in CMDB
 * Return: void
 *========================================================================
 */
void CInterfaceCheckerController::LoadCMDBInterfaceInfo(auto_ptr<DBClientCursor> &ptrServerResultCursor)
{
	BSONObj oServerInfo;	
	
	string strCode;
	string strVID;
	string strServerName;
	int iServerType;
	int iServerStatus;

	BSONArray baPubInterface;
	BSONArray baPriInterface;
	

	CInterfaceCheckerModel *pInterfaceCheckerModel;

	Query qCondition = QUERY("deleted" << 0);
	//ptrServerResultCursor = Find(TBL_SERVER, qCondition);

	if (!Find(TBL_SERVER, ptrServerResultCursor, qCondition))
	{
		return;
	}

	try
	{
		if (ptrServerResultCursor->more())
		{
			while(ptrServerResultCursor->more())
			{
				strCode = strVID = strServerName = "";
				baPubInterface = BSONArray();
				baPriInterface = BSONArray();

				oServerInfo = ptrServerResultCursor->nextSafe();
				strCode = oServerInfo.getStringField("code");
				
				if (oServerInfo.hasField("vid"))
					strVID = oServerInfo.getStringField("vid");

				strServerName = oServerInfo.getStringField("server_name");
				iServerType = oServerInfo.getIntField("server_type");
				iServerStatus = oServerInfo.getIntField("status");

				if (!oServerInfo.getObjectField("public_interface").isEmpty())
				{
					baPubInterface = GetInterfaceList(oServerInfo["public_interface"]);
				}
				if (!oServerInfo.getObjectField("private_interface").isEmpty())
				{
					baPriInterface = GetInterfaceList(oServerInfo["private_interface"]);
				}
				
				if (iServerType == SERVER_VIRTUAL)
				{
					if (strVID != "")
					{
						pInterfaceCheckerModel = GetInterfaceCheckerInfoByCode(strVID);
					}
					else
					{
						pInterfaceCheckerModel = GetInterfaceCheckerInfoByCode(strCode);
					}
				}
				else
				{
					pInterfaceCheckerModel = GetInterfaceCheckerInfoByCode(strCode);
				}
				
				pInterfaceCheckerModel->SetCode(strCode);
				pInterfaceCheckerModel->SetVID(strVID);
				pInterfaceCheckerModel->SetCMDBServerName(strServerName);
				pInterfaceCheckerModel->SetCMDBPublicInterface(baPubInterface);
				pInterfaceCheckerModel->SetCMDBPrivateInterface(baPriInterface);
				pInterfaceCheckerModel->SetServerType(iServerType);
				pInterfaceCheckerModel->SetServerStatus(iServerStatus);
			}
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

BSONArray CInterfaceCheckerController::GetInterfaceList(BSONElement beInterface)
{
	BSONArray baResult = BSONArray();
	vector<BSONElement> vtInterface;
	BSONArrayBuilder babInterface;
	
	vtInterface = beInterface.Array();
	
	for(int i = 0; i < vtInterface.size(); i++)
	{
		babInterface << vtInterface[i];
	}
	baResult = babInterface.arr();
	return baResult;
}
vector<BSONObj> CInterfaceCheckerController::GetFilterInterface(vector<BSONObj> vtInterface)
{
	vector<BSONObj> vtResult;
	string strIP = "";
	string strMac = "";

	for(int i = 0; i < vtInterface.size(); i++)
	{
		BSONObj boInterface = vtInterface[i];
		strIP = boInterface.getStringField("ip");
		strMac = boInterface.getStringField("mac_address");

		if ((strIP == INVALID_IP_ADDRESS) || (strMac == INVALID_MAC_ADDRESS))
			continue;

		vtResult.push_back(boInterface);
	}

	return vtResult;
}

/*============= IsMatchInterface ========================
 * Function: IsMatchInterface
 * Description: Check 2 interface is match or not
 * Return: true or false
 *========================================================================
 */
bool CInterfaceCheckerController::IsMatchInterface(BSONArray baCMDBInterface, Json::Value joODAInterface)
{
	bool bResult = true;
	string strCMDBInterface = "";
	int iSumCMDBInterface = 0;
	int iSumODAInterface = 0;

	vector<BSONObj> vtCMDBInterface;
	vector<BSONObj> vtCMDBFilterInterface;

	baCMDBInterface.Vals(vtCMDBInterface);
	vtCMDBFilterInterface = GetFilterInterface(vtCMDBInterface);

	iSumCMDBInterface = vtCMDBFilterInterface.size();
	iSumODAInterface = joODAInterface.size();

	if (iSumCMDBInterface != iSumODAInterface)
		bResult = false;
	else
	{
		if (iSumODAInterface == 0)
			bResult = true;
		else
		{
			for (int i = 0; i < iSumCMDBInterface; i++)
			{
				BSONObj boInterface = vtCMDBFilterInterface[i];	
				if (!IsInterfaceExists(boInterface, joODAInterface))
					bResult = false;
			}
		}
	}
	return bResult;
}


/*============= IsMatchInterface ========================
 * Function: IsInterfaceExists
 * Description: Check interface is exists
 * Return: true or false
 *========================================================================
 */
bool CInterfaceCheckerController::IsInterfaceExists(BSONObj boInterface, Json::Value jarrInterfaceInfo)
{
	bool bResult = false;
	string strIp = "";
	string strMac = "";
	
	string strIpOfElement = "";
	string strMacOfElemnt = "";
	
	try
	{
		strIp = boInterface.getStringField("ip");
		strMac = boInterface.getStringField("mac_address");
		strMac = CUtilities::ToLowerString(strMac);

		for(Json::Value::UInt index = 0 ; index < jarrInterfaceInfo.size(); index ++)
		{
			strIpOfElement = jarrInterfaceInfo[index]["IP"].asString();
			strMacOfElemnt = jarrInterfaceInfo[index]["MAC"].asString();
			strMacOfElemnt = CUtilities::ToLowerString(strMacOfElemnt);

			if (strIpOfElement == strIp && strMacOfElemnt == strMac)
			{
				return true;
			}
		}
	}
	catch(exception& ex)
	{	
		stringstream ssErrorMsg;
		string strLog;
		ssErrorMsg << ex.what() << "][" << __FILE__ << "|" << __LINE__ ;
		strLog = CUtilities::FormatLog(ERROR_MSG, "CInterfaceCheckerController", "IsInterfaceExists","exception:" + ssErrorMsg.str());
		CUtilities::WriteErrorLog(strLog);
	}
	return bResult;
}

/*============= SaveInterfaceCheckerInfo ========================
 * Function: SaveAllServerInterfaceInfo
 * Description: Save Interface info of all server
 * Return: void
 *========================================================================
 */
void CInterfaceCheckerController::SaveAllServerInterfaceInfo(const string& strTableName)
{
	CInterfaceCheckerModel *pInterfaceCheckerModel = NULL;
	int iTotal = 0;
	string strCode;
	
	BSONObj boCondition;
	Remove(strTableName, boCondition);

	try
	{
		Code2InterfaceInfoMap::iterator it = m_mapCode2InterfaceInfoMap.begin();
		while(it != m_mapCode2InterfaceInfoMap.end())
		{
			strCode = (*it).first;
			
			pInterfaceCheckerModel = (*it).second;
			if (pInterfaceCheckerModel->GetCode() != "")
			{
				SaveInterfaceCheckerInfo(strTableName, pInterfaceCheckerModel);
			}
			it++;
			iTotal++;
		}
	}
	catch(exception& ex)
	{	
		stringstream ssErrorMsg;
		string strLog;
		ssErrorMsg << ex.what() << "][" << __FILE__ << "|" << __LINE__ ;
		strLog = CUtilities::FormatLog(ERROR_MSG, "CInterfaceCheckerController", "SaveAllServerInterfaceInfo","exception:" + ssErrorMsg.str());
		CUtilities::WriteErrorLog(strLog);
	}
	cout << "Save total:" << iTotal << endl;
}
/*============= SaveInterfaceCheckerInfo ========================
 * Function: SaveInterfaceCheckerInfo
 * Description: Save Interface checker info
 * Return: void
 *========================================================================
 */
void CInterfaceCheckerController::SaveInterfaceCheckerInfo(const string& strTableName, CInterfaceCheckerModel *pInterfaceCheckerModel)
{
	BSONObj boInterfaceInfo;
	BSONObj boCondition;
	
	string strCode;
	strCode =  pInterfaceCheckerModel->GetCode();

	boInterfaceInfo = pInterfaceCheckerModel->GetInterfaceCheckerInfo();
	boCondition = BSON("code" << strCode);

	Insert(strTableName, boInterfaceInfo, boCondition);
}

BSONArray CInterfaceCheckerController::ConvertJson2BsonArray(Json::Value joValue)
{
	BSONArray baInfo = BSONArray();
	BSONArrayBuilder babResult;

	try
	{
		if (joValue.isArray() && joValue.size() > 0)
		{
			for(Json::Value::UInt index = 0 ; index < joValue.size(); index ++)
			{
				BSONObj boInterface = BSON("ip" << joValue[index]["IP"].asString() << "mac_address" << joValue[index]["MAC"].asString());
				babResult.append(boInterface);
			}
			baInfo = babResult.arr();
		}
	}
	catch(exception& ex)
	{	
		stringstream ssErrorMsg;
		string strLog;
		ssErrorMsg << ex.what() << "][" << __FILE__ << "|" << __LINE__ ;
		strLog = CUtilities::FormatLog(ERROR_MSG, "CInterfaceCheckerController", "ConvertJson2BsonArray","exception:" + ssErrorMsg.str());
		CUtilities::WriteErrorLog(strLog);
	}

	return baInfo;
}