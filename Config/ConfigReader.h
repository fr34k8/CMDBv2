#pragma once
#include <string.h>
#include <iostream>
#include <fstream>
#include <string>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>
using namespace std;
using boost::property_tree::ptree;

#ifndef BASECONFIG_H
#define BASECONFIG_H

class CConfigReader
{
	protected:
		string m_strFileName;
		ptree m_pt;

	public: 
		CConfigReader();
		CConfigReader(const std::string& file_name);
		virtual ~CConfigReader();
		
		void Update(const std::string& strGroup, const std::string& strProperty, const std::string& strValue);
		void Add(const std::string& strGroup, const std::string& strProperty, const std::string& strValue);
		std::string ReadStringValue(const std::string& strGroup, const std::string& strProperty);
		bool ReadBoolValue(const string& strGroupName, const string& strProperty);
		int ReadIntValue(const string& strGroupName, const string& strProperty);
};

#endif//BASECONFIG_H