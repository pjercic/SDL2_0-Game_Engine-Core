#ifndef _CXMLPARSE_H_
#define _CXMLPARSE_H_

#include <vector>
#include <tinyxml2.h>

#ifndef XMLCheckResult
#define XMLCheckResult(a_eResult) if (a_eResult != XML_SUCCESS) { printf("Error: %i\n", a_eResult); return a_eResult; }
#endif

using namespace tinyxml2;

class CXmlParse {

public:
	static CXmlParse            XmlParseControl;
	static std::vector<CXmlParse*>    CXmlParseList;

	//	Variables tied to configuration XML file
	char	TilesetFile[255];
	int		AreaSize;
	char	MapFile[255];

public:
	CXmlParse();

public:
	bool OnLoad(char* File);

};

#endif