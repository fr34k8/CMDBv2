#pragma once
#include "MongodbModel.h"
#include "../Common/Common.h"

class CCollectorModel: public CMongodbModel
{
public:
	CCollectorModel(void);
	virtual ~CCollectorModel(void);

	inline string GetLibraryName() { return m_strLibraryName; }
	inline void SetLibraryName(const string& strLibraryName) { m_strLibraryName = strLibraryName; }

	inline string GetAPIName() { return m_strAPIName; }
	inline void SetAPIName(const string& strAPIName) { m_strAPIName = strAPIName; }

	inline string GetCollectorName() { return m_strCollectorName; }
	inline void SetCollectorName(const string& strCollectorName) { m_strCollectorName = strCollectorName; }

	inline string GetSource() { return m_strSource; }
	inline void SetSource(const string& strSource) { m_strSource = strSource; }

	inline string GetDirtyTableName() { return m_strDirtyTableName; }
	inline void SetDirtyTableName(const string& strDirtyTableName) { m_strDirtyTableName = strDirtyTableName; }
	
	inline string GetTableName() { return m_strTableName; }
	inline void SetTableName(const string& strTableName) { m_strTableName = strTableName; }

	inline string GetType() { return m_strType; }
	inline void SetType(const string& strType) { m_strType = strType; }

protected:
	string m_strLibraryName;
	string m_strAPIName;
	string m_strCollectorName;
	string m_strSource;
	string m_strDirtyTableName;
	string m_strTableName;
	string m_strType;
};
