#include<stdio.h>
#include<limits.h>

void fcfs(int n, int burst_time[]){
    int waiting_time[n];
    int turnaround_time[n];
    int total_waiting_time =0;
    int total_turnaround_time =0;

    waiting_time[0]=0;
    for(int i=1;i<n;i++)
    {
        waiting_time[i] = burst_time[i-1]+waiting_time[i-1];
    }

    for(int i=0;i<n;i++){
        turnaround_time[i] = burst_time[i]+waiting_time[i];
        total_waiting_time += waiting_time[i];
        total_turnaround_time += turnaround_time[i]; 
    }

    printf("Process\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for(int i=0;i<n;i++)
    {
        printf("%d\t%d\t\t%d\t\t%d\n",i+1,burst_time[i],waiting_time[i],turnaround_time[i]);
    }

    printf("Average Waiting Time: %.2f\n", (float) total_waiting_time / n);
    printf("Average Turnaround Time: %.2f\n", (float) total_turnaround_time / n);
}

int main() {
    int n = 4;
    int burst_time[] = {10, 5, 8, 6};
    int priority[] = {2, 1, 4, 3};
    int quantum = 2;

    printf("FCFS:\n");
    fcfs(n, burst_time);


    return 0;
}