#pragma once

#include "../Utilities/Utilities.h"
#include "../Utilities/DBUtilities.h"
#include <vector>
#include <queue>
#include <stdlib.h>
#include <stdio.h>
#include <algorithm>
#include <string.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <time.h>
#include <map>
#include <set>
#include <iterator> // for ostream_iterator
using namespace std;

typedef vector<string> StringArray;
typedef vector<int> IntArray;
typedef set<string> StringSet;
typedef enum
{
	IP_PUBLIC = 1,
	IP_PRIVATE = 0
} IP_TYPE;

struct InterfaceInfo
{
	string strJson;
	string strMac;
	IP_TYPE eType;
};

struct NotificationAPIInfo
{
	string strJson;
	string strCode;
	string strServerName;
	int iActionType;
	int iStatus;
};

#define JSON_ROOT 0;
//======Logic define==========
#define YES 1
#define NO 0

//======Time define===========
#define SEC_PER_MIN		60
#define SEC_PER_HOUR	3600
#define SEC_PER_DAY		86400
#define SEC_PER_WEEK		(7 * SEC_PER_DAY)
#define SEC_PER_MONTH		(30 * SEC_PER_DAY)
#define SEC_PER_YEAR		(365 * SEC_PER_DAY)
//===Interval Define (by secs)===
#define DB_CONNECT_RETRY_INTERVAL 1
#define DB_RECONNECT_TIME 3
#define INFO_INDEX_POOLER 5
#define LOAD_INFO_DELAY 1
#define LOAD_INFO_CHANGE_CYCLE 1
#define TRACK_CHANGE_INTERVAL 1
#define NOTI_PROCESS_DELAY 500

#define CI_TYPE_SERVER 1
#define CI_TYPE_PRODUCT 2
#define CI_TYPE_DEPARTMENT 3
#define CI_TYPE_DIVISION 4
#define CI_TYPE_CHASSIS 5
#define CI_TYPE_AGGREGATION_SWITCH 6
#define CI_TYPE_ACCESS_SWITCH 7
#define CI_TYPE_CORE_SWITCH 8
#define CI_TYPE_PDU 9

#define ACTION_TYPE_ADD 1
#define ACTION_TYPE_UPDATE 2
#define ACTION_TYPE_DELETE 3

#define ACTION_TYPE_FIELD "action type"

#define PARTNER_DC "DC"
#define PARTNER_MIS "MIS"
#define PARTNER_TOM "TOM"
#define PARTNER_SNS "SNS"
#define COLLECTOR_MIS "mis"
#define COLLECTOR_SNS "sns"
#define COLLECTOR_ODA "oda"
#define CHANGE_BY_BACKEND "backend"
//==========================================
//=== Interval Synchronize Data (by secs)===
#define SYNC_INFO_DELAY 1800
//=== Interval Check Data (by secs)===
#define CHECK_INFO_DELAY 1800
//=== Interval Load Data (by secs)===
#define LOAD_DATA_DELAY 1
//=== Interval Load Data (by secs)===
#define MINING_DATA_DELAY 10
//=== Interval Compute Rack Data (by secs)===
#define COMPUTE_RACK_DATA_DELAY 30
//==========================================
#define CI_COLLECTION 0
#define OLD_FIELD 1

//=====THREAD======
#define MIN_INDEX_POOLER_RECORD 2000 // will be proceeed in 2000/50 = 40 seconds
//=====CI NAME=====
#define SERVER "server"
#define SERVER_VM "server_vm"
#define SERVER_PHYSICAL "server_physical"
#define PRODUCT "product"
#define DEPARTMENT "department"
#define DIVISION "division"

//===API RESULT===//
#define API_ACTION_ERROR 0
#define API_ACTION_SUCCESS 1
#define API_ACTION_FAIL 2
#define API_RETRY_TIME 3

#define DONE 1
#define NOT_YET 0

#define RACK_MAX_U 42
#define LIMIT_MINING_RECORD 500