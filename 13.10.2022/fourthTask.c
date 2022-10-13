#include <stdlib.h>
#include <stdio.h>

int main(){
	int i=0;
	extern char **environ;
	while(environ[i]!=NULL){
		printf("%s\n", environ[i]);
		i++;
	}
}
