#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
	if(argc == 1){
		printf("Example for call program: ./first 1\n");
		return 0;
	}
	char *info = argv[1];
	char str[10] = "ps -f ";
	strcat(str, info);
	system(str);
	return 0; 
}
