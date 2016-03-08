#include "CXmlParse.h"

CXmlParse CXmlParse::XmlParseControl;

CXmlParse::CXmlParse() {
	;
}

bool CXmlParse::OnLoad(char* File) {

	if (File != NULL) {
		XMLDocument* doc = new XMLDocument();
		doc->LoadFile(File);
		int errorID = doc->ErrorID();
		delete doc; doc = 0;

		printf("Test file '%s' loaded. ErrorID=%d\n", File, errorID);
		if (errorID) {
			printf("Failed to load XML configuration\n");
		}
	}

	return true;
}