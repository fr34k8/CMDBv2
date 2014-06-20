#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <iconv.h>
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/split.hpp>
#include <iterator> // for ostream_iterator
#include <vector>
#include <map>
#include <boost/regex.hpp>
#include <string>
#include <sys/types.h>
#include <sys/wait.h>
#include <dirent.h>

using namespace std;

//=====Log define=====
#define INFO_MSG "Info"
#define ERROR_MSG "Error"
#define WARNING_MSG "Warning"

#ifndef UTILITIES_H
#define UTILITIES_H

class CConfig;

class CUtilities
{
	private:
		string m_strErrorFile;

	public: 
		CUtilities();
		virtual ~CUtilities();
				
		static void WriteDBLog(const std::string& strType, const std::string& strErrorMsg);
		static void WriteErrorLog(const std::string& strType, const std::string& strErrorMsg);
		static void WriteInfoLog(const std::string& strType, const std::string& strMsg);
		static void WriteErrorLog(const std::string& strErrorMsg);
		static string FormatDateSuffixHistory(struct tm tm);
		static string GetDateSuffixHistory(int iPeriod);
		static std::vector<int> GetListZabbixProcessId(string strPathDatePattern);
		static string GetStdoutFromCommand(string cmd);
		static string ReplaceString(string strSubject, const string& strSearch, const string& strReplace);
		static string VIMJsonParser(string VInfo);
		static unsigned long IpToLong(string strIp);
		static vector<string> SplitString(string strBuffer, string strSplit);
		static vector<string> GetIPAddressCorrectly(string strInterfaceInfo);
		static string GetMacAddressCorrectly(string strInterfaceInfo);
		static string RemoveBraces(string strWithBraces);
		static string GetMongoObjId(string strObjId);
		static string GetCurrTime();
		static string GetCurrTime(const char* pFormat);
		static string GetCurrTimeStamp();
		static string ToLowerString(string strText);
		static string ToUpperString(string strText);
		static string GetNameByWebKey(string strKey);
		static string GetStepNameByWebKey(string strKey);
		static string GetUnitByWebKey(string strKey);
		static string ReplaceBlockBracket(string strBlockValue);
		static string GetSuffixPartition(long long lClock, int iPartitionDay = 0);
		static string FormatLog(string strType, string strProcessName, string strFunctionName, string strInfo);
		static long long UnixTimeFromString(string strTime);
		static string UnixTimeToDateTime(string strUnixTime);
		static string StripTags(string strHtml);
		static string SystemCall(string strCmd);
		static string ConvertIntToString(int number);
		static string ConvertLongToString(long number);
		static struct tm* GetLocalTime(time_t *rawtime);
		static char* EncodeUTF8(const char* strValue);
		static pid_t CheckExistingProcess(const char* cName);
		static string GetSpecialTime(const char* pFormat, struct tm* timeinfo);
		static time_t GetDateAgo(int iSeconds);
		static string GetAccountDomainByEmail(const string& strEmail);
		static bool IsMatch2String(string strWordA, string strWordB);
};

#endif //UTILITIES_H