#include "BaseExternal.h"

typedef char* (*SDKServiceInfo)(string&, char*,char*,char*,unsigned int,char*);

class CSDKService:
	public CBaseExternal
{
public:
	CSDKService(void);
	~CSDKService(void);

	inline char* GetClientId() { return m_pClientId; }
	inline void SetClientId(char* pClientId) { m_pClientId = pClientId; }

	inline string GetPassword() { return m_strPasswd; }
	inline void SetPassword(const string& strPasswd) { m_strPasswd = strPasswd; }
	
	inline char* GetOperation() { return m_pOperation; }
	inline void SetOperation(char* pOperation) { m_pOperation = pOperation; }

	inline char* GetRequestData() { return m_pRequestData; }
	inline void SetRequestData(char* pRequestData) { m_pRequestData = pRequestData; } 
	char* CallService();
protected:
	string GetChecksum(unsigned int iTime); 
protected:
	char* m_pClientId;
	string m_strPasswd;
	char* m_pOperation;
	char* m_pRequestData;
};
