#include "PDUInfoChangeModel.h"

CPDUInfoChangeModel::CPDUInfoChangeModel(void)
{
	InitLookUpMap();
}

CPDUInfoChangeModel::~CPDUInfoChangeModel(void)
{
}


void CPDUInfoChangeModel::InitLookUpByPass()
{
	m_mapLookUpByPass["pdu_id"] = true;
}
