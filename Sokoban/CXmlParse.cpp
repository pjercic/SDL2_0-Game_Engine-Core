#include "CXmlParse.h"

CXmlParse CXmlParse::XmlParseControl;

CXmlParse::CXmlParse() {
	;
}

bool CXmlParse::OnLoad(char* File) {

	if (File != NULL) {

		XMLDocument doc = new XMLDocument();
		XMLError eResult = doc.LoadFile(File);
		int errorID = doc.ErrorID();
	
		printf("Test file '%s' loaded. ErrorID=%d\n", File, errorID);
		if (errorID) {
			printf("Failed to load XML configuration\n");
		}

		XMLNode * pRoot = doc.FirstChild();
		if (pRoot == nullptr)
			return XML_ERROR_FILE_READ_ERROR;

		XMLElement * pElement = pRoot->FirstChildElement("Level");
		if (pElement == nullptr) 
			return XML_ERROR_PARSING_ELEMENT;
		
		//	int
		int iOutInt;
		//eResult = pElement->QueryIntText(&iOutInt);
		eResult = pElement->QueryIntAttribute("RowCount", &AreaSize);
		XMLCheckResult(eResult);

		const char * szAttributeText = nullptr;
		szAttributeText = pElement->Attribute("BackgroundTexture");
		if (szAttributeText == nullptr) return XML_ERROR_PARSING_ATTRIBUTE;
		strcpy(TilesetFile, szAttributeText);

		//	float
		pElement = pRoot->FirstChildElement("Level");
		if (pElement == nullptr) return XML_ERROR_PARSING_ELEMENT;

		float fOutFloat;
		//eResult = pElement->QueryFloatText(&fOutFloat);
		eResult = pElement->QueryFloatAttribute("RowCount", &fOutFloat);
		XMLCheckResult(eResult);

		//	text
		szAttributeText = nullptr;
		pElement = pElement->FirstChildElement("Bricks");
		szAttributeText = pElement->GetText();
		if (szAttributeText == nullptr) return XML_ERROR_PARSING_ATTRIBUTE;
		std::string strOutMonth = szAttributeText;

		//	list of elements
		pElement = pRoot->FirstChildElement("Level")->FirstChildElement("BrickTypes");
		if (pElement == nullptr) return XML_ERROR_PARSING_ELEMENT;

		XMLElement * pListElement = pElement->FirstChildElement("BrickType");
		std::vector<int> vecList;

		while (pListElement != nullptr)
		{
			int iOutListValue;
			eResult = pListElement->QueryIntAttribute("HitPoints", &iOutListValue);
			XMLCheckResult(eResult);

			vecList.push_back(iOutListValue);
			pListElement = pListElement->NextSiblingElement("BrickType");
		}

		delete &doc;
	}

	return true;
}