#include <stdio.h>

/*
0- id 
1 -bt 
2- share
3- wt 
4-tat
5- done
6-rt
*/

int arr[10][7];

int totalTime(int n){
    int tot =0;
    for(int i=0;i<n;i++)
        tot+= arr[i][1];
    return tot;
}
void PSS(int n){
    int t=0,done=0,last=0,q;
    int tot = totalTime(n);
    float awt=0.0, atat=0.0;
    int gantt[tot];
    while(done < n){
        int found =0;
        for(int i=0;i<n;i++){
            int idx = (last +i)%n;
            q = arr[idx][2];
            if(arr[idx][5] != 1){
                gantt[t] = idx;
                if(arr [idx][6] >q){
                    arr[idx][6]- = q;
                    t+= q; 
                }
                else{
                    t+= arr[idx][6];
                    arr[idx][6] =0;
                    arr[idx][5] =1;
                    arr[idx][4] = t ;
                    arr[idx][3] = arr[idx][4] - arr[idx][1];
                    awt+= arr[idx][3];
                    atat+=arr[idx][4];
                    done++;
                }
                last = idx;
                found =1;
                break;
            }
        }
        if(found ==0)
            gantt[t++] = -1; // Idle
    }
    printf("\nGANTT CHART:\n");
    for(int i=0;i<tot;i++){
        if(gantt[i] == -1) printf("Idle ");
        else printf("P%d ", arr[gantt[i]][0]);
    }
        awt/= n;
        atat/= n;
        printf("\n\t TAT\t WT\n");
        for(int i=0;i<n;i++) 
            printf("P%d:\t%.2f\t%.2f\n", arr[i][0], (float)arr[i][4], (float)arr[i][3]);
        printf("\nAverage TAT: %.2f\nAverage WT: %.2f\n", awt, atat);
    
}

int main(){
    int n;
    printf("Enter number of processes: ");
    scanf("%d",&n);
    for(int i=0;i<n;i++){
        printf("Enter id, burst time and share for process %d:\n",i);
        scanf("%d",&arr[i][0]);
        scanf("%d",&arr[i][1]);
        scanf("%d",&arr[i][2]);
        arr[i][6] = arr[i][1]; // Remaining time initialized to burst time
    }
    PSS(n);
}
