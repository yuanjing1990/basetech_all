#include <windows.h>
#include <tchar.h>
#include <stdio.h>
int CDECL MessageBoxPrintf(TCHAR* szCaption,TCHAR* szFormat,...)
{
	TCHAR szBuffer[1024];
	va_list pArgList;
	va_start(pArgList,szFormat);
	//������غ������Բο�Windows������Ƶ�һ��
	//�Ѷ�ջ�еĲ�����ʽ����szBuffer��
	_vsntprintf(szBuffer,sizeof(szBuffer)/sizeof(TCHAR),szFormat,pArgList);
	va_end(pArgList);
	return MessageBox(NULL,szBuffer,szCaption,0);
}
int WINAPI WinMain(HINSTANCE hInst,HINSTANCE hPrev,LPTSTR szCmdLine,int iCmdShow)
{
	MessageBoxPrintf(_TEXT("HelloMsg"),_TEXT("Hello %s,Welcome To %s!"),_TEXT("Yuanjing"),_TEXT("Windows"));
	return 0;
}

