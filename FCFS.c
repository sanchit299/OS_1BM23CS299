#include<stdio.h>
int main(){
    int bt[20], wt[20], tat[20] , n;
    float tatavg, wtavg;
    printf("Enter number of processes : ");
    scanf("%d",&n);
    for(int i=0; i<n; i++){
        printf("Enter burst Length: ");
        scanf("%d",&bt[i]);
    }
    wt[0] = wtavg = 0;
    tat[0] = tatavg = 0;
    for(int i=1; i<n; i++){
        wt[i] = wt[i-1] + bt[i-1];
        tat[i] = wt[i] + bt[i];
        wtavg = wtavg + wt[i];
        tatavg = tatavg + tat[i];
    }
    printf("\t PROCESS\t BURST TIME\t WAITING TIME\t TURNAROUND TIME\n");
    for(int i=0; i<n; i++){
        printf("\n\t P%d \t\t %d \t\t %d\t\t %d\n", i , bt[i], wt[i], tat[i]);
    }
    printf("Average Turnaround Time : %f\n",tatavg/n);
    printf("Average Waiting Time : %f",wtavg/n);
    return 0;
}