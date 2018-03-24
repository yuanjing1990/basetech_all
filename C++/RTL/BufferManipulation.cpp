//memcpy_sʹ�ò���
//
//
//
//

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <memory.h>

#ifdef WIN32
#define _memccpy memccpy
#define _swab swab
#endif

char buf[512] = "Hello,This is a test!";

int main(int argc,char* argv[])
{
	char dest[512] = {0};
	memccpy(dest,buf,'T',512);
	printf("%s",dest);
	printf("\n");
	printf("%s",(char*)memchr(buf,'T',512));
	printf("\n");
	memcpy(dest,buf,512);
	printf("%s",dest);
	printf("\n");
	memcmp(buf,dest,sizeof(buf)) >= 0 ? printf("buf is Larger") : printf("dest is Larger");
	printf("\n");
	printf("%lu",sizeof(buf));
	memset(dest,0,512);
	memcpy(dest,buf,strlen(buf)-3);
	printf("%s",dest);
	printf("\n");

	memmove(dest+2,dest,strlen(dest));
	printf("%s",dest);
	printf("\n");
	//errno_t err;
	//int err = memcpy_s(dest,510,buf,512);
	//if(err == ERANGE)
	//	printf("%s","Dest Range Error!");
#ifdef WIN32
	swab(buf,dest,sizeof(buf));
	printf(dest);
	printf("\n");
	swab(dest,dest,sizeof(buf));
	printf(dest);
	printf("\n");
#endif
	return 0;
}
