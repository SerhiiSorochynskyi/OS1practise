#include <stdio.h>
int i, j;
int n = 15;
int flag = 15;

int findSmallest(int mass[], int min){
	flag--;
	int minIndex = 0;
	for(i = 0; i < n; i++){
		if(mass[i] != 0 && mass[i] < min){
			min = mass[i];
			minIndex = i;
		}
	}
	if(mass[minIndex-1] != 0 && minIndex != 0 && mass[minIndex-1] > mass[minIndex]){
		mass[minIndex-1] += mass[minIndex];
		mass[minIndex] = 0;
		return min;
	}else if(mass[minIndex+1] != 0 && minIndex != n  && mass[minIndex+1] > mass[minIndex]){
		mass[minIndex+1] += mass[minIndex];
		mass[minIndex] = 0;
		return min;
	}else{
		for(i = minIndex; i < n; i++){
			if(mass[i] != 0 && mass[minIndex] < mass[i]){
				mass[i] += mass[minIndex];
				mass[minIndex] = 0;
				return min;
			}
		}
		for(i = minIndex; i >= 0; i--){
			if(mass[i] != 0 && mass[minIndex] < mass[i]){
				mass[i] += mass[minIndex];
				mass[minIndex] = 0;
				return min;
			}
		}
	}
	return min;
}

int main(){
	srand(time(NULL));
	int lim = 100;
	int *mass = (int*)malloc(n*sizeof(int));
	for(i = 0; i < n; i++){
		mass[i] = rand()%lim+1;
		printf("[%d]%3d ", i, mass[i]);
	}
	while(flag != 1){
		printf("\n");
		findSmallest(mass, lim*lim);
		for(i = 0; i < n; i++){
			if(mass[i] != 0){
				printf("[%d]%3d ", i, mass[i]);
			}
		}
	}
	return 0;
}
