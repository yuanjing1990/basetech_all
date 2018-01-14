#ifdef WIN32
#import <msxml6.dll>
#endif
#include <iostream>
using namespace std;
int main(int argc,char* argv[])
{
#ifdef WIN32
	::CoInitialize(NULL);
	MSXML2::IXMLDOMDocumentPtr pDoc;
	MSXML2::IXMLDOMElementPtr xmlRoot;
	HRESULT hr = pDoc.CreateInstance(__uuidof(MSXML2::DOMDocument60));
	if(!SUCCEEDED(hr))
	{
		MessageBox(NULL,"Error","无法创建DOMDocument",MB_OK);
		return 0;
	}
	xmlRoot = pDoc->createElement((_bstr_t)(char*)"Book");
	xmlRoot->setAttribute("id",(_bstr_t)"100");
	pDoc->appendChild(xmlRoot);
	cout << "Hello World!" << endl;
	MSXML2::IXMLDOMElementPtr pNode;
	pNode = pDoc->createElement((_bstr_t)(char*)"Author");
	pNode->Puttext((_bstr_t)"<![CDATA[yuan&jingy]]>");
	xmlRoot->appendChild(pNode);
	pNode = pDoc->createElement((_bstr_t)(char*)"Title");
	pNode->Puttext((_bstr_t)"Story");
	xmlRoot->appendChild(pNode);
	pDoc->save("he.xml");
#endif
	return 0;
}
