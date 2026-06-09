#include <stdio.h>
#define MAX 100

void resetBlocks(int original[], int copy[], int size)
{
    for (int i = 0; i < size; i++)
        copy[i] = original[i];
}

void initializeAllocation(int allocation[], int n)
{
    for (int i = 0; i < n; i++)
        allocation[i] = -1;
}

void displayAllocation( int allocation[],int processSize[], int n){
    printf("Process No.\tProcess Size\tBlock No.\n");
    for (int i = 0; i < n; i++)
    {
        printf("%d\t\t%d\t\t", i + 1, processSize[i]);
        if (allocation[i] != -1)
            printf("%d\n", allocation[i] + 1);
        else printf("Not Allocated\n");
    }
}

void firstFit(int blockSize[], int m, int processSize[], int n){
    int allocation[MAX];
    initializeAllocation(allocation, n);

    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            if (blockSize[j] >= processSize[i]){
                allocation[i] = j;
                blockSize[j] -= processSize[i];
                break;
            }

    printf("\nFirst Fit\n");
    displayAllocation( allocation, processSize, n);
}

void bestFit(int blockSize[], int m, int processSize[], int n){
    int allocation[MAX];
    initializeAllocation(allocation, n);

    for (int i = 0; i < n; i++){
        int bestIndex = -1;

        for (int j = 0; j < m; j++)
        {
            if (blockSize[j] >= processSize[i])
                if (bestIndex == -1 || blockSize[j] < blockSize[bestIndex])
                    bestIndex = j;
        }

        if (bestIndex != -1){
            allocation[i] = bestIndex;
            blockSize[bestIndex] -= processSize[i];
        }
    }
    printf("\nBest Fit\n");
    displayAllocation( allocation, processSize, n);
}

void worstFit(int blockSize[], int m, int processSize[], int n){
    int allocation[MAX];
    initializeAllocation(allocation, n);

    for (int i = 0; i < n; i++){
        int worstIndex = -1;
        for (int j = 0; j < m; j++)
        {
            if (blockSize[j] >= processSize[i])
                if (worstIndex == -1 || blockSize[j] > blockSize[worstIndex])
                    worstIndex = j;
        }

        if (worstIndex != -1){
            allocation[i] = worstIndex;
            blockSize[worstIndex] -= processSize[i];
        }
    }
    printf("\nWorst Fit\n");
    displayAllocation(allocation, processSize, n);
}

int main(){
    int m, n;
    int originalBlockSize[MAX];
    int blockSize[MAX];
    int processSize[MAX];

    printf("Enter number of memory blocks: ");
    scanf("%d", &m);

    printf("Enter sizes of %d memory blocks:\n", m);
    for (int i = 0; i < m; i++)
        scanf("%d", &originalBlockSize[i]);

    printf("Enter number of processes: ");
    scanf("%d", &n);

    printf("Enter sizes of %d processes:\n", n);
    for (int i = 0; i < n; i++)
        scanf("%d", &processSize[i]);

    resetBlocks(originalBlockSize, blockSize, m);
    firstFit(blockSize, m, processSize, n);

    resetBlocks(originalBlockSize, blockSize, m);
    bestFit(blockSize, m, processSize, n);

    resetBlocks(originalBlockSize, blockSize, m);
    worstFit(blockSize, m, processSize, n);

    return 0;
}
