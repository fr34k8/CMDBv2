#include "CollectorController.h"
#include "../Model/CollectorModel.h"
#include "../Common/DBCommon.h"

CCollectorController::CCollectorController(void)
{
	m_strTableName = TBL_COLLECTOR_INFO;
}

CCollectorController::~CCollectorController(void)
{
	CollectorName2CollectorInfoMap::iterator it = m_mapCollectorName2CollectorInfo.begin();
	while (it != m_mapCollectorName2CollectorInfo.end())
	{
		delete (*it).second;
		it++;
	}

	m_mapCollectorName2CollectorInfo.clear();
}



CCollectorModel* CCollectorController::GetCollectorInfoByCollectorName(const string& strCollectorName)
{
	CCollectorModel* pCollectorInfo = NULL;
	CollectorName2CollectorInfoMap::iterator it = m_mapCollectorName2CollectorInfo.find(strCollectorName);
	
	if (it != m_mapCollectorName2CollectorInfo.end())
	{
		pCollectorInfo = (*it).second;
	}
	else
	{
		pCollectorInfo = new CCollectorModel();		
		m_mapCollectorName2CollectorInfo[strCollectorName] = pCollectorInfo;
	}

	return pCollectorInfo;
}

bool CCollectorController::LoadCollectorInfo(const string& strCollectorName)
{
	bool bResult = false;	
	string strTableName;
	string strDirtyTableName;
	string strLibraryName;
	string strAPIName;
	string strTypeName;
	string strSource;

	try
	{
		// Load data from database by name
		Query queryCondition = QUERY("collector_name"<<strCollectorName);
		auto_ptr<DBClientCursor> ptrResultCursor = Find(queryCondition);

		if (ptrResultCursor.get() == NULL)
		{
			return false;
		}

		if (ptrResultCursor->more())
		{
			bResult = true;
			while (ptrResultCursor->more()) {
				BSONObj oCollectorInfo = ptrResultCursor->nextSafe();
				// Get partner info
				CCollectorModel* pCollectorInfo = GetCollectorInfoByCollectorName(strCollectorName);
				
				// Register API to table for getting collector info
				strTableName = oCollectorInfo.getStringField("table_name");
				strDirtyTableName = oCollectorInfo.getStringField("dirty_table_name");
				strAPIName = oCollectorInfo.getStringField("api_name");
				strLibraryName = oCollectorInfo.getStringField("library_name");
				strTypeName = oCollectorInfo.getStringField("type");
				strSource = oCollectorInfo.getStringField("source");
				
				pCollectorInfo->SetCollectorName(strCollectorName);
				pCollectorInfo->SetLibraryName(strLibraryName);
				pCollectorInfo->SetAPIName(strAPIName);
				pCollectorInfo->SetDirtyTableName(strDirtyTableName);
				pCollectorInfo->SetTableName(strTableName);
				pCollectorInfo->SetType(strTypeName);
				pCollectorInfo->SetSource(strSource);
			}
			ptrResultCursor.reset();
		}
	}
	catch(exception& ex)
	{	
		stringstream ssErrorMsg;
		string strLog;
		ssErrorMsg << ex.what() << "][" << __FILE__ << "|" << __LINE__ ;
		strLog = CUtilities::FormatLog(ERROR_MSG, "CCollectorController", "LoadCollectorInfo","exception:" + ssErrorMsg.str());
		CUtilities::WriteErrorLog(ERROR_MSG, strLog);
	}
	return bResult;
}

bool CCollectorController::IsCollectorNameExists(const string& strCollectorName)
{
	CollectorName2CollectorInfoMap::iterator it = m_mapCollectorName2CollectorInfo.find(strCollectorName);
	if (it != m_mapCollectorName2CollectorInfo.end())
	{
		return true;
	}
	else
	{
		return false;
	}
}

string CCollectorController::GetCollectorType(const string& strCollectorName)
{
	string strTypeResult;
	CCollectorModel* pCollectorInfo = NULL;


	if (IsCollectorNameExists(strCollectorName))
	{
		pCollectorInfo = m_mapCollectorName2CollectorInfo[strCollectorName];
		strTypeResult = pCollectorInfo->GetType();
	}
	
	return strTypeResult;
}