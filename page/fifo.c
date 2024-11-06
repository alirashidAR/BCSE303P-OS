#include<stdio.h>

void fifo(int pages[], int n, int capacity){
    int frames[capacity], front =0, faults=0;
    for(int i=0;i<capacity;i++){
        frames[i] =-1;
    }

    for(int i=0;i<n;i++){
        int found = 0;
        for(int j=0;j<capacity;j++)
        {
            if(frames[j]==pages[i])
            {
                found =1;
                break;
            }
        }

        if(!found){
            frames[front] = pages[i];
            front =  (front+1)%capacity;
            faults++;
        }
        printf("Frames: ");
        for (int j = 0; j < capacity; j++) {
            if (frames[j] != -1) printf("%d ", frames[j]);
            else printf("- ");
        }
        printf("\n");
    }
    printf("Total Page Faults (FIFO): %d\n", faults);
}

int main() {
    int pages[] = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2};
    int n = sizeof(pages) / sizeof(pages[0]);
    int capacity = 3;

    printf("\nFIFO:\n");
    fifo(pages, n, capacity);
    
    return 0;
}
