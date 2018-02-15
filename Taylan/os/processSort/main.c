#include "main.h"


int main(){
	int process[SIZE];
	int burstTime[SIZE];
	int priority[SIZE];
	int arrival[SIZE]={0};
	int pr, bu, pri;
	int i;

	for(i = 0; i < SIZE; i++){
		printf("Please enter process name, burst time and priority $ ");
		scanf("%d", &pr);
		scanf("%d", &bu);
		scanf("%d", &pri);
		process[i] = pr;
		burstTime[i] = bu;
		priority[i] = pri;
	}
	/*Printing the original order of the process*/
	printf("Original process order.\n");
	for(i=0; i<SIZE; i++){
		printf("P[%d]\t", process[i]);
	}
	priorityScheduler(process, burstTime, priority);
	printf("\n");
	/*Printing after priority order*/
	printf("After priority order\n");
	for(i=0; i<SIZE; i++){
		printf("P[%d]\t", process[i]);
	}
	printf("Now roundrobin time \n");
	roundrobin(process, arrival, burstTime);

	return 0;
}
