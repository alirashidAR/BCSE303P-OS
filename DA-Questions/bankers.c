#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

#define MAX_PROCESSES 10
#define MAX_RESOURCES 10


int allocation[MAX_PROCESSES][MAX_RESOURCES];
int maximum[MAX_PROCESSES][MAX_RESOURCES];
int available[MAX_RESOURCES];
int need[MAX_PROCESSES][MAX_RESOURCES];
int num_processes, num_resources;

void calculateNeed(){
    for(int i=0;i<num_processes;i++)
    {
        for(int j=0;j<num_resources;j++)
        {
            need[i][j] = maximum[i][j] - allocation[i][j];
        }
    }
}


bool canAllocate(int process){
    for(int j=0;j<num_resources;j++)
    {
        if(need[process][j]>available[j])
        {
            return false;
        }
    }
    return true;
}

bool isSafe(){
    int work[MAX_PROCESSES];
    bool finish[MAX_PROCESSES] = {false};
    int safe_seq[MAX_PROCESSES];
    int count =0;

    for(int i=0;i<num_resources;i++)
    {
        work[i] = available[i];
    }

    while(count<num_processes)
    {
        bool found = false;
        for(int i=0;i<num_processes;i++)
        {
            if(!finish[i] && canAllocate(i))
            {   
                for(int j=0;j<num_resources;j++)
                {
                    work[j] += allocation[i][j];
                }
                safe_seq[count++]=i;
                finish[i] = true;
                found = true;
            }
        }

        if(!found)
        {
            return false;
        }
    }

    printf("System is in a safe state.\nSafe sequence is: ");
    for (int i = 0; i < num_processes; i++) {
        printf("P%d ", safe_seq[i]);
    }
    printf("\n");
    return true;

}


bool requestResources(int process, int request[])
{
    for(int i=0;i<num_resources;i++)
    {
        if(need[process][i]<request[i])
        {
            printf(" Requested more than needed");
            return false;
        }
    }

    for(int i=0;i<num_resources;i++)
    {
        if(available[i]<request[i])
        {
            printf(" Not enough resources available");
            return false;
        }
    }

    // we tentatively allocate the resource in doing so we subtract from avalible, need and add in the allocated part;


    for(int i=0;i<num_resources;i++){
        available[i] -= request[i];
        need[process][i] -= request[i];
        allocation[process][i] += request[i];
    }


    if(isSafe()){
        printf("Yes it is safe to allocated");
        return true;
    }else{
        printf("Not safe to allocate the requested resources.");
        // backtrack
        for(int i=0;i<num_resources;i++){
            available[i] += request[i];
            need[process][i] += request[i];
            allocation[process][i] -= request[i];
        }
        return false;   
    }
}


int main(){
    printf("Enter the number of process:");
    scanf("%d\n", &num_processes);

    printf("Enter the number of resources:");
    scanf("%d\n", &num_resources);

    printf("Enter the allocation matrix:\n");
    for(int i=0;i<num_processes;i++){
        for(int j=0;j<num_resources;j++){
            scanf("%d", &allocation[i][j]);
        }
    }

    printf("Enter the maximum matrix:\n");
    printf("Enter the maximum matrix:\n");
    for (int i = 0; i < num_processes; i++) {
        for (int j = 0; j < num_resources; j++) {
            scanf("%d", &maximum[i][j]);
        }
    }

    printf("Enter the available resources: ");
    for (int i = 0; i < num_resources; i++) {
        scanf("%d", &available[i]);
    }

    // Calculate Need matrix
    calculateNeed();

    printf("\nNeed matrix:\n");
    for (int i = 0; i < num_processes; i++) {
        for (int j = 0; j < num_resources; j++) {
            printf("%d ", need[i][j]);
        }
        printf("\n");
    }

    // Check initial safe state
    if (isSafe()) {
        printf("The system is initially in a safe state.\n");
    } else {
        printf("The system is not initially in a safe state.\n");
    }

}