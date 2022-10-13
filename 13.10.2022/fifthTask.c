#include <stdlib.h>
#include <stdio.h>

int main(int argc, char **argv){
	if(argv[1]==NULL){
		printf("Please enter the environment name while starting, for example: ./fifthTask SHELL\n");
		return 0;
	}
	char *env = getenv(argv[1]);
	printf("for %s is\n%s\n", argv[1], env);
}
