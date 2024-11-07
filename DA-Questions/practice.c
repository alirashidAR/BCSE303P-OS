#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
#include<stdbool.h>
#include<unistd.h>


void priority(int n, int burst_time[])
{
    int waiting_time[n], turn_around_time[n];
    bool comepleted[n];
    int current_time =0;
    int count =0;
    for(int i=0;i<n;i++) comepleted[i] =  false;

    while(count<n)
    {
        int shortest =-1;
        for(int i=0;i<n;i++)
        {
            if(!comepleted[i] && (shortest==-1 || burst_time[i]<burst_time[shortest]))
            {
                shortest=i;
            }
        }
        current_time += burst_time[shortest];
        waiting_time[shortest] = current_time - burst_time[shortest];
        turn_around_time[shortest] =  current_time;
        comepleted[shortest] = true;
        count++;
    }
}