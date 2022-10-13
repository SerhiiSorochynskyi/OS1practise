#include <stdlib.h>
#include <stdio.h>

int main(int argc, char **argv){
	if(argc < 2){
		clearenv();
	}else if(unsetenv(argv[1]) != 0)
		printf("can`t delete this environment: %s\n", argv[1]);
	int i=0;
	extern char **environ;
	if(environ==NULL){
		printf("Environment is empty!\n");
		return 0;
	}
	while(environ[i]!=NULL){
		printf("%s\n", environ[i]);
		i++;
	}
	return 0;
}
