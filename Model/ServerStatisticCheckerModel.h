 #pragma once
#include "MongodbModel.h"
#include "mongo/client/dbclient.h"
using namespace mongo;

class CServerStatisticCheckerModel: public CMongodbModel
{
public:
	CServerStatisticCheckerModel(void);
	~CServerStatisticCheckerModel(void);

	inline int GetSnSVirtual() { return m_iSnSVirtual; }
	inline void SetSnSVirtual(int iVirtual) { m_iSnSVirtual = iVirtual;}
	
	inline int GetSnSPhysical() { return m_iSnSPhysical; }
	inline void SetSnSPhysical(int iPhysical) { m_iSnSPhysical = iPhysical;}

	inline int GetCMDBVirtual() { return m_iCMDBVirtual; }
	inline void SetCMDBVirtual(int iCMDBVirtual) { m_iCMDBVirtual = iCMDBVirtual; }

	inline int GetCMDBU() { return m_iCMDBU; }
	inline void SetCMDBU(int iCMDBU) { m_iCMDBU = iCMDBU; }

	inline int GetCMDBChassis() { return m_iCMDBChassis; }
	inline void SetCMDBChassis(int iCMDBChassis) { m_iCMDBChassis = iCMDBChassis; }

	inline int GetCMDBUnknown() { return m_iCMDBUnknown; }
	inline void SetCMDBUnknown(int iCMDBUnknown) { m_iCMDBUnknown = iCMDBUnknown; }

	inline int GetClock() { return m_iClock; }
	inline void SetClock(int iClock) { m_iClock = iClock; }

	BSONObj GetServerStatisticCheckerInfo();
protected:
	int m_iSnSVirtual;
	int m_iSnSPhysical;
	int m_iCMDBVirtual;
	int m_iCMDBU;
	int m_iCMDBChassis;
	int m_iCMDBUnknown;
	int m_iClock;
};