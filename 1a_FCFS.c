#include <stdio.h>

#define max 10
int arr[max][5];

/*
0- at
1- bt
2- ct
3- wt
4- tat
*/

void swap(int j){
    int t[5];
    for(int i=0;i<5;i++){
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

void fcfs(int n){
    int t=0;
    float awt=0, atat=0;

    for(int i=0;i<n;i++){
        if(t < arr[i][0]) t = arr[i][0];
        arr[i][3] = t - arr[i][0]; // WT
        arr[i][2] = t + arr[i][1]; // CT
        arr[i][4] = arr[i][2] - arr[i][0]; // TAT

        t += arr[i][1];
        awt += arr[i][3];
        atat += arr[i][4];
    }
    awt /= n;
    atat /= n;
    printf("AWT = %.2f\nATAT = %.2f\n", awt, atat);
}

void main(){
    int n;
    printf("Enter number of processes: ");
    scanf("%d",&n);
    for(int i=0;i<n;i++){
        printf("Enter arrival time and burst time for process %d:\n",i);
        scanf("%d",&arr[i][0]);
        scanf("%d",&arr[i][1]);
    }
    sort(n);
    fcfs(n);
}