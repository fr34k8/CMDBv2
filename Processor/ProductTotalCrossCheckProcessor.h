#pragma once
	#include "Processor.h"
	#include "CITotalCrossCheckProcessor.h"
class CProductTotalCrossCheckProcessor : public CCITotalCrossCheckProcessor
{
public:
	CProductTotalCrossCheckProcessor(const string& strFileName);
	virtual ~CProductTotalCrossCheckProcessor(void);
};