#include <stdio.h>
#include <math.h>
#define MAX 10

struct Process {
    int id;
    int bt;
    int period;
    int rt, next_at, deadline ,ct ,tat ,wt;
    int last_finish_time;
    int total_jobs;
};

int gcd(int a , int b){
    return b==0? 0: gcd(b, a%b);
}
int lcm(int a , int b){
    return (b*a)/gcd(a,b);
}
int computeTime(struct Process t[], int n){
    int hp=t[0].period;
    for(int i=0;i<n;i++) hp =lcm(hp, t[i].period);
    return hp;
}
void RMS_Preemptive(struct Process t[], int n) {

    for (int i = 0; i < n; i++) {//Initialize
        t[i].rt = 0;
        t[i].next_at = 0;
        t[i].deadline = t[i].period;
        t[i].ct = t[i].tat = t[i].wt = 0;
        t[i].last_finish_time = 0;
        t[i].total_jobs = 0;
    }
    
    int totalTime = computeTime(t, n);
    int gantt[totalTime];
    for (int i = 0; i < n - 1; i++) // Sort by period (priority)
        for (int j = 0; j < n - i - 1; j++)
            if (t[j].period > t[j + 1].period) {
                struct Process temp = t[j];
                t[j] = t[j + 1];
                t[j + 1] = temp;
            }

    for (int time = 0; time < totalTime; time++) {
        for (int i = 0; i < n; i++) {
            if (time == t[i].next_at) {
                t[i].rt = t[i].bt;
                t[i].deadline = time + t[i].period;
                t[i].next_at += t[i].period;
                t[i].last_finish_time = time;
            }
        }
        int idx = -1;
        for (int i = 0; i < n; i++) 
            if (t[i].rt > 0) {
                idx = i;
                break;
            }
        
        if (idx != -1) {
            gantt[time] = t[idx].id;
            t[idx].rt--;

            if (t[idx].rt == 0) {
                int finish = time + 1;
                t[idx].ct = finish; 
                int tat = finish - (t[idx].last_finish_time);
                int wt = tat - t[idx].bt;
                t[idx].tat += tat;
                t[idx].wt += wt;
                t[idx].total_jobs++;

                if (finish > t[idx].deadline) 
                    printf("Deadline Miss by Process %d at time %d\n",t[idx].id, finish);
            }

        }
        else gantt[time] = -1;
    }

    printf("\nGANTT CHART:\n");
    for (int i = 0; i < totalTime; i++) {
        if (gantt[i] == -1) printf("Idle ");
        else printf("P%d ", gantt[i]);
    }

    printf("\n\nID\tCT\tAVG TAT\tAVG WT\n");
    for (int i = 0; i < n; i++) {
        if (t[i].total_jobs > 0) { // important line
            printf("%d\t%d\t%.2f\t%.2f\n",
                   t[i].id,
                   t[i].ct,
                   (float)t[i].tat / t[i].total_jobs,
                   (float)t[i].wt / t[i].total_jobs);
        }
    }
}

void main() {
    int n;
    struct Process t[MAX];
    printf("Enter number of processes: ");
    scanf("%d", &n);
    float CPU_utilization=0.0;
    printf("Enter BT ,Period : ");
    for (int i = 0; i < n; i++) {
        t[i].id = i;
        printf("\nProcess %d:\n", i);
        scanf("%d", &t[i].bt);
        scanf("%d", &t[i].period);
        CPU_utilization+=(float)t[i].bt/t[i].period;
    }
    float boundUtilization =(float) n* ((float) pow(2.0,(1.0/n)) -1.0);
    printf("CPU Utilization: %.2f, Bound Utilization : %.2f", CPU_utilization,boundUtilization);
    if(CPU_utilization <= boundUtilization) printf("\nValid\n");
    else printf("\nInvalid\n");
    RMS_Preemptive(t, n);
}