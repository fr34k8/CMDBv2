#pragma once
#include "MongodbModel.h"
#include "../Common/Common.h"

class CNotificationModel: public CMongodbModel
{
public:
	CNotificationModel(void);
	virtual ~CNotificationModel(void);

	inline string GetLibraryName() { return m_strLibraryName; }
	inline void SetLibraryName(const string& strLibraryName) { m_strLibraryName = strLibraryName; }

	inline string GetAPIName() { return m_strAPIName; }
	inline void SetAPIName(const string& strAPIName) { m_strAPIName = strAPIName; }

	inline string GetPartnerName() { return m_strPartnerName; }
	inline void SetPartnerName(const string& strPartnerName) { m_strPartnerName = strPartnerName; }

	inline string GetResponse() { return m_strResponse; }
	inline void SetResponse(const string& strResonpse) { m_strResponse = strResonpse; }

	inline void SetData(const BSONObj& objData) { m_objBSON = objData; }
	inline int GetNotification() { return m_iIsNotified; }
	inline void SetNotification(int iIsNotified = API_ACTION_SUCCESS) { m_iIsNotified = iIsNotified; }

	virtual BSONObj GetNotificationInfo(BSONObj boCIInfo, BSONObj boNewCIInfo){};
	static BSONObj GetHistoricalNotiRecord(BSONObj boRecord, BSONObj boStatus);
protected:
	string m_strLibraryName;
	string m_strAPIName;
	string m_strPartnerName;
	string m_strResponse;
	int m_iIsNotified;
};
