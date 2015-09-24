#include <stdarg.h>
#include <stdio.h>
void arg_test(char* fmat,...)
{
	va_list vl;
    int i=0;
	va_start(vl,fmat);
	do
	{
        int i = va_arg(vl,int);
        if(i == -1) break;
		printf("%d\n",i);
	}while(true);
	va_end(vl);
}

int main(int argc,char* argv[])
{
	arg_test("hello",1,2,3,4);
	return 0;
}
