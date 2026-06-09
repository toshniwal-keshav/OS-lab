#include <stdio.h>
#include <stdbool.h>
#define max_P 10
#define max_R 10
int n, m;
int allocation[max_P][max_R];
int max[max_P][max_R];
int need[max_P][max_R];
int available[max_R];

bool isSafe(){
    int safeSeq[max_P];
    bool finish[max_P] = {false};
    int work[max_R];
    for (int i = 0; i < n; i++)
        finish[i] = false;
// Calculate Need matrix
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            need[i][j] = max[i][j] - allocation[i][j];
// Initialize work = available
    for (int i = 0; i < m; i++)
        work[i] = available[i];

    int count = 0;
    while (count < n){
        bool found = false;
        for (int i = 0; i < n; i++) {
            if (!finish[i]){
                bool canFinish = true;
                for (int j = 0; j < m; j++) {
                    if (need[i][j] > work[j]) {
                        canFinish = false;
                        break;
                    }
                }
                if (canFinish){
                    for (int k = 0; k < m; k++)
                        work[k] += allocation[i][k];
                    safeSeq[count++] = i;
                    finish[i] = true;
                    found = true;
                }
            }
        }
        if (!found) break; // No suitable process found -> unsafe state
    }
    bool safe = true;
    for (int i = 0; i < n; i++){   
        if (!finish[i]){   
            safe = false;
            break;
        }   
    }

    if (safe) {
        printf("\nSystem is in a safe state.\nSafe sequence is: ");
        for (int i = 0; i < n; i++) {
            printf("P%d", safeSeq[i]);
            if (i != n - 1) printf(" -> ");
        }
        printf("\n");
    }
    else printf("\nSystem is NOT in a safe state. Deadlock may occur.\n");
    return safe;
}
int main(){
    bool safe;
    printf("Enter number of processes: ");
    scanf("%d", &n);
    printf("Enter number of resources: ");
    scanf("%d", &m);
    printf("Enter Allocation Matrix:\n");
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            scanf("%d", &allocation[i][j]);

    printf("Enter Maximum Demand Matrix:\n");
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            scanf("%d", &max[i][j]);

    printf("Enter Available Resources:\n");
    for (int i = 0; i < m; i++)
        scanf("%d", &available[i]);

    safe = isSafe();
    int req = 1;
    while(safe){
        printf("\nFor new request , enter 1 lest enter zero:");
        scanf("%d",&req);
        if(!req) break;
        printf("Enter process having new request:");
        int reqP;
        scanf("%d",&reqP);
        printf("Enter Request for all resource of process %d:\n",reqP);
        for(int i=0;i<m;i++) {
            int x;
            scanf("%d",&x);
            allocation[reqP][i] += x;
            available[i] -= x;
        }
        safe = isSafe();
    }
    return 0;
}