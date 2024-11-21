#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

void fcfs(int pages[],int n, int capacity)
{
    int frames[capacity];
    int faults =0;
    int found = 0;
    int front =0;
    for(int i=0;i<capacity;i++){
        frames[i] =-1;
    }
    
    for(int i=0;i<n;i++)
    {
        found =0;
        for(int j=0;j<capacity;j++)
        {
            if(frames[j]==pages[i])
            {
                found =1;
                break;
            }
        }
        if(found!=1)
        {
            faults++;
            frames[front] = pages[i];
            front = (front+1)%capacity;
        }
    }
    printf("Total Misses:%d", faults);
}

void lru(int pages[],int n, int capacity)
{
    int faults =0;
    int found = 0;
    int time[capacity];
    int frames[capacity];
    for(int i=0;i<capacity;i++)
    {
        time[i]=0;
        frames[i] =-1;
    }
    int lru_index =0;
    int count=0;
    for(int i=0;i<n;i++)
    {
        lru_index=0;
        found=0;
        for(int j=0;j<capacity;j++)
        {
            if(frames[j]==pages[i])
            {
                found=1;
                time[j]=++count;
                break;
            }
        }
        if(!found)
        {
            int min_time = 10e9;
            for(int i=0;i<capacity;i++)
            {
                if(time[i]<min_time)
                {
                    lru_index=i;
                    min_time=time[i];
                }
            }
            frames[lru_index]=pages[i];
            time[lru_index]=++count;
            faults++;
        }
    }

}

int predict(int pages[],int frames[],int n, int index,int capacity)
{
    int res =-1;
    int farthest =index;
    for(int i=0;i<capacity;i++)
    {
        int j;
        for(j=index;j<n;j++)
        {
            if(frames[i]==pages[j])
            {
                if(j>farthest)
                {
                    res =i;
                    farthest = j;
                }
                break;
            }
        }
        if(j==n) return i;
    }
    return (res==0)?0:res;
}

void optimal(int pages[],int n, int capacity)
{
    int frames[capacity],faults=0;
    int found =0;
    for(int i=0;i<capacity;i++) frames[i] = -1;

    for(int i=0;i<n;i++)
    {   
        found =0;
        for(int j=0;j<capacity;j++)
        {
            if(frames[j]==pages[i])
            {
                found =1;
                break;
            }
        }

        if(!found)
        {
            if(i<capacity){
                frames[i]=pages[i];
            }else{
                int j= predict(pages,frames,n,i+1,capacity);
                frames[j] = pages[i];
            }
            faults++;
        }
    }
}

int main()
{
    int n;
    printf("Enter number of pages:");
    scanf("%d",&n);
    printf("Enter the pages:");
    int pages[n];
    for(int i=0;i<n;i++)
    {
        scanf("%d",&pages[i]);
    }
    fcfs(pages,n,3);
}