#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>

int main() {
	pid_t pid = fork();
	time_t now = time(NULL);
	time_t end = now+2;
	int i = 0, j = 0;
	while(now <= end){
		if(pid == 0){
			//printf("process - child\n");
			i++;
		}else if(pid > 0){
			//printf("process - parent, childs pid - %d\n", pid);
			j++;
		}
		now = time(NULL);
	}
	if(pid > 0)
		printf("PARENT result of counting: %d\n", j);
	if(pid == 0)
		printf(" CHILD result of counting: %d\n", i);
	return 0; 
}
