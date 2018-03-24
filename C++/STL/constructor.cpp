#include <iostream>
#include <string.h>
#include "myutil.h"

using namespace std;
//一个自定义的String类型
class String
{
public:
	//String(){};
	String(const char* p){
		if(p == 0)
		{
			m_data = new char[1];
			m_data[0] = '\0';
			return;
		}
		m_data = new char[strlen(p)+1];
		m_data[strlen(p)] = '\0';
		strcpy(m_data,p);
	};
	~String(){
		delete[] m_data;
	};
	friend ostream& operator<<(ostream& os,String& s)
	{
		os << s.m_data << endl;
		return os;
	}
private:
	char* m_data;
};

template<class T>
class NamedPtr
{
public:
	NamedPtr(const string& initName, T* initPtr):name(initName),ptr(initPtr){};
private:
	string name;
	T* ptr;
};
void DoNothing(String t)
{
}
static String s("Test");
int main(int argc,char* argv[])
{
	cout << s;
	String str("Hello");
	String str1("World");
	DoNothing(str1);
	str = str1;
	s = str1;
	cout << s;
}
