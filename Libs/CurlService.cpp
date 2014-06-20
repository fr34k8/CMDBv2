#include "CurlService.h"

//#define HEADER "Content-Type: application/json"
#define ZABBIX_API_HEADER		"Content-Type: application/json-rpc"
#define ZABBIX_API_USER_AGENT	"Chrome/13.0.764.0"

#define HEADER "Content-Type: text/xml"
#define USER_AGENT "Mozilla/5.0 Chromium/13.0.764.0 Chrome/13.0.764.0 Safari/534.35"

CCurlService::CCurlService(void)
{
}

CCurlService::~CCurlService(void)
{
}

bool CCurlService::CallLink(char* pUrl, char* pUsername, char* pPassword, char* pField, char** _pReturn)
{
	bool bResult = true;
	char *pDataInfo = NULL;

	CURL *curl;
	//curl_global_init(CURL_GLOBAL_ALL);

	CURLcode res;
	string readBuffer;

	string strUrl;
	string strParameter;

	strUrl = pUrl;
	
	if (NULL != pField)
	{
		strParameter = pField;
		strUrl += strParameter;
	}
	
	cout << "URL:" << strUrl << endl;
	struct curl_slist *headers = NULL;
	headers = curl_slist_append(headers, HEADER);
	curl = curl_easy_init();
	curl_easy_setopt(curl, CURLOPT_URL, (char*)strUrl.c_str());

	if (NULL != pUsername)
		curl_easy_setopt(curl, CURLOPT_USERNAME, pUsername); 

	if (NULL != pPassword)
		curl_easy_setopt(curl, CURLOPT_PASSWORD, pPassword); 
	
    curl_easy_setopt(curl, CURLOPT_TIMEOUT, 60);
	curl_easy_setopt(curl, CURLOPT_USERAGENT, USER_AGENT);
    curl_easy_setopt(curl, CURLOPT_HEADER, 0);
	//curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "PUT");
	 
	/*if(NULL != pField) {
		curl_easy_setopt(curl, CURLOPT_POST, 1);
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, pField);
	}*/
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER,headers);
	
    res = curl_easy_perform(curl);
	if(res != CURLE_OK) {
		bResult = false;
	}
	else
	{
		int nDataLength = 0;
		nDataLength = readBuffer.size();
		pDataInfo = new char[nDataLength + 1];
		pDataInfo[nDataLength] = '\0';

		//// Copy result to memory
		strcpy(pDataInfo, readBuffer.c_str());
		*_pReturn = pDataInfo;
	}
    curl_easy_cleanup(curl);
	//curl_global_cleanup();

	return bResult;
}

bool CCurlService::CallZabbixAPI(const string& strURL, const string& strData, 
								 string& strResult)
{
	bool bResult = true;
	CURL *pCurl;
	CURLcode cURLCode;

	struct curl_slist *headers = NULL;

	// Init CURL
	headers = curl_slist_append(headers, ZABBIX_API_HEADER);
	pCurl = curl_easy_init();
	curl_easy_setopt(pCurl, CURLOPT_URL, (char*)strURL.c_str());

	curl_easy_setopt(pCurl, CURLOPT_TIMEOUT, 60);
	curl_easy_setopt(pCurl, CURLOPT_USERAGENT, ZABBIX_API_USER_AGENT);
    curl_easy_setopt(pCurl, CURLOPT_HEADER, 0);

	if(strData != "") {
		curl_easy_setopt(pCurl, CURLOPT_POST, 1);
		curl_easy_setopt(pCurl, CURLOPT_POSTFIELDS, strData.c_str());
	}

	curl_easy_setopt(pCurl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(pCurl, CURLOPT_WRITEDATA, &strResult);
    curl_easy_setopt(pCurl, CURLOPT_HTTPHEADER,headers);
	
    cURLCode = curl_easy_perform(pCurl);
	if(cURLCode != CURLE_OK) {
		bResult = false;
	}
	
    curl_easy_cleanup(pCurl);

	return bResult;
}