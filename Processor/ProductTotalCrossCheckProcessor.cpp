#include "ProductTotalCrossCheckProcessor.h"
#include "../Config/ConfigFile.h"
#include "../Common/DBCommon.h"

CProductTotalCrossCheckProcessor::CProductTotalCrossCheckProcessor(const string& strFileName)
:CCITotalCrossCheckProcessor(strFileName)
{
	/*m_strLibName = SNS_SERVICES_LIB;
	m_strAPIName = API_SNS_GET_TOTAL_SERVER_PER_PRODUCT;*/
	m_strLibName = "libSnSService-1.0.so";
	m_strAPIName = "GetTotalServerPerProduct";
}

CProductTotalCrossCheckProcessor::~CProductTotalCrossCheckProcessor(void)
{
}