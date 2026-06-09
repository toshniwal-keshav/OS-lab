#include <stdio.h>

#define max 10
int arr[max][7];

/*
0- at
1- bt
2- ct
3- wt
4- tat
5-done
6-rt
*/

void swap(int j){
    int t[7];
    for(int i=0;i<7;i++){
        t[i]=arr[j][i];
        arr[j][i]=arr[j+1][i];
        arr[j+1][i]=t[i];
    }
}

void sort(int n){ //on basis of AT
    for(int i=0;i<n-1;i++){
        for(int j=0;j<n-1-i;j++){
            if(arr[j][0] > arr[j+1][0])
                swap(j);
        }
    }
}

void RoundRobin(int n){
    int done = 0, t = 0, last = -1;
    int q;
    float awt = 0.0, atat = 0.0;

    printf("Enter Time Quantum: ");
    scanf("%d", &q);

    while(done < n){
        int found = 0;

        for(int i = 1; i <= n; i++){
            int idx = (last + i) % n;

            if(arr[idx][5] != 1 && arr[idx][0] <= t){

                if(arr[idx][6] > q){
                    arr[idx][6] -= q;
                    t += q;
                }
                else{
                    t += arr[idx][6];
                    arr[idx][2] = t;
                    arr[idx][4] = arr[idx][2] - arr[idx][0];
                    arr[idx][3] = arr[idx][4] - arr[idx][1];
                    arr[idx][5] = 1;
                    arr[idx][6] = 0;

                    awt += arr[idx][3];
                    atat += arr[idx][4];
                    done++;
                }

                last = idx;
                found = 1;
                break;
            }
        }

        if(found == 0) t++;
    }

    awt /= n;
    atat /= n;

    printf("AWT = %.2f\nATAT = %.2f", awt, atat);
}

void main(){
    int n;
    printf("Enter number of processes: ");
    scanf("%d",&n);
    for(int i=0;i<n;i++){
        printf("Enter arrival time and burst time for process %d:\n",i);
        scanf("%d",&arr[i][0]);
        scanf("%d",&arr[i][1]);
        arr[i][6]=arr[i][1];
        arr[i][5] = 0;
    }
    sort(n);
    RoundRobin(n);
}