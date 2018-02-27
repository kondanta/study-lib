#include "main.h"

void priorityScheduler(int process[], int burstTime[], int priority[]){
	int i, j, temp, pos;
	for(i = 0; i < SIZE; i++){
		pos = i;
		for(j=i+1; j < SIZE; j++){
			if(priority[j] < priority[pos]) // checking the next process priority, if it's higher
				pos = j;					// swap them
		}
		/*Swapping operations.*/
		temp = priority[i];
		priority[i] = priority[pos];
		priority[pos] = temp;

		temp = burstTime[i];
		burstTime[i] = burstTime[pos];
		burstTime[pos] = temp;

		temp = process[i];
		process[i] = process[pos];
		process[pos] = temp;

	}
}