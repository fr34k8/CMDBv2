#include <curl/curl.h>
#include <curl/easy.h>
#include <string.h>
#include <iostream>

using namespace std;

struct MemoryStruct {
  char *memory;
  size_t size;
};

class CCurlService
{
public:
	CCurlService(void);
	~CCurlService(void);
		
	bool CallLink(char* pUrl, char* pUsername, char* pPassword, char* pField, char** _pReturn);
	static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp){
		((string*)userp)->append((char*)contents, size * nmemb);
		return size * nmemb;
	}

protected:
	bool CallZabbixAPI(const string& strURL, const string& strData, string& strResult);
};

