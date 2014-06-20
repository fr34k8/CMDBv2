#pragma once
#include "../Common/Common.h"

class CCIInfoIndexModel;
typedef vector<CCIInfoIndexModel*> CIInfoIndexModelArray;
class CCIIndexPoolerModel
{
public:
	CCIIndexPoolerModel(void);
	virtual ~CCIIndexPoolerModel(void);

	inline void Push(CCIInfoIndexModel* pCIInfoIndexModel) { m_arrCIInfoIndexModel.push_back(pCIInfoIndexModel); }	
	inline int GetLength() { return m_arrCIInfoIndexModel.size(); }

	CCIInfoIndexModel* operator[](int iIndex);
	CCIIndexPoolerModel* Clone();
protected:
	CIInfoIndexModelArray m_arrCIInfoIndexModel;
};
