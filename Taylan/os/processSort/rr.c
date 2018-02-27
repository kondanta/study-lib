#include "main.h"

/*It finds the process' cycle time.
Cycle: P1 > P2 > P3 > P4 > P5 > P1 -> like this.
*/
void roundrobin(int process[] , int arrival[],  int bursttime[]){
    int quantum, i, j=SIZE;
    int counter[SIZE]={0};
    printf("\nEnter quantum: ");
    scanf("%d", &quantum);

    for(i = 0; j != 0;){

        if(bursttime[i] <= quantum && bursttime[i] > 0){
            j--;
            printf("%d ", process[i]);
            // i++;
            counter[i] += 1;
            bursttime[i] = 0;
        }if(bursttime[i]==0){
            printf("Process[%d] has cycled `%d` times\n",process[i], counter[i]);
            i++;
        }else if(bursttime[i] > 0){
            bursttime[i] -= quantum;
            counter[i] += 1;
        }
    }
}
