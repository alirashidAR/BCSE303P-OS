#include<stdio.h>
#include<limits.h>

void lru(int pages[], int n, int capacity){
    int frames[capacity], time[capacity],faults=0, count =0;

    for(int i=0;i<capacity;i++) frames[i]=-1;

    for(int i=0;i<n;i++)
    {
        int found =0, lru_index =0;
        for(int j=0;j<capacity;j++){
            if(frames[j] == pages[i]){
                found=1;
                time[j] = ++count;
                break;
            }
        }

        if(!found){
            int min_time = INT_MAX;
            for(int j =0;j<capacity;j++){
                if(time[j]<min_time){
                    min_time=time[j];
                    lru_index =j;
                }
            }
            frames[lru_index] = pages[i];
            time[lru_index] = ++count;
            faults++;
        }
        printf("Frames: ");
        for(int j=0;j<capacity;j++){
            if(frames[j]!=-1) printf("%d ", frames[j]);
            else printf("- ");
        }
        printf("\n");
    }

    printf("Total Page Faults (LRU): %d\n", faults);
}


int main() {
    int pages[] = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2};
    int n = sizeof(pages) / sizeof(pages[0]);
    int capacity = 3;

    printf("\nFIFO:\n");
    lru(pages, n, capacity);
    
    return 0;
}
