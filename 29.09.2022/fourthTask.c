#include <stdio.h>
#include <stdlib.h>
int i, n = 3;
int *arrayList;

void expandArrayList(int newSize, int n){
	int *newArrayList;
	
	newArrayList = (int*)calloc(newSize, sizeof(int));
	for(i = 0; i < n; i++)
		newArrayList[i] = arrayList[i];
		
	arrayList = (int*)calloc(newSize, sizeof(int));
	for(i = 0; i < newSize; i++)
		arrayList[i] = newArrayList[i];
}

void checkCapacity(){
	int newSize;
	for(i = 0; i < n; i++){
		if(i == n-1 && arrayList[i] != 0){
			newSize = (n*3)/2+1;
			expandArrayList(newSize, n);
			n = newSize;
			break;
		}
	}
}

int addNum(int newNum, int lastAddedIndex){
	for(i = 0; i < n; i++){
		if(arrayList[i] == 0 && i >= lastAddedIndex){
			arrayList[i] = newNum;
			return i;
			break;
		}
	}
}

void insertNum(int index, int newNum){
	checkCapacity();
	for(i = n; i > index; i--){
		arrayList[i] = arrayList[i-1];
	}
	arrayList[index] = newNum;
}

int findIndex(){
	printf("enter index from 0 to %d: ", n-1);
	int in = -1;
	while(in < 0 || in > n-1){
		scanf("%d", &in);
	}
	return in;
}

int enterNum(){
	int newNum;
	printf("enter new int num: ");
	scanf("%d", &newNum);
	return newNum;
}

int main(){
	int choice;
	int index;
	int newNum;
	int lastAddedIndex = 0;
	arrayList = (int*)calloc(n, sizeof(int));
	
	while(1){
		printf("\n1)add(int num)\n2)insert(index, int num)\n3)size\n4)remove(index)\n5)set(index, int num)\n6)get(index)\n7)print arrayList\n\n");
		scanf("%d", &choice);
		switch(choice){
			case 1:
				newNum = enterNum();
				checkCapacity();
				lastAddedIndex = addNum(newNum, lastAddedIndex);
				break;
			case 2:
				index = findIndex(n);
				newNum = enterNum();
				insertNum(index, newNum);
				break;
			case 3:
				printf("size of arrayList is: %d\n", n);
				break;
			case 4:
				index = findIndex(n);
				arrayList[index] = 0;
				break;
			case 5:
				index = findIndex(n);
				newNum = enterNum();
				arrayList[index] = newNum;
				break;
			case 6:
				index = findIndex(n);
				printf("[%d]%d\n", index, arrayList[index]);
				break;
			case 7:
				for(i = 0; i < n; i++){
					printf("[%d]%d\n", i, arrayList[i]);
				}
				break;
			default: printf("Wrong operation!");
		}
	}
	return 0;
}
