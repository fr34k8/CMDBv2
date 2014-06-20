#pragma once
#include "Processor.h"

typedef string(*dataAPI)();
class CCITotalCrossCheckProcessor : public CProcessor
{
public:
	CCITotalCrossCheckProcessor(const string& strFileName);
	virtual ~CCITotalCrossCheckProcessor(void);

	void ComparationProceed();
protected:
	string GetDataAPI();
	string m_strLibName;
	string m_strAPIName;
};