 #pragma once
#include "MongodbModel.h"
#include "mongo/client/dbclient.h"
using namespace mongo;

class CInterfaceCheckerModel: public CMongodbModel
{
public:
	CInterfaceCheckerModel(void);
	~CInterfaceCheckerModel(void);

	inline string GetCode() { return m_strCode; }
	inline void SetCode(const string& strCode) { m_strCode = strCode;}

	inline string GetVID() { return m_strVID; }
	inline void SetVID(const string& strVID) { m_strVID = strVID; }
	//--------------------------------------------------------------//
	inline string GetCMDBServerName() { return m_strCMDBServerName; }
	inline void SetCMDBServerName(const string& strServerName) { m_strCMDBServerName = strServerName; }
	//--------------------------------------------------------------//
	inline BSONArray GetCMDBPublicInterface() { return m_baPublicInterface; }
	inline void SetCMDBPublicInterface(BSONArray baInterface) { m_baPublicInterface = baInterface; }
	//--------------------------------------------------------------//
	inline BSONArray GetCMDBPrivateInterface() { return m_baPrivateInterface; }
	inline void SetCMDBPrivateInterface(BSONArray baInterface) { m_baPrivateInterface = baInterface; }
	//--------------------------------------------------------------//
	inline string GetODAServerName() { return m_strODAServerName; }
	inline void SetODAServerName(const string& strServerName) { m_strODAServerName = strServerName; }
	//--------------------------------------------------------------//
	inline BSONArray GetODAPublicInterface() { return m_baODAPublicInterface; }
	inline void SetODAPublicInterface(BSONArray baInterface) { m_baODAPublicInterface = baInterface; }
	//--------------------------------------------------------------//
	inline BSONArray GetODAPrivateInterface() { return m_baODAPrivateInterface; }
	inline void SetODAPrivateInterface(BSONArray baInterface) { m_baODAPrivateInterface = baInterface; }
	//--------------------------------------------------------------//
	inline int GetServerType() { return m_nServerType; }
	inline void SetServerType(int nServerType) { m_nServerType = nServerType; }
	//--------------------------------------------------------------//
	inline int GetServerStatus() { return m_nServerStatus; }
	inline void SetServerStatus(int nServerStatus) { m_nServerStatus = nServerStatus; }
	//--------------------------------------------------------------//
	inline int GetIsMatch() { return m_nIsMatch; }
	inline void SetIsMatch(int nIsMatch) { m_nIsMatch = nIsMatch; }

	BSONObj GetInterfaceCheckerInfo();

protected:
	string m_strCode;
	string m_strVID;
	string m_strCMDBServerName;
	string m_strODAServerName;
	BSONArray m_baPublicInterface;
	BSONArray m_baPrivateInterface;
	BSONArray m_baODAPublicInterface;
	BSONArray m_baODAPrivateInterface;
	int m_nServerType;
	int m_nServerStatus;
	int m_nIsMatch;

};