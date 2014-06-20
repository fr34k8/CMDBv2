#include "ZabbixAPIController.h"
#include "../Model/JsonModel.h"

#define ZABBIX_AGENT_PORT			10050
#define ZABBIX_API_PROTOCOL			"jsonrpc"
#define ZABBIX_API_METHOD			"method"
#define ZABBIX_API_PARAMS			"params"
#define ZABBIX_API_USER				"user"
#define ZABBIX_API_PASSWORD			"password"
#define ZABBIX_API_ID				"id"

#define ZABBIX_METHOD_LOGIN			"user.login"
#define ZABBIX_METHOD_HOST_CREATE	"host.create"
#define ZABBIX_METHOD_HOST_DELETE	"host.delete"
#define ZABBIX_METHOD_PROXY_UPDATE	"proxy.update"
#define ZABBIX_METHOD_ITEM_CREATE	"item.create"

CZabbixAPIController::CZabbixAPIController(const string& strZabbixVersion)
{
	m_strZabbixVersion = strZabbixVersion;
	m_strAuthentication = "";
	m_strZabbixLink = ""; 
}

CZabbixAPIController::~CZabbixAPIController(void)
{
}

bool CZabbixAPIController::Connect(const string& strLink, const string& strUserName, 
								   const string& strPassword)
{
	bool bResult = false;
	m_strZabbixLink = strLink;
	string strData = ComputeLoginData(strUserName, strPassword);
	
	bResult = CallZabbixAPI(strLink, strData, m_strAuthentication);	

	return bResult;
}

string CZabbixAPIController::ComputeLoginData(const string& strUserName, 
											 const string& strPassword)
{
	/* Data Format
	{
   "jsonrpc": "2.0",
   "method": "user.login",
   "params": {
      "user": "admin",
      "password": "zabbix"
   },
   "id": 1
	}*/

	CJsonModel objParams;
	objParams.AppendValue(ZABBIX_API_USER, strUserName);
	objParams.AppendValue(ZABBIX_API_PASSWORD, strPassword);

	CJsonModel objData;
	objData.AppendValue(ZABBIX_API_PROTOCOL, m_strZabbixVersion);
	objData.AppendValue(ZABBIX_API_METHOD, ZABBIX_METHOD_LOGIN);
	objData.AppendValue(ZABBIX_API_PARAMS, objParams.toString());
	objData.AppendValue(ZABBIX_API_ID, 1);

	return objData.toString();
}

bool CZabbixAPIController::CreateHost(const string& strHostName, const string& strIp, 
										const string& strPort, const string& strGroupID,
										const string& strTemplates, string& strHostID)
{	
	bool bResult = false;	
	string strData = ComputeCreateHostData(strHostName, strIp, strPort, 
										strGroupID, strTemplates);
	
	bResult = CallZabbixAPI(m_strZabbixLink, strData, strHostID);	

	return bResult;	
}

string CZabbixAPIController::ComputeCreateHostData(const string& strHostName, 
											   const string& strIp, 
											   const string& strPort, 
											   const string& strGroupID, 
											   const string& strTemplates)
{
	/* Data Format
	{
    "jsonrpc": "2.0",
    "method": "host.create",
    "params": {
        "host": "Linux server",
        "interfaces": [
            {
                "type": 1,
                "main": 1,
                "useip": 1,
                "ip": "192.168.3.1",
                "dns": "",
                "port": "10050"
            }
        ],
        "groups": [
            {
                "groupid": "50"
            }
        ],
        "templates": [
            {
                "templateid": "20045"
            }
        ],
        "inventory": {
            "macaddress_a": "01234",
            "macaddress_b": "56768"
        }
    },
    "auth": "038e1d7b1735c6a5436ee9eae095879e",
    "id": 1
	}
	*/
	CJsonModel objData;

	return objData.toString();
}

string CZabbixAPIController::ComputeProxyUpdateData(const string& strProxyID, const string& strHostID)
{
	/* Data format
	{
    "jsonrpc": "2.0",
    "method": "proxy.update",
    "params": {
        "proxyid": "10293",
        "hosts": [
            "10294",
            "10295"
        ]
    },
    "auth": "038e1d7b1735c6a5436ee9eae095879e",
    "id": 1
	}*/
	CJsonModel objData;

	return objData.toString();
}

bool CZabbixAPIController::CreateItem(const string& strName, const string& strKey, 
									  const string& strHostID, int nType, 
									  int nValueType, int nInterfaceID, 
									  const string& strApplication, 
									  int nDelay, string& strItemID)
{
	bool bResult = false;	
	string strData = ComputeCreateItemData(strName, strKey, strHostID, 
											nType, nValueType, nInterfaceID, 
											strApplication, nDelay);
	
	bResult = CallZabbixAPI(m_strZabbixLink, strData, strItemID);	

	return bResult;	
}

string CZabbixAPIController::ComputeCreateItemData(const string& strName, 
												   const string& strKey, 
												   const string& strHostID, 
												   int nType, int nValueType,
												   int nInterfaceID, 
												   const string& strApplication,
												   int nDelay)
{
	/*
	Data format
	{
    "jsonrpc": "2.0",
    "method": "item.create",
    "params": {
        "name": "Free disk space on $1",
        "key_": "vfs.fs.size[/home/joe/,free]",
        "hostid": "30074",
        "type": 0,
        "value_type": 3,
        "interfaceid": "30084",
        "applications": [
            "609",
            "610"
        ],
        "delay": 30
    },
    "auth": "038e1d7b1735c6a5436ee9eae095879e",
    "id": 1
	}
	*/
	CJsonModel objData;

	return objData.toString();
}