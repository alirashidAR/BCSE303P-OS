#include<stdio.h>
#include<limits.h>

void round_robin(int n, int burst_time[], int quantum){
    int remaining_time[n],waiting_time[n],turnaround_time[n];
    int total_waiting_time =0;
    int total_turnaround_time =0;

    for(int i=0;i<n;i++){
        remaining_time[i] = burst_time[i];
        waiting_time[i]=0;
    }

    int current_time =0;
    int done;

    do{
        done =1;
        for(int i=0;i<n;i++){
            if(remaining_time[i]>0){
                done =0;
                if(remaining_time[i]>quantum){
                    current_time += quantum;
                    remaining_time[i] -= quantum;
                }else{
                    current_time += remaining_time[i];
                    waiting_time[i] = current_time - burst_time[i];
                    remaining_time[i]= 0;
                }
            }
        }
    }while(!done);

    for(int i=0;i<n;i++){
        turnaround_time[i] = waiting_time[i]+burst_time[i];
        total_waiting_time += waiting_time[i];
        total_turnaround_time += turnaround_time[i];
    }
    printf("Process\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\n", i + 1, burst_time[i], waiting_time[i], turnaround_time[i]);
    }

    printf("Average Waiting Time: %.2f\n", (float) total_waiting_time / n);
    printf("Average Turnaround Time: %.2f\n", (float) total_turnaround_time / n);

}

int main() {
    int n = 4;
    int burst_time[] = {10, 5, 8, 6};
    int priority[] = {2, 1, 4, 3};
    int quantum = 2;

    printf("\nRound Robin:\n");
    round_robin(n, burst_time, quantum);

    return 0;
}
