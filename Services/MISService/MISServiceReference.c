#include "stdio.h"
#include <iostream>
#include <string>
#include <unistd.h>		/* defines _POSIX_THREADS if pthreads are available */
#if defined(_POSIX_THREADS) || defined(_SC_THREADS)
#include <pthread.h>
#endif
#include <signal.h>		/* defines SIGPIPE */
#include "../../Common/ExternalCommon.h"
#include "../../Common/Common.h"
#include "../../Libs/CurlService.h"
using namespace std;

extern "C"  char* GetMISDataInfo(char* pField)
{	
	CCurlService *pCurl = new CCurlService();
	char *pResponse = NULL;
	string strUserName = "sdk_intf";
	string strPasswd = "Vng@SDK#intf!2438035";
	
	pCurl->CallLink((char*)MIS_ORGCHART_URL, (char*)strUserName.c_str(), (char*)strPasswd.c_str(), pField, &pResponse);

	if (NULL != pCurl)
		delete pCurl;

	return pResponse;
}

extern "C"  char* GetMISUserInfo(char* pField)
{	
	CCurlService *pCurl = new CCurlService();
	char *pResponse = NULL;
	string strUserName = "misesb";
	string strPasswd = "Vng@123";

	pCurl->CallLink((char*)MIS_ESB_ORGCHART_URL, (char*)strUserName.c_str(), (char*)strPasswd.c_str(), pField, &pResponse);
	
	if (NULL != pCurl)
		delete pCurl;

	return pResponse;
}

extern "C"  int ProductMISAPI(string strField, string &strResult)
{
	CCurlService *pCurl = new CCurlService();
	char *pResponse = NULL;
	char *pField = NULL;
	pField = new char[strlen(strField.c_str()) + 1];
	strcpy(pField, strField.c_str());
	string strUserName = "misesb";
	string strPasswd = "Vng@123";
	if (strField.find("\"request_code\" : \"\"") != std::string::npos){
		return API_ACTION_FAIL;
	}

	pCurl->CallLink((char*)MIS_ESB_UPDATE_PRODUCT_URL, (char*)strUserName.c_str(), (char*)strPasswd.c_str(), pField, &pResponse);
	if (NULL != pCurl)
		delete pCurl;
	strResult = string(pResponse);
	if (strResult.find("[]") != std::string::npos)
		return API_ACTION_FAIL;
	return API_ACTION_SUCCESS;
}
