#include "../Common/Common.h"
#include "json/json.h"
#include <json/value.h>

class CJsonModel
{
public:
	CJsonModel();
	virtual ~CJsonModel();
	bool AppendJson(string strJsonValue);
	void AppendValue(string strFieldNamme, string strJsonValue);
	void AppendValue(string strFieldNamme, int iJsonValue);
	string GetString(string strFieldNamme);
	int GetInt(string strFieldNamme);
	long long GetLong(string strFieldNamme);
	string toString();
	string toString(unsigned int iIndex, string strKey);
	string toString(string strKey, unsigned int iIndex);
	Json::Value parseValueRootJson(string strJsonValue);
	string toStringIndex(unsigned int iIndex);
	string toStringKey(string strKey);
	bool GoToIndex(unsigned int iIndex);
	bool GoToKey(string strKey);
	int GetSize();
	void DestroyData();

protected:
	Json::Value m_valRoot;
};