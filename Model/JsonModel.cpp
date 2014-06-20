#include "JsonModel.h"

CJsonModel::CJsonModel()
{
}

CJsonModel::~CJsonModel()
{
	DestroyData();
}

bool CJsonModel::AppendJson(string strJsonValue)
{
	bool bParsedSuccess;
	Json::Reader objReader;
	Json::Value valApp;
	unsigned int uiRoot;
	stringstream ssErrorMsg;
	string strLog;

	try{
		bParsedSuccess = objReader.parse(strJsonValue, valApp, false);
	}
	catch(exception& ex)
	{	
		ssErrorMsg << ex.what() << "][" << __FILE__ << "|" << __LINE__ ;
		strLog = CUtilities::FormatLog(ERROR_MSG, "CJsonModel", "AppendArray","exception:" + ssErrorMsg.str());
		CUtilities::WriteErrorLog(ERROR_MSG, strLog);
	}
	if(!bParsedSuccess){
		return false;
	}
	try{
		uiRoot = JSON_ROOT;
		m_valRoot[m_valRoot.size()] = valApp;
		m_valRoot = m_valRoot[uiRoot];
	}
	catch(exception& ex)
	{	
		ssErrorMsg << ex.what() << "][" << __FILE__ << "|" << __LINE__ ;
		strLog = CUtilities::FormatLog(ERROR_MSG, "CJsonModel", "AppendArray","exception:" + ssErrorMsg.str());
		CUtilities::WriteErrorLog(ERROR_MSG, strLog);
	}
	return true;
}

void CJsonModel::AppendValue(string strFieldNamme, string strJsonValue)
{
	m_valRoot[strFieldNamme] = strJsonValue;
}

void CJsonModel::AppendValue(string strFieldNamme, int iJsonValue)
{
	m_valRoot[strFieldNamme] = iJsonValue;
}

string CJsonModel::GetString(string strFieldNamme)
{
	return m_valRoot[strFieldNamme].asString();
}

int CJsonModel::GetInt(string strFieldNamme)
{
	return atoi(m_valRoot[strFieldNamme].asString().c_str());
}

long long CJsonModel::GetLong(string strFieldNamme)
{
	return atol(m_valRoot[strFieldNamme].asString().c_str());
}

string CJsonModel::toString()
{
	string strRes = "[]";
	try{
		if(!m_valRoot.empty()){
			strRes = m_valRoot.toStyledString();
		}
	}
	catch(exception& ex)
	{	
		stringstream ssErrorMsg;
		string strLog;
		ssErrorMsg << ex.what() << "][" << __FILE__ << "|" << __LINE__ ;
		strLog = CUtilities::FormatLog(ERROR_MSG, "CJsonModel", "toString","exception:" + ssErrorMsg.str());
		CUtilities::WriteErrorLog(ERROR_MSG, strLog);
	}
	
	return strRes;
}

Json::Value CJsonModel::parseValueRootJson(string strJsonValue)
{
	bool bParsedSuccess;
	Json::Reader objReader;
	Json::Value valApp;
	
	try{
		bParsedSuccess = objReader.parse(strJsonValue, valApp, false);
	}
	catch(exception& ex)
	{	
		stringstream ssErrorMsg;
		string strLog;
		ssErrorMsg << ex.what() << "][" << __FILE__ << "|" << __LINE__ ;
		strLog = CUtilities::FormatLog(ERROR_MSG, "CJsonModel", "parseValueRootJson","exception:" + ssErrorMsg.str());
		CUtilities::WriteErrorLog(ERROR_MSG, strLog);
	}
	return valApp;
}

string CJsonModel::toStringIndex(unsigned int iIndex){
	return m_valRoot[iIndex].toStyledString();
}
string CJsonModel::toStringKey(string strKey){
	return m_valRoot[strKey].toStyledString();
}

bool CJsonModel::GoToIndex(unsigned int iIndex)
{
	bool bResult = true;
	try{
		if(m_valRoot[iIndex].empty())
			return false;
		m_valRoot = m_valRoot[iIndex];
	}
	catch(exception& ex)
	{	
		stringstream ssErrorMsg;
		string strLog;
		ssErrorMsg << ex.what() << "][" << __FILE__ << "|" << __LINE__ ;
		strLog = CUtilities::FormatLog(ERROR_MSG, "CJsonModel", "GoToIndex","exception:" + ssErrorMsg.str());
		CUtilities::WriteErrorLog(ERROR_MSG, strLog);
	}
	return bResult;
}

bool CJsonModel::GoToKey(string strKey)
{
	bool bResult = true;
	try{
		if(m_valRoot[strKey].empty())
			return false;
		m_valRoot = m_valRoot[strKey];
	}
	catch(exception& ex)
	{	
		stringstream ssErrorMsg;
		string strLog;
		ssErrorMsg << ex.what() << "][" << __FILE__ << "|" << __LINE__ ;
		strLog = CUtilities::FormatLog(ERROR_MSG, "CJsonModel", "GoToKey","exception:" + ssErrorMsg.str());
		CUtilities::WriteErrorLog(ERROR_MSG, strLog);
	}
	return bResult;
}


string CJsonModel::toString(unsigned int iIndex, string strKey)
{
	try{
		return m_valRoot[iIndex][strKey].toStyledString();
	}
	catch(exception& ex)
	{	
		stringstream ssErrorMsg;
		string strLog;
		ssErrorMsg << ex.what() << "][" << __FILE__ << "|" << __LINE__ ;
		strLog = CUtilities::FormatLog(ERROR_MSG, "CJsonModel", "toString","exception:" + ssErrorMsg.str());
		CUtilities::WriteErrorLog(ERROR_MSG, strLog);
	}
	return "";
}

string CJsonModel::toString(string strKey, unsigned int iIndex)
{
	try{
		return m_valRoot[strKey][iIndex].toStyledString();
	}
	catch(exception& ex)
	{	
		stringstream ssErrorMsg;
		string strLog;
		ssErrorMsg << ex.what() << "][" << __FILE__ << "|" << __LINE__ ;
		strLog = CUtilities::FormatLog(ERROR_MSG, "CJsonModel", "toString","exception:" + ssErrorMsg.str());
		CUtilities::WriteErrorLog(ERROR_MSG, strLog);
	}
	return "";
}

int CJsonModel::GetSize()
{
	try{
		return m_valRoot.size();
	}
	catch(exception& ex)
	{	
		stringstream ssErrorMsg;
		string strLog;
		ssErrorMsg << ex.what() << "][" << __FILE__ << "|" << __LINE__ ;
		strLog = CUtilities::FormatLog(ERROR_MSG, "CJsonModel", "GetSize","exception:" + ssErrorMsg.str());
		CUtilities::WriteErrorLog(ERROR_MSG, strLog);
	}
	return 0;
}
	
void CJsonModel::DestroyData()
{	
	if(!m_valRoot.empty())
	{
		m_valRoot.clear();
	}
}