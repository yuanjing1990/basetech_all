#include <iostream>
using namespace std;
class Singleton
{
protected:
	static Singleton* _m;
	Singleton(){};
public:
	static Singleton* GetSingleton()
	{
		if(_m == NULL)
		{
			try{
				return (_m = new Singleton());
			}catch(...){
				return (_m = NULL);
			}
		}
		else
			return _m;
	};
	static void DestorySingleton()
	{
		if(_m != NULL)
		{
			try{
				delete _m;
			}catch(...){
			}
		}
		_m = NULL;
	};
	void Operation()
	{
		cout << "Singleton's Operation!"; 
	}
};
Singleton* Singleton::_m = NULL;
int main(int argc,char* argv[])
{
	Singleton* s = Singleton::GetSingleton();
	if(s == NULL)
	{
		cout << "GetSingleton Failed!" << endl;
		return 0;
	}
	s->Operation();
	Singleton::DestorySingleton();
}