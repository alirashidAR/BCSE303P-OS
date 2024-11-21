#include<stdio.h>
#include<stdlib.h>

int predict(int pages[], int frames[],int index, int n, int capacity)
{
    int res =-1;
    int farthest = index;
    for(int i=0;i<capacity;i++)
    {
        int j;
        for(j=index;j<n;j++)
        {
            if(frames[i]==pages[j])
            {
                if(j>farthest)
                {
                    farthest =j;
                    res =i;
                }
            }
            break;
        }
        if(j==n) return i;
    }
    return (res==-1)?0:res;
}

void optimal(int pages[], int capacity,int n)
{
    int frames[capacity];
    int faults =0;
    for(int i=0;i<capacity;i++) frames[i] =-1;
    int found =0;
    for(int i=0;i<n;i++)
    {
        int found =0;
        for(int j=0;j<capacity;j++)
        {
            if(pages[i]==frames[j])
            {
                found =1;
                break;
            }
        }

        if(!found)
        {
            if(i<capacity) frames[i] = pages[i];
            else{
                int j = predict(pages,frames,i+1,n,capacity);
                frames[j] = pages[i];
            }
            faults++;
        }
  printf("Frames: ");
        for(int j=0;j<capacity;j++){
            if(frames[j]!=-1) printf("%d ", frames[j]);
            else printf("- ");
        }
        printf("\n");
    }
    printf("Total Page Faults (Optimal): %d\n", faults);
}

int main() {
    int pages[] = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2};
    int n = sizeof(pages) / sizeof(pages[0]);
    int capacity = 3;

    printf("\n OPTIMAL:\n");
    optimal(pages, capacity, n);
    
    return 0;
}