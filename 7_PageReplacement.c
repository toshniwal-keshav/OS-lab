#include <stdio.h>
#include <stdbool.h>
#define MAX 100
// Display Function
void display(int pg, int frames[], int count){
    printf("pg %d -> [", pg);

    for (int i = 0; i < count; i++){
        printf("%d", frames[i]);
        if (i < count - 1)
            printf(" ");
    }
    printf("]\n");
}

void fifo(int pgs[], int n, int capacity){
    int frames[capacity];
    int front = 0, count = 0, faults = 0;
    printf("\nFIFO pg Replacement \n");

    for (int i = 0; i < n; i++){
        bool found = false;
        for (int j = 0; j < count; j++)
            if (frames[j] == pgs[i])
            {
                found = true;
                break;
            }

        if (!found){
            if (count < capacity)
                frames[count++] = pgs[i];
            else{
                frames[front] = pgs[i];
                front = (front + 1) % capacity;
            }
            faults++;
        }
        display(pgs[i], frames, count);
    }
    printf("Total pg Faults (FIFO): %d\n", faults);
}

void lru(int pgs[], int n, int capacity){
    int frames[capacity];
    int count = 0, faults = 0;

    printf("\nLRU pg Replacement \n");
    for (int i = 0; i < n; i++){
        bool found = false;
        for (int j = 0; j < count; j++)
            if (frames[j] == pgs[i]) {
                found = true;
                for (int k = j; k < count - 1; k++)
                    frames[k] = frames[k + 1];
                frames[count - 1] = pgs[i];
                break;
            }

        if (!found){
            if (count < capacity)
                frames[count++] = pgs[i];
            else{
                for (int k = 0; k < capacity - 1; k++)
                    frames[k] = frames[k + 1];
                frames[capacity - 1] = pgs[i];
            }
            faults++;
        }
        display(pgs[i], frames, count);
    }
    printf("Total pg Faults (LRU): %d\n", faults);
}

void optimal(int pgs[], int n, int capacity){
    int frames[capacity];
    int count = 0, faults = 0;
    printf("\nOptimal pg Replacement\n");
    for (int i = 0; i < n; i++){
        bool found = false;
        for (int j = 0; j < count; j++)
            if (frames[j] == pgs[i]){
                found = true;
                break;
            }
        if (!found){
            if (count < capacity)
                frames[count++] = pgs[i];
            else{
                int farthest = -1, index = -1;
                for (int j = 0; j < capacity; j++){
                    int k;
                    for (k = i + 1; k < n; k++) {
                        if (frames[j] == pgs[k])
                            break;
                    }
                    if (k > farthest){
                        farthest = k;
                        index = j;
                    }
                }
                frames[index] = pgs[i];
            }
            faults++;
        }
        display(pgs[i], frames, count);
    }
    printf("Total pg Faults (Optimal): %d\n", faults);
}

int main(){
    int n, capacity;
    int pgs[MAX];

    printf("Enter number of pgs: ");
    scanf("%d", &n);

    printf("Enter pg reference string:\n");
    for (int i = 0; i < n; i++)
        scanf("%d", &pgs[i]);

    printf("Enter number of frames: ");
    scanf("%d", &capacity);

    fifo(pgs, n, capacity);
    lru(pgs, n, capacity);
    optimal(pgs, n, capacity);

    return 0;
}