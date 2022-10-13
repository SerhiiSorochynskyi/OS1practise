#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <malloc.h>

int main(int argc, char **argv){
	if(argc < 3){
		printf("Please enter the environment name while starting, for example:\n ./fifthTask HOME /temp\n");
		return 0;
	}
	int choice = 0;
	char *path, *ptr;
	ptr = argv[2];
	path = malloc(strlen(ptr)+100);
	while(choice != 1 || choice !=2){
		printf("1)setenv\n2)putenv\n");
		scanf("%d", &choice);
		if(choice == 1){
			if(setenv(argv[1], argv[2], 0) != 0){
				printf("can`t set to this environment: %s", argv[1]);
				return 0;
			}
		}else if(choice == 2){
			strcpy(path, argv[1]);
			strcat(path, "=");
			strcat(path, ptr);
			if(putenv(path) != 0){
				printf("can`t put this environment: %s", argv[1]);
				return 0;
			};
		}else continue;
		printf("%s=%s\n", argv[1], getenv(argv[1]));
		return 0;
	}
}
