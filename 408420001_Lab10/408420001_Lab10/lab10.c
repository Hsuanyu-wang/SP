#include "apue.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <signal.h>

void put_pull_rod(int signum);
void fish_eating();
void exit_game(int signum);

int fishNum = 0;	// counting fish number
int boolean = 0;	// used as a boolean

int main(void){

	struct sigaction sig_put_pull_rod;
	sig_put_pull_rod.sa_handler = put_pull_rod;
	
	struct sigaction sig_exit_game;
	sig_exit_game.sa_handler = exit_game;

	//write your code here******************************
	while(1){
		sigaction(SIGTSTP, &sig_exit_game, NULL);
		sigaction(SIGINT, &sig_put_pull_rod, NULL);
		struct sigaction sig_fish_eating;
		sig_fish_eating.sa_handler = fish_eating;
		sigaction(SIGALRM, &sig_fish_eating, NULL);
		alarm(0);
		printf("Fishing is ready!(send '^C' signal to start)\n");
		pause();
		pause();
	}
	//**************************************************
	return 0;
}


void put_pull_rod(int signum){
	//*************************************************
	if(boolean == 0){
		printf("\nPut the fishing rod(wait 2 second)\n");
		sleep(2);
		printf("Bait into water, waiting fish...(wait at most 5 second)\n");
		time_t fish_coming;
		fish_coming = rand()%5+1;
		alarm(fish_coming);
		sleep(fish_coming);
		boolean = 1;
		//if fish is eating will escape in 3 seconds
		alarm(3);
	}
	else if(boolean == 1){
		printf("\nPull the fishing rod\n");
		int rest_time = alarm(0);
		time_t fish_eating;
		fish_eating = rand()%2;
		if(fish_eating){
			if(rest_time > 0){
				printf("Catch a Fish!\n");
				printf("Totally caught fishes: %d\n", ++fishNum);
			}
			time_t bait_eaten;
			bait_eaten = rand()%2;
			if(bait_eaten){
				printf("The bait was eaten!!\n");
			}
		}
		else{
			printf("(No fish eating!)\n");
		}
		boolean = 0;
	}
	//*************************************************
}

void fish_eating(){
	//*************************************************
	if(boolean == 0)
		printf("A fish is eating(coming), pull the fishing rod(send '^C' to pull, time limits = 3 seconds)\n");
	else if(boolean == 1){
		printf("The fish was escaped!\n");
		boolean = 0;
	}
	//*************************************************
}

void exit_game(int signum){
	printf("\nTotally caught fishes: %d\n", fishNum);
	exit(0);
}

