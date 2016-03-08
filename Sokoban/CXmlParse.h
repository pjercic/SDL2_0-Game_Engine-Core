#ifndef _CXMLPARSE_H_
#define _CXMLPARSE_H_

#include <vector>
#include <tinyxml2.h>

using namespace tinyxml2;

class CXmlParse {

public:
	static CXmlParse            XmlParseControl;

public:
	CXmlParse();

public:
	bool OnLoad(char* File);

};

class CXmlParseData {
public:
	static std::vector<CXmlParseData>    XmlParseDataList;

public:
	CXmlParseData();
};

#endif