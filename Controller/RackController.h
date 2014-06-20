#pragma once
#include "CMDBController.h"

class CMailboxController;

class CRackController :
	public CCMDBController
{
public:
	CRackController(void);
	~CRackController(void);

	void RemoveAvailableU(const string& strRack, const string& strSite, 
						int nFromU, int nToU);
	void AddAvailableU(const string& strRack, const string& strSite, 
						int nFromU, int nToU);
	//Add Switch
	void AddRackSwitch(const BSONObj& boSwitchInfo);
	void RemoveRackSwitch(const BSONObj& boSwitchInfo);
	void UpdateRackSwitch(const BSONObj& boOldCIInfo, const BSONObj& boNewCIInfo, const BSONObj& boChangedFields);

	//Add Swich Chassis
	void AddRackSwitchChassis(const BSONObj& boSwitchInfo, CMailboxController* ptrMailboxController);
	void RemoveRackSwitchChassis(const BSONObj& boSwithInfo);
	void UpdateRackSwitchChassis(const BSONObj& boOldCIInfo, const BSONObj& boNewCIInfo, const BSONObj& boChangedFields, CMailboxController* ptrMailboxController);
	
	//Add PDU
	void AddRackPDU(const BSONObj& boSwitchInfo);
	void RemoveRackPDU(const BSONObj& boSwitchInfo);
	void UpdateRackPDU(const BSONObj& boOldCIInfo, const BSONObj& boNewCIInfo, const BSONObj& boChangedFields);

protected:
	bool FindRackByNameAndSite(const string& strRack, const string& strSite, auto_ptr<DBClientCursor>& ptrResultCursor);
};
