#include "MySQLController.h"
#include <string.h>
#include "../Common/DBCommon.h"

ConnectInfo g_CInfo;
CMySQLController::CMySQLController()
{
	my_bool reconnect = 0;
	mysql_options(&m_Connection, MYSQL_OPT_RECONNECT, &reconnect);
	m_strTableName = "";
	m_pResult = NULL;
}

CMySQLController::CMySQLController(ConnectInfo CInfo)
{
	m_pResult = NULL;

	bool bRes = false;
	try
	{
		bRes = Connect(CInfo);
		if (!bRes)
		{
			sleep(10);
			bRes = Connect(CInfo);
		}
	}
	catch (exception& ex)
	{
		string strLog;
		stringstream strErrorMess;
		strErrorMess << ex.what() << "][" << __FILE__ << "|" << __LINE__;
		strLog = CUtilities::FormatLog(ERROR_MSG, "CMySQLController", "Find", "exception:" + strErrorMess.str());
		CUtilities::WriteErrorLog(ERROR_MSG, strLog);
	}
}

CMySQLController::~CMySQLController()
{
	if (m_pResult != NULL)
	{
		mysql_free_result(m_pResult);
		m_pResult = NULL;
	}
	mysql_close(&m_Connection);
}

bool CMySQLController::Connect(ConnectInfo CInfo)
{
	g_CInfo = CInfo;
	mysql_init(&m_Connection);

	if (!mysql_real_connect(&m_Connection, CInfo.strHost.c_str(), CInfo.strUser.c_str(), CInfo.strPass.c_str(), CInfo.strSource.c_str(), 0, NULL, CLIENT_MULTI_STATEMENTS))
	{
		string strFormatLog;
		stringstream strErrorMess;

		fprintf(stderr, "Failed to connect to database: Error: %s\n", mysql_error(&m_Connection));
		strErrorMess << mysql_error(&m_Connection);

		strFormatLog = CUtilities::FormatLog(ERROR_MSG, "MySQLController", "Connect", strErrorMess.str());
		CUtilities::WriteErrorLog(strFormatLog);

		return false;
	}
	return true;
}

bool CMySQLController::Connect()
{
	mysql_init(&m_Connection);

	if (!mysql_real_connect(&m_Connection, g_CInfo.strHost.c_str(), g_CInfo.strUser.c_str(), g_CInfo.strPass.c_str(), g_CInfo.strSource.c_str(), 0, NULL, CLIENT_MULTI_STATEMENTS))
	{
		string strFormatLog;
		stringstream strErrorMess;

		fprintf(stderr, "Failed to connect to database: Error: %s\n", mysql_error(&m_Connection));
		strErrorMess << mysql_error(&m_Connection);

		strFormatLog = CUtilities::FormatLog(ERROR_MSG, "MySQLController", "Connect", strErrorMess.str());
		CUtilities::WriteErrorLog(ERROR_MSG, strFormatLog);

		return false;
	}
	return true;
}

void CMySQLController::SetQuery(string strQuery)
{
	m_strQuery = strQuery.c_str();
}

bool CMySQLController::Query()
{
	try{
		int state = mysql_real_query(&m_Connection, m_strQuery, (unsigned int)strlen(m_strQuery));
		if (state != 0)
		{
			return false;
		}
		return true;
	}
	catch (exception& ex)
	{
		string strLog;
		stringstream strErrorMess;
		strErrorMess << ex.what() << "][" << __FILE__ << "|" << __LINE__;
		strLog = CUtilities::FormatLog(ERROR_MSG, "CMySQLController", "Find", "exception:" + strErrorMess.str());
		CUtilities::WriteErrorLog(ERROR_MSG, strLog);
		return false;
	}
}

int CMySQLController::SelectQuery()
{
	try{
		int state = mysql_query(&m_Connection, m_strQuery);
		if (state != 0)
		{
			printf(mysql_error(&m_Connection));
			return state;
		}
		m_pResult = mysql_store_result(&m_Connection);
		m_iNumFields = mysql_num_fields(m_pResult);
		m_pFields = mysql_fetch_fields(m_pResult);

		return state;
	}
	catch (exception& ex)
	{
		string strLog;
		stringstream strErrorMess;
		strErrorMess << ex.what() << "][" << __FILE__ << "|" << __LINE__;
		strLog = CUtilities::FormatLog(ERROR_MSG, "CMySQLController", "Find", "exception:" + strErrorMess.str());
		CUtilities::WriteErrorLog(ERROR_MSG, strLog);
		return 0;
	}
}

bool CMySQLController::SelectQuery(const char* strQuery)
{
	try{
		int state = mysql_query(&m_Connection, strQuery);
		if (state != 0)
		{
			printf(mysql_error(&m_Connection));
			return false;
		}
		m_pResult = mysql_store_result(&m_Connection);
		return true;
	}
	catch (exception& ex)
	{
		string strLog;
		stringstream strErrorMess;
		strErrorMess << ex.what() << "][" << __FILE__ << "|" << __LINE__;
		strLog = CUtilities::FormatLog(ERROR_MSG, "CMySQLController", "Find", "exception:" + strErrorMess.str());
		CUtilities::WriteErrorLog(ERROR_MSG, strLog);
		return false;
	}
}


int CMySQLController::GetColByFieldName(string strFieldName)
{
	for (int i = 0; i < m_iNumFields; i++)
	{
		if (strFieldName.compare(m_pFields[i].name) == 0)
		{
			return i;
		}
	}
	return -1;
}

bool CMySQLController::Query(const char* strQuery)
{
	try{
		int state = mysql_real_query(&m_Connection, strQuery, (unsigned int)strlen(strQuery));
		if (state != 0)
		{
			return false;
		}
		return true;
	}
	catch (exception& ex)
	{
		string strLog;
		stringstream strErrorMess;
		strErrorMess << ex.what() << "][" << __FILE__ << "|" << __LINE__;
		strLog = CUtilities::FormatLog(ERROR_MSG, "CMySQLController", "Find", "exception:" + strErrorMess.str());
		CUtilities::WriteErrorLog(ERROR_MSG, strLog);
		return false;
	}
}

int CMySQLController::AffectedRows(){
	return mysql_affected_rows(&m_Connection);
}

void CMySQLController::PrintResult()
{
	MYSQL_ROW row;
	unsigned int i = 0;
	while ((row = mysql_fetch_row(m_pResult)) != NULL){
		printf("%s\n", row[i] != NULL ?
			row[i] : "NULL");
	}
}

bool CMySQLController::NextRow()
{
	m_oRow = mysql_fetch_row(m_pResult);
	if (m_oRow == false || m_oRow == NULL)
	{
		mysql_free_result(m_pResult);
		return false;
	}
	return true;
}

string CMySQLController::FetchString(string strFieldName)
{
	int iCol = GetColByFieldName(strFieldName);
	string strValue = "";

	if (m_oRow[iCol] != NULL)
		strValue = m_oRow[iCol];

	return strValue;
}

int CMySQLController::FetchInt(string strFieldName)
{
	int iCol = GetColByFieldName(strFieldName);
	if (m_oRow[iCol] != NULL)
		return atoi(m_oRow[iCol]);
	return -1;
}

long long CMySQLController::FetchLong(string strFieldName)
{
	MYSQL_FIELD *field;
	int iCol = GetColByFieldName(strFieldName);
	if (m_oRow[iCol] != NULL)
		return atol(m_oRow[iCol]);
	return NULL;
}

long long CMySQLController::ModelGetLong(string strFieldName)
{
	MYSQL_ROW row;
	MYSQL_FIELD *field;
	for (int i = 0; i < m_pResult->row_count; i++)
	{
		try{
			row = mysql_fetch_row(m_pResult);
			// In tat ca cac colume:
			for (int col = 0; col < mysql_num_fields(m_pResult); col++)
			{
				field = mysql_fetch_field(m_pResult);
				if (strFieldName.compare(field->name) == 0)
				{
					return atol(row[col]);
				}
			}
		}
		catch (exception& ex)
		{
			string strLog;
			stringstream strErrorMess;
			strErrorMess << ex.what() << "][" << __FILE__ << "|" << __LINE__;
			strLog = CUtilities::FormatLog(ERROR_MSG, "CMySQLController", "Find", "exception:" + strErrorMess.str());
			CUtilities::WriteErrorLog(ERROR_MSG, strLog);
		}
	}
}

int CMySQLController::ModelGetInt(string strFieldName)
{
	MYSQL_ROW row;
	MYSQL_FIELD *field;
	for (int i = 0; i < m_pResult->row_count; i++)
	{
		try{
			row = mysql_fetch_row(m_pResult);
			// In tat ca cac colume:
			for (int col = 0; col < mysql_num_fields(m_pResult); col++)
			{
				field = mysql_fetch_field(m_pResult);
				if (strFieldName.compare(field->name) == 0)
				{
					return atoi(row[col]);
				}
			}
		}
		catch (exception& ex)
		{
			string strLog;
			stringstream strErrorMess;
			strErrorMess << ex.what() << "][" << __FILE__ << "|" << __LINE__;
			strLog = CUtilities::FormatLog(ERROR_MSG, "CMySQLController", "Find", "exception:" + strErrorMess.str());
			CUtilities::WriteErrorLog(ERROR_MSG, strLog);
		}
	}
}

char* CMySQLController::ModelGetString(string strFieldName)
{
	MYSQL_ROW row;
	MYSQL_FIELD *field;
	for (int i = 0; i < m_pResult->row_count; i++)
	{
		try{
			row = mysql_fetch_row(m_pResult);

			for (int col = 0; col < mysql_num_fields(m_pResult); col++)
			{
				field = mysql_fetch_field(m_pResult);
				if (strFieldName.compare(field->name) == 0)
				{
					return row[col];
				}
			}
		}
		catch (exception& ex)
		{
			string strLog;
			stringstream strErrorMess;
			strErrorMess << ex.what() << "][" << __FILE__ << "|" << __LINE__;
			strLog = CUtilities::FormatLog(ERROR_MSG, "CMySQLController", "Find", "exception:" + strErrorMess.str());
			CUtilities::WriteErrorLog(ERROR_MSG, strLog);
		}
	}
}

void CMySQLController::ResetConnect()
{
	mysql_close(&m_Connection);
	while (!Connect())
		sleep(5);
}

bool CMySQLController::Close()
{
	mysql_close(&m_Connection);
}

bool CMySQLController::Reconnect()
{
	mysql_close(&m_Connection);

	mysql_init(&m_Connection);
	if (!mysql_real_connect(&m_Connection, g_CInfo.strHost.c_str(), g_CInfo.strUser.c_str(), g_CInfo.strPass.c_str(), g_CInfo.strSource.c_str(), 0, NULL, CLIENT_MULTI_STATEMENTS))
	{
		CUtilities::WriteErrorLog(ERROR_MSG, mysql_error(&m_Connection));
		return false;
	}
	return true;
}
