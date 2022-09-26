#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <unistd.h>

int main(){
	srand(time(NULL));
	int balance = 5000;
	int choice, i;
	int multiplier = 1;
	int bid = 100;
	int flag = 1;
	int game[3];
	
	while(1){
		printf("1)Auto game\n2)Show combinations\n3)Quit\n");
		scanf("%d", &choice);
		if(choice == 1){
			while(flag != -1){
				balance -= bid;
				printf("\n\nYour current balance is %d, bid is %d\n", balance, bid);
				for(i = 0; i < 3; i++){
					game[i] = rand()%8;
					sleep(1);
					printf("%d ", game[i]);
				}
				
				if(game[0] == 5 || game[0] == 7){
					multiplier = 2;
					if(game[1] == game[0]){
						multiplier = 5;
						if(game[2] == game[1]){
							if(game[0] == 5){
								multiplier = 55;
								flag = 2;
							}else{
								printf("JACKPOT!!! YOU WON");
								return 0;
							}
						}
					}
					flag = 2;
				}else{
					if(game[0] == game[1] && game[1] == game[2]){
						if(game[0] == 6){
							printf("\nYOU HAVE BEEN ROBBED BY A ONE-ARMED BANDIT");
							multiplier = -10;
							flag = 2;
						}else{
							multiplier = 33;
							flag = 2;
						}
					}else{
						flag = 0;
					}
				}
				if(flag == 0)
				printf("\nTry again!");
				if(flag == 2){
					printf("\n!!!You won %d credits!!!", bid*multiplier);
					balance += bid*multiplier;
					multiplier = 1;
				}
				sleep(1);
				//system("cls");
				if(balance <= 0)
					flag = -1;
			}
			printf("\nYOU LOSE!");
			return 0;
		}else if(choice = 2){
			printf("\nWinning combinations\nMULTIPLIER X33: 000 111 222 333 444\nMULTIPLIER X2: 5XX 7XX\nMULTIPLIER X5: 55X 77X\nMULTIPLIER X55: 555\nJACKPOT: 777\n\n");
		}else return 0;
}
	return 0;
}
