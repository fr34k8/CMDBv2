#include "ConfigReader.h"
#include <sstream>
#include <stdio.h>
#include "../Common/Common.h"
#include "../Utilities/Utilities.h"

using namespace std;
using namespace boost;
using namespace property_tree;
/*
 * Constructor - Assign a file name
 */
CConfigReader::CConfigReader(const std::string& strFileName)
{	
	m_strFileName = strFileName;
	try
    {
		read_ini(m_strFileName, m_pt);
	}
    catch(std::exception& ex)
	{	
		stringstream strErrorMess;
		strErrorMess << ex.what() << " " << __FILE__ << " " << __LINE__ << " | at : " <<  CUtilities::GetCurrTime() << endl;
		CUtilities::WriteErrorLog(ERROR_MSG, strErrorMess.str());
	}
}

/*
 * Destructor -
 */
CConfigReader::~CConfigReader()
{
	m_pt.clear();
}

/*
 * update - Writes the updated configuration file.
 */
void CConfigReader::Update(const std::string& strGroup, const std::string& strProperty, const std::string& strValue)
{
	string strQuery = strGroup + "." + strProperty;
	try{
		m_pt.put(strQuery, strValue);
		write_ini( m_strFileName, m_pt );
	}
	catch(std::exception& ex)
	{	
		stringstream strErrorMess;
		strErrorMess << ex.what() << " " << __FILE__ << " " << __LINE__ << " | at : " <<  CUtilities::GetCurrTime() << endl;
		CUtilities::WriteErrorLog(ERROR_MSG, strErrorMess.str());
	}
}

/*
 * add - Add info into configuration file.
 */
void CConfigReader::Add(const std::string& strGroup, const std::string& strProperty, const std::string& strValue)
{
   string strQuery = strGroup + "." + strProperty;
   try{
	   m_pt.add(strQuery, strValue);
	   write_ini( m_strFileName, m_pt );
   }
    catch(std::exception& ex)
	{	
		stringstream strErrorMess;
		strErrorMess << ex.what() << " " << __FILE__ << " " << __LINE__ << " | at : " <<  CUtilities::GetCurrTime() << endl;
		CUtilities::WriteErrorLog(ERROR_MSG, strErrorMess.str());
	}
}

/*
 * load - Load value from configuration file.
 */
std::string CConfigReader::ReadStringValue(const std::string& strGroup, const std::string& strProperty)
{  
	string strQuery = strGroup + "." + strProperty;	
	string strRes = "";
	try 
	{
		strRes =  m_pt.get<std::string>(strQuery);
	}
    catch(std::exception& ex)
	{	
		stringstream ssErrorMsg;
		string strLog;
		ssErrorMsg << ex.what() << "][" << __FILE__ << "|" << __LINE__ ;
		strLog = CUtilities::FormatLog(ERROR_MSG, "CConfigReader", "ReadStringValue","exception:" + ssErrorMsg.str());
		CUtilities::WriteErrorLog(strLog);
	}

	return strRes;
}

bool CConfigReader::ReadBoolValue(const string& strGroupName, const string& strProperty)
{
	string strValue = ReadStringValue(strGroupName, strProperty);
	
	if (strValue == "true")
	{		
		return true;
	}
	else
	{	
		return false;
	}

	return true;
}

int CConfigReader::ReadIntValue(const string& strGroupName, const string& strProperty)
{
	string strValue = ReadStringValue(strGroupName, strProperty);
	return atoi(strValue.c_str());
}