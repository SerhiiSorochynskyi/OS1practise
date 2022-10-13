#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/param.h>
#include <sys/utsname.h>

int main(){
	char hostname[HOST_NAME_MAX + 1];
	struct utsname buf;
	if(gethostname(hostname, HOST_NAME_MAX) != 0){
		printf("can`t show hostname\n");
	}else{
		printf("hostname: %s\n", hostname);
		printf("hostid: %ld\n", gethostid());
	}
	if(uname(&buf) == 0){
		printf("OS: %s\n", buf.sysname);
		printf("OS name: %s\n", buf.nodename);
		printf("OS version: %s\n", buf.version);
		printf("OS release: %s\n", buf.release);
		printf("Arch: %s\n", buf.machine);
		
	}else return 0;
}
