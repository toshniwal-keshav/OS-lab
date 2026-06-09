#include <stdio.h>

#define max 10
int arr[max][6];

/*
0- at
1- bt
2- ct
3- wt
4- tat
5-done
*/

void swap(int j){
    int t[6];
    for(int i=0;i<=5;i++){
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

void sjf(int n){
    int done =0;
    int t=0;
    float awt =0.0, atat=0.0;
    while(n>done){
        int id=-1, minBT=99999;
        for(int i=0;i<n;i++){
            if(arr[i][5] != 1 && arr[i][0] <= t){
                if(arr[i][1] < minBT){
                minBT=arr[i][1];
                id =i;
                }
                else if (arr[i][1] == minBT)
                    if (arr[i][0] < arr[id][0]) id = i;

            }
        }

        if(id !=-1){
            arr[id][3]=t-arr[id][0];
            arr[id][2]=t+ arr[id][1];
            arr[id][4]= arr[id][2]-arr[id][0];
            arr[id][5]=1;
            awt+= arr[id][3];
            atat+=arr[id][4];
            t= arr[id][2];
            done++;

        }
        else t++;
    }
    atat/=n;
    awt/=n;

    printf("AWT = %.2f \nATAT = %.2f",awt,atat);
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
    sjf(n);
}