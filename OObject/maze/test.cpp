#include "DesignModel\Singleton.h"
#include <stdio.h>
class Test : public Singleton<Test>
{
	friend class Singleton<Test>;
	public:
		void TestPrint(){
			printf("This is a Test!");
		}
};

int main(int argc,char** argv)
{
	Test* test = Test::GetSingleton();
	test->TestPrint();
	Test::Release();
	return 0;
}