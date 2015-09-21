#include <windows.h>
#include <iostream>
class CObject;
struct CRuntimeClass
{
	LPCSTR m_lpClassName;
	int m_nObjectSize;
	UINT m_wSchema;
	CObject* (PASCAL* m_pfnCreateObject)();
	#ifdef _AFXDLL
	CRuntimeClass* (PASCAL* m_pfnGetBaseClass)();
	#else
	CRuntimeClass* m_pBaseClass;
	#endif
	//CObject* CreateObject();
	CRuntimeClass* m_pNextClass;
	//const AFX_CLASSINIT* m_pClassInit;
};

#define DECLARE_DYNAMIC(class_name) \
	public:\
	static const CRuntimeClass class##class_name;\
	virtual CRuntimeClass* GetRuntimeClass() const;
	
#define IMPLEMENT_DYNAMIC(class_name,base_class) \
	IMPLEMENT_RUNTIMECLASS(class_name,base_class,0xFFFF,NULL,NULL)
	
#define IMPLEMENT_RUNTIMECLASS(class_name,base_class,wSchema,pfnNew,class_init) \
	const CRuntimeClass class_name::class##class_name = {\
	#class_name,sizeof(class class_name),wSchema,pfnNew,RUNTIME_CLASS(base_class),NULL};\
	CRuntimeClass* class_name::GetRuntimeClass() const{\
		return RUNTIME_CLASS(class_name);};
		
#define RUNTIME_CLASS(class_name) _RUNTIME_CLASS(class_name)
#define _RUNTIME_CLASS(class_name) ((CRuntimeClass*)(&class_name::class##class_name))	

class CObject
{
	DECLARE_DYNAMIC(CObject)
public:
	
private:
	
};
const CRuntimeClass CObject::classCObject = {
	"CObject",sizeof(CObject),0xffff,NULL,NULL,NULL};
CRuntimeClass* CObject::GetRuntimeClass() const{
	return _RUNTIME_CLASS(CObject);}

class A : public CObject
{
	DECLARE_DYNAMIC(A)
public:
	A(){
		std::cout << "A's Derived Map:\n";
		CRuntimeClass* t = GetRuntimeClass();
		while(t != NULL)
		{
			std::cout << t->m_lpClassName << std::endl;
			t = t->m_pBaseClass;
		}
	}
};
IMPLEMENT_DYNAMIC(A,CObject)

class B : public A
{
	DECLARE_DYNAMIC(B)
public:
	B(){
		std::cout << "B's Derived Map:\n";
		CRuntimeClass* t = GetRuntimeClass();
		while(t != NULL)
		{
			std::cout << t->m_lpClassName << std::endl;
			t = t->m_pBaseClass;
		}
	}
};
IMPLEMENT_DYNAMIC(B,A)

int main(int argc,char* argv[])
{
	B b;
}