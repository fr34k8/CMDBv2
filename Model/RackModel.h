#pragma once
#include "DeviceModel.h"

class CRackServerU;

class CRackModel:
	public CDeviceModel
{
public:
	CRackModel(void);
	~CRackModel(void);
	
	BSONObj GetAddServerURecord(BSONObj boInfo);
	BSONObj GetDeleteServerURecord(string strServerSerial);
	
	BSONObj GetAddServerChassisRecord(BSONObj boInfo);
	BSONObj GetDeleteServerChassisRecord(string strServerSerial);
	
	BSONObj GetAddSwitchRecord(BSONObj boInfo);
	BSONObj GetDeleteSwitchRecord(string strSwitchSerial);
	
	BSONObj GetAddSwitchChassisRecord(BSONObj boInfo);
	BSONObj GetDeleteSwitchChassisRecord(string strSwitchSerial);
	BSONObj GetVLanInfo(auto_ptr<DBClientCursor> ptrRackCursor);
	BSONObj GetAddPDURecord(const BSONObj& boInfo);
	BSONObj GetDeletePDURecord(const string& strPDUName, const string& strPDUPMM);

	Query IsExistsChassisQuery(string strRackName, string strSite, string strIPChassis);
	Query IsExistsRackQuery(string strRackName, string strSite);

	void Load(const BSONObj& boRackInfo);
	void AddAvailableU(BSONObj& boRackInfo, int nFromU, int nToU);
	void RemoveAvailableU(BSONObj& boRackInfo, int nFromU, int nToU);
	void CalculateAvailableU(BSONArrayBuilder& babArrayAvailableU);
	void LoadAvailableU(bool bIsAvailable);

	static void CreateSwitchChassisMailInfo(const BSONObj& boSwitchInfo, BSONObj& boMailDataInfo);
protected:
	void InitAvailableU(bool bIsAvailable);
	void UpdateAvailableU(int nFromU, int nToU, bool bIsAvailableRange);
	void UpdateAvailableU(BSONObj& boRackInfo, int nFromU, int nToU, bool bIsAvailable);

protected:
	std::vector<BSONElement> m_vtAvailableU;
	bool m_arrAvailableU[RACK_MAX_U + 1];
};