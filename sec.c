#include <stdio.h>

int main(){
  srand(time(NULL));
  
  int n = 15;
  int mass[n];
  int i;
  int average = 0;
  int biggerThanAverage = 0;
  int sumAfterNegative = 0;
  int flag = 0;
  
  for(i = 0; i < n; i++){
    mass[i] = rand()%2000 - 1000;
    average += mass[i];
    printf("%d | ", mass[i]);
  }
  
  average = average/n;
  printf("\n average: %d", average);
  for(i = 0; i < n; i++){
    if(mass[i] > average)
      biggerThanAverage++;
  }
  printf("\n count of numbers that bigger than average: %d", biggerThanAverage);
  
  for(i = 0; i < n; i++){
    if(flag = 1)
      sumAfterNegative += mass[i];
      
    if(mass[i] > 0)
      flag = 1;
  }
  printf("\n sum of elements after first negative: %d", sumAfterNegative);
  
  return 0;
}
