#include <stdarg.h>
#include <stdio.h>
void arg_test(char* fmat,...)
{
	va_list vl;
	va_start(vl,fmat);
	if(va_arg(vl,int) != -1)
	{
		printf("%d",(int)vl);
	}
	va_end(vl);
}

int main(int argc,char* argv[])
{
	arg_test("hello",1,2,3,4);
	return 0;
}