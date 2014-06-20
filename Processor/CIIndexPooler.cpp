#include "CIIndexPooler.h"
#include "../Model/CIInfoIndexModel.h"
#include "../Model/CIIndexPoolerModel.h"
#include "../Controller/CIInfoIndexController.h"
#include "../Controller/CIInfoChangeController.h"
#include "../Config/ConfigFile.h"
#include "../Common/DBCommon.h"

CCIIndexPooler::CCIIndexPooler(const string& strCfgFile)
{
	//CConfigFile::GetInstance(strCfgFile);
	m_pConfigFile = new CConfigFile(strCfgFile);
}

CCIIndexPooler::~CCIIndexPooler(void)
{
	if (m_pCIInfoIndexController != NULL)
	{
		delete m_pCIInfoIndexController;
		m_pCIInfoIndexController = NULL;
	}
	if (m_pConfigFile != NULL)
	{
		delete m_pConfigFile;
		m_pConfigFile = NULL;
	}

	//CConfigFile::DestroyInstance();
}


bool CCIIndexPooler::Connect()
{
	bool bResult = true;
	//====================================CMDB Connection==================================
	m_pConfigFile->SetActiveDBGroup(MONGODB_CMDB_GROUP);
	ConnectInfo CInfo = CDBUtilities::GetConnectInfo();

	//================Connect DB=================
	if(!m_pCIInfoIndexController->Connect(CInfo))
	{
		CUtilities::WriteErrorLog(ERROR_MSG, CUtilities::FormatLog(ERROR_MSG, "CCIIndexPooler", "Connect()", "Connection Fail"));
		bResult = false;
	}

	return bResult;
}

void CCIIndexPooler::ProceedInfo(CCIIndexPoolerModel* pCIIndexPoolerModel)
{
	if (!Connect())
	{
		return;
	}
	
	for (int i = 0; i < pCIIndexPoolerModel->GetLength(); i++)	
	{
		CCIInfoIndexModel* pCIInfoIndexModel = (*pCIIndexPoolerModel)[i];
		// Proceed indexing for CI information
		if (ProceedIndex(pCIInfoIndexModel))
		{
			// Delete CI information in CI change info table
			if (!DeleteInfo(pCIInfoIndexModel))
			{
				break; // Proceed index for this information next time
			}
		}		
	}	
}

bool CCIIndexPooler::IsIndexExisted(CCIInfoIndexModel* pCIInfoIndexModel, string strValue)
{
	return m_pCIInfoIndexController->IsExisted(pCIInfoIndexModel->IsExistedIndexQuery(strValue));
}

bool CCIIndexPooler::AddIndex(CCIInfoIndexModel* pCIInfoIndexModel)
{
	Query queryIndex;
	BSONObj boIndexRecord;
	string strNewValue, strObjID, strField;
	strNewValue = pCIInfoIndexModel->GetNewValue();
	strObjID = pCIInfoIndexModel->GetCIID();
	strField = pCIInfoIndexModel->GetFieldName();

	if(IsIndexExisted(pCIInfoIndexModel, strNewValue))
		return true;
	queryIndex = pCIInfoIndexModel->GetAddIndexQuery();
	boIndexRecord = pCIInfoIndexModel->GetAddIndexRecord();
	if(!m_pCIInfoIndexController->Upsert(boIndexRecord,queryIndex))
	{
		CUtilities::WriteInfoLog(INFO_MSG, CUtilities::FormatLog(INFO_MSG, "CCIIndexPooler", "CreateIndex(CCIInfoIndexModel*)", "ADD|FAIL|OID:" + strObjID + "FIELD:" + strField));
		return false;
	}
}

bool CCIIndexPooler::DeleteIndex(CCIInfoIndexModel* pCIInfoIndexModel)
{
	Query queryIndex;
	BSONObj boIndexRecord;
	vector<BSONElement> vbeInfoArray;
	auto_ptr<DBClientCursor> ptrIndexCursor = auto_ptr<DBClientCursor>();
	string strObjID, strField;
	strObjID = pCIInfoIndexModel->GetCIID();
	strField = pCIInfoIndexModel->GetFieldName();
	
	queryIndex = pCIInfoIndexModel->GetDeleteIndexQuery();
	boIndexRecord = pCIInfoIndexModel->GetDeleteIndexRecord();
	if(m_pCIInfoIndexController->Update(boIndexRecord,queryIndex))
	{
		/*
			Remove an index record that "info" array is empty
		*/
		ptrIndexCursor = m_pCIInfoIndexController->Find(queryIndex);
		if ((ptrIndexCursor.get() != NULL) && (ptrIndexCursor->more()))
		{
			boIndexRecord = ptrIndexCursor->nextSafe();
			vbeInfoArray = boIndexRecord["info"].Array();
			if(vbeInfoArray.size() == 0){
				m_pCIInfoIndexController->Remove(queryIndex);
			}
		}
		return true;
	}
	else
	{
		CUtilities::WriteInfoLog(INFO_MSG, CUtilities::FormatLog(INFO_MSG, "CCIIndexPooler", "CreateIndex(CCIInfoIndexModel*)", "DEL|FAIL|OID:" + strObjID + "FIELD:" + strField));
		return false;
	}
}
bool CCIIndexPooler::UpdateIndex(CCIInfoIndexModel* pCIInfoIndexModel)
{
	Query queryIndex;
	BSONObj boIndexRecord;
	vector<BSONElement> vbeInfoArray;
	auto_ptr<DBClientCursor> ptrIndexCursor = auto_ptr<DBClientCursor>();
	string strOldValue, strNewValue, strObjID, strField;
	strOldValue = pCIInfoIndexModel->GetOldValue();
	strNewValue = pCIInfoIndexModel->GetNewValue();
	strObjID = pCIInfoIndexModel->GetCIID();
	strField = pCIInfoIndexModel->GetFieldName();
	bool bResult;
	bResult = true;
	if (IsIndexExisted(pCIInfoIndexModel, strOldValue))
	{
		queryIndex = pCIInfoIndexModel->GetDeleteIndexQuery();
		boIndexRecord = pCIInfoIndexModel->GetDeleteIndexRecord();
		if (m_pCIInfoIndexController->Update(boIndexRecord, queryIndex))
		{
			/*
			Remove an index record that "info" array is empty
			*/
			ptrIndexCursor = m_pCIInfoIndexController->Find(queryIndex);
			if ((ptrIndexCursor.get() == NULL) && (ptrIndexCursor->more()))
			{
				boIndexRecord = ptrIndexCursor->nextSafe();
				vbeInfoArray = boIndexRecord["info"].Array();
				if (vbeInfoArray.size() == 0){
					m_pCIInfoIndexController->Remove(queryIndex);
				}
			}
		}
		else
		{
			CUtilities::WriteInfoLog(INFO_MSG, CUtilities::FormatLog(INFO_MSG, "CCIIndexPooler", "CreateIndex(CCIInfoIndexModel*)", "UPDEL|FAIL|OID:" + strObjID + "FIELD:" + strField));
			bResult = false;
		}
	}
	//====================================================
	/*
	Add an index record with new key
	*/
	if (!IsIndexExisted(pCIInfoIndexModel, strNewValue))
	{
		queryIndex = pCIInfoIndexModel->GetAddIndexQuery();
		boIndexRecord = pCIInfoIndexModel->GetAddIndexRecord();
		if (!m_pCIInfoIndexController->Upsert(boIndexRecord, queryIndex))
		{
			CUtilities::WriteInfoLog(INFO_MSG, CUtilities::FormatLog(INFO_MSG, "CCIIndexPooler", "CreateIndex(CCIInfoIndexModel*)", "UPADD|FAIL|OID:" + strObjID + "FIELD:" + strField));
			bResult = false;
		}
	}
	return bResult;
}

bool CCIIndexPooler::ProceedIndex(CCIInfoIndexModel* pCIInfoIndexModel)
{
	bool bResult = false;
	string strNewValue, strOldValue;

	if (NULL == pCIInfoIndexModel)
	{
		return bResult;
	}

	strNewValue = pCIInfoIndexModel->GetNewValue();
	strOldValue = pCIInfoIndexModel->GetOldValue();	
	
	if (strOldValue.empty())
	{
		// Add index for new text
		if (!strNewValue.empty())
		{
			bResult = AddIndex(pCIInfoIndexModel);
		}
	}
	else
	{
		// Text has been deleted
		if (strNewValue.empty())
		{
			bResult = DeleteIndex(pCIInfoIndexModel);
		}
		else // Text changed from old value to new value
		{
			bResult = UpdateIndex(pCIInfoIndexModel);
		}
	}
	return bResult;
}

bool CCIIndexPooler::DeleteInfo(CCIInfoIndexModel* pCIInfoIndexModel)
{
	string strObjID = pCIInfoIndexModel->GetObjectID();
	Query queryRemoveCondition = Query(BSON("_id"<<OID(strObjID)));	
	if(!m_pCIInfoIndexController->RemoveInfoChange(queryRemoveCondition))
	{
		CUtilities::WriteInfoLog(INFO_MSG, CUtilities::FormatLog(INFO_MSG, "CCIIndexPooler", "DeleteInfo(CCIInfoIndexModel*)", "REMOVE|FAIL|OID:" + strObjID));
		return false;
	}
	return true;
}
