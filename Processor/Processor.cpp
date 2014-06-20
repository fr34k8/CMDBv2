#include "Processor.h"
#include "../Common/DBCommon.h"
#include "../Config/ConfigFile.h"
#include "../Controller/MongodbController.h"
#include "../Controller/MySQLController.h"

CProcessor::CProcessor(const string& strFileName)
{
	CConfigFile::GetInstance(strFileName);
}

CProcessor::~CProcessor(void)
{
	/*if (NULL != m_pConfigFile)
	{
		delete m_pConfigFile;
	}*/
	CConfigFile::DestroyInstance();

	mapDBGroup2ControllerArray::iterator mit;
	for (mit = m_mapDBGroup2ControllerArray.begin(); mit != m_mapDBGroup2ControllerArray.end(); mit++) {
		m_mapDBGroup2ControllerArray[mit->first].clear();
	}
	m_mapDBGroup2ControllerArray.clear();
	cout << "Finished Destruction CProcessor(void)" << endl;
}

void CProcessor::RegisterController(CMongodbController* pController, string strDBGroup)
{
	Controller uController;
	if (NULL != pController)
	{
		if ("" == strDBGroup)
		{
			strDBGroup = DB_GROUP_MONGODB_DEFAULT;
		}

		cout << typeid(*pController).name() << " registers for group " << strDBGroup << endl;
		uController.pMongodbController = pController;
		m_mapDBGroup2ControllerArray[strDBGroup].push_back(uController);
	}
}

void CProcessor::RegisterController(CMySQLController* pController, string strDBGroup)
{
	Controller uController;
	if (NULL != pController)
	{
		if ("" == strDBGroup)
		{
			strDBGroup = DB_GROUP_MYSQL_DEFAULT;
		}

		cout << typeid(*pController).name() << " registers for group " << strDBGroup << endl;
		uController.pMySQLController = pController;
		m_mapDBGroup2ControllerArray[strDBGroup].push_back(uController);
	}
}

/* Author: DuyLH */
bool CProcessor::Connect()
{
	bool bTemp = false;
	bool bResult = true;
	string strDBGroup;
	ControllerArray vController;
	//====================================CMDB Connection==================================
	mapDBGroup2ControllerArray::iterator mit;
	for (mit = m_mapDBGroup2ControllerArray.begin(); mit != m_mapDBGroup2ControllerArray.end(); mit++) {

		// Repeat if you also want to iterate through the second map.
		strDBGroup = mit->first;
		vController = mit->second;

		CConfigFile::GetInstance()->SetActiveDBGroup(strDBGroup);
		ConnectInfo CInfo = CDBUtilities::GetConnectInfo();

		cout << "Trying connect controllers to group [" << strDBGroup << "] ..." << endl;
		ControllerArray::iterator it;
		cout << "[Num of registered controllers] " << vController.size() << endl;
		//cout << "[DBHost] "		<< CInfo.strHost << endl;
		//cout << "[DBType] "		<< CInfo.strDBType << endl;
		//cout << "[DBSource] "		<< CInfo.strSource << endl;
		//cout << "[DBName] "		<< CInfo.strDBName << endl;
		//cout << "[DBUser] "		<< CInfo.strUser << endl;
		//cout << "[DBPass] "		<< CInfo.strPass << endl;
		//cout << "[DBReference] "  << CInfo.strReadReferenceOption << endl;

		for (int i = 0; i<DB_RECONNECT_TIME; i++)
		{
			it = vController.begin();

			// Connect all controllers to database
			while (it != vController.end())
			{
				Controller uController = *it;
				//pController = *it;

				if (CInfo.strDBType == DBTYPE_MONGODB)
				{
					bTemp = (uController.pMongodbController)->Connect(CInfo);
				}
				else if (CInfo.strDBType == DBTYPE_MYSQL)
				{
					bTemp = (uController.pMySQLController)->Connect(CInfo);
				}
				else
				{
					cout << "DBType config not found..." << endl;
					return false;
				}
				if (!bTemp)
				{
					CUtilities::WriteErrorLog(ERROR_MSG, CUtilities::FormatLog(ERROR_MSG, "CProcessor", "Connect()", "Connection Fail"));
					sleep(DB_CONNECT_RETRY_INTERVAL);

					// Mark as false if one controller could not connect to database
					bResult = false;
					break;
				}
				else
				{
					bResult = true;
				}
				it++;
			}
			// All controllers were connnected to database
			if (bResult)
			{
				cout << "[" << strDBGroup << "] All controllers were connected successfully" << endl;
				break;

			}
			else
			{
				cout << "[" << strDBGroup << "] One of controllers could not connect to DB. Retrying ... " << endl;
				continue;
			}
		}

	}

	return bResult;
}
