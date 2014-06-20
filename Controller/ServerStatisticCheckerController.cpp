#include "ServerStatisticCheckerController.h"
#include "../Common/DBCommon.h"
#include "../Model/CollectorModel.h"
#include "../Model/JsonModel.h"
#include "../Model/ServerStatisticCheckerModel.h"

CServerStatisticCheckerController::CServerStatisticCheckerController(void)
{
}


CServerStatisticCheckerController::~CServerStatisticCheckerController(void)
{
}

/*============= Compare Server Statistic With SnS ========================
 * Function: CompareServerStatisticWithSnS
 * Description: Compare amount server physical & virtual with SnS
 * Return: void
 *========================================================================
 */
void CServerStatisticCheckerController::CompareServerStatisticWithSnS(CCollectorModel *pCoiectorInfo, char* pData)
{
	CJsonModel objJsonModel; 
	string strDataInfo;
	string strDirtyTable;
	string strServerTable;

	int iSnSPhysical = 0;
	int iSnSVirtual = 0;
	
	int iTotalServerU = 0;
	int iTotalServerChassis = 0;
	int iTotalServerVirtual = 0;
	int iTotalServerUnknown = 0;

	BSONObj boCond;

	strDataInfo = pData;
	strDirtyTable = pCoiectorInfo->GetDirtyTableName();
	strServerTable = pCoiectorInfo->GetTableName();
	
	cout << "table:" << strServerTable << endl;
	try
	{
		Json::Value jRootValue;
		jRootValue = objJsonModel.parseValueRootJson(strDataInfo);
		
		if (!jRootValue.isNull())
		{
			if (!jRootValue["Physical"].isNull())
				iSnSPhysical = jRootValue["Physical"].asInt();
			if (!jRootValue["Virtual"].isNull())
				iSnSVirtual = jRootValue["Virtual"].asInt();
			
			cout << "sns physical:" << iSnSPhysical << endl;
			cout << "sns virtual:" << iSnSVirtual << endl;

			//Count server U
			boCond = BSON("server_type" << SERVER_U << "deleted" << 0);
			iTotalServerU = (int)Count(strServerTable, boCond);
			cout << "Server U:" << iTotalServerU << endl;

			//Count Server Chassis
			boCond = BSON("server_type" << SERVER_CHASSIS << "deleted" << 0);
			iTotalServerChassis = (int)Count(strServerTable, boCond);
			cout << "Server Chassis:" << iTotalServerChassis << endl;

			//Count Server Virtual
			boCond = BSON("server_type" << SERVER_VIRTUAL << "deleted" << 0);
			iTotalServerVirtual = (int)Count(strServerTable, boCond);
			cout << "Server Virtual:" << iTotalServerVirtual << endl;

			//Count Server Unknown
			boCond = BSON("server_type" << UNKNOWN << "deleted" << 0);
			iTotalServerUnknown = (int)Count(strServerTable, boCond);
			cout << "Server Unknown:" << iTotalServerUnknown << endl;

			if ((iSnSVirtual != iTotalServerVirtual) || 
				(iSnSPhysical != (iTotalServerU + iTotalServerChassis + iTotalServerUnknown)))
			{
				time_t tDate;
				tDate = CUtilities::GetDateAgo(0);

				CServerStatisticCheckerModel oServStatisticModel;
				oServStatisticModel.SetSnSVirtual(iSnSVirtual);
				oServStatisticModel.SetSnSPhysical(iSnSPhysical);
				oServStatisticModel.SetCMDBVirtual(iTotalServerVirtual);
				oServStatisticModel.SetCMDBU(iTotalServerU);
				oServStatisticModel.SetCMDBChassis(iTotalServerChassis);
				oServStatisticModel.SetCMDBUnknown(iTotalServerUnknown);
				oServStatisticModel.SetClock(tDate);
				SaveServerStatisticChecker(strDirtyTable, oServStatisticModel);
			}
		}
	}
	catch(exception& ex)
	{	
		stringstream ssErrorMsg;
		string strLog;
		ssErrorMsg << ex.what() << "][" << __FILE__ << "|" << __LINE__ ;
		strLog = CUtilities::FormatLog(ERROR_MSG, "CCheckerController", "CompareServerStatisticWithSnS","exception:" + ssErrorMsg.str());
		CUtilities::WriteErrorLog(strLog);
	}
}


/*============= Save Server Statistic which was checked ========================
 * Function: SaveServerStatisticChecker
 * Description: Save Server Statistic which was check with SnS
 * Return: void
 *========================================================================
 */
void CServerStatisticCheckerController::SaveServerStatisticChecker(const string& strTableName, CServerStatisticCheckerModel objServStatistic)
{
	BSONObj boServStatisticInfo = objServStatistic.GetServerStatisticCheckerInfo();
	BSONObj boCondition;

	Remove(strTableName, boCondition);
	cout << "checker table:" << strTableName << endl;
	Insert(strTableName, boServStatisticInfo, boCondition);
}
