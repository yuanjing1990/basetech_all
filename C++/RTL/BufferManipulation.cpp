//memcpy_s使用不了
//
//
//
//

#include <memory.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

char buf[512] = "Hello,This is a test!";

int main(int argc,char* argv[])
{
	char dest[512] = {0};
	_memccpy(dest,buf,'T',512);
	printf(dest);
	printf("\n");
	printf((char*)memchr(buf,'T',512));
	printf("\n");
	memcpy(dest,buf,512);
	printf(dest);
	printf("\n");
	memcmp(buf,dest,sizeof(buf)) >= 0 ? printf("buf is Larger") : printf("dest is Larger");
	printf("\n");
	printf("%d",sizeof(buf));
	memset(dest,0,512);
	memcpy_s(dest,512,buf,strlen(buf)-3);
	printf(dest);
	printf("\n");
	
	memmove(dest+2,dest,strlen(dest));
	printf(dest);
	printf("\n");
	//errno_t err;
	//int err = memcpy_s(dest,510,buf,512);
	//if(err == ERANGE)
	//	printf("%s","Dest Range Error!");
	_swab(buf,dest,sizeof(buf));
	printf(dest);
	printf("\n");
	_swab(dest,dest,sizeof(buf));
	printf(dest);
	printf("\n");
	return 0;
}