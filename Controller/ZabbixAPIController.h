#pragma once
#include "../Libs/CurlService.h"

class CZabbixAPIController :
	public CCurlService
{
public:
	CZabbixAPIController(const string& strZabbixVersion = "2.0");
	virtual ~CZabbixAPIController(void);

	bool Connect(const string& strLink, const string& strUserName, 
					const string& strPassword);
	bool CreateHost(const string& strHostName, const string& strIp, 
						const string& strPort, const string& strGroupID, 
						const string& strTemplates, string& strHostID);
	bool CreateItem(const string& strName, const string& strKey, 
					const string& strHostID, int nType, int nValueType,
					int nInterfaceID, const string& strApplication,
					int nDelay, string& strItemID);

protected:
	string ComputeLoginData(const string& strUserName, const string& strPassword);
	string ComputeCreateHostData(const string& strHostName, const string& strIp, 
							const string& strPort, const string& strGroupID, 
							const string& strTemplates);
	string ComputeProxyUpdateData(const string& strProxyID, const string& strHostID);
	string ComputeCreateItemData(const string& strName, const string& strKey, 
							const string& strHostID, int nType, int nValueType,
							int nInterfaceID, const string& strApplication,
							int nDelay);
protected:	
	string m_strZabbixVersion;
	string m_strAuthentication;
	string m_strZabbixLink;
};
