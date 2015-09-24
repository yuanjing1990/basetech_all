//#include <crtdbg.h>
//#include <iostream>
//#define _DEBUG
//int main(int argc,char* argv[])
//{
//	using namespace std;
//	int* p = new int;
//	*p = 1;
//	cout << _CrtDumpMemoryLeaks() << endl;
//}
/* MyDbgNew.h
 Defines global operator new to allocate from
 client blocks
*/

#ifdef _DEBUG
   #define DEBUG_CLIENTBLOCK   new( _CLIENT_BLOCK, __FILE__, __LINE__)
#else
   #define DEBUG_CLIENTBLOCK
#endif // _DEBUG


/* MyApp.cpp
    Compile options needed: /Zi /D_DEBUG /MLd
 *            or use a
 *      Default Workspace for a Console Application to
 *      build a Debug version
*/
#ifdef WIN32
#include "crtdbg.h"
//#include "mydbgnew.h"

#ifdef _DEBUG
#define new DEBUG_CLIENTBLOCK
#endif

#endif //WIN32

int main( )   {
    char *p1;
    p1 =  new char[40];
#ifdef WIN32
    _CrtMemDumpAllObjectsSince( NULL );
#endif
}
