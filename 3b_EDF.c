#include <stdio.h>

#define MAX 10

struct Process {
    int id;
    int bt;
    int period;

    int rt;
    int next_at;
    int deadline;
    int arrival_time;

    int ct;
    int tat;
    int wt;

    int total_jobs;
};

int gcd(int a , int b){
    return b==0? a: gcd(b, a%b);
}
int lcm(int a , int b){
    return (b*a)/gcd(a,b);
}
int computeTime(struct Process t[], int n){
    int hp=t[0].period;
    for(int i=0;i<n;i++) hp =lcm(hp, t[i].period);
    return hp;
}
void EDF_Preemptive(struct Process t[], int n) {

    for (int i = 0; i < n; i++) {
        t[i].rt = 0;
        t[i].next_at = 0;
        t[i].deadline = t[i].period;
        t[i].arrival_time = 0;
        t[i].ct = t[i].tat = t[i].wt = 0;
        t[i].total_jobs = 0;
    }
    int totalTime = computeTime(t, n);
    int gantt[totalTime];
    for (int time = 0; time < totalTime; time++) {
        for (int i = 0; i < n; i++) {
            if (time == t[i].next_at) {
                if(t[i].rt > 0) 
                     printf("Deadline Miss by Process %d at time %d\n",t[idx].id, finish);
                t[i].rt = t[i].bt;
                t[i].arrival_time = time;
                t[i].deadline = time + t[i].period;
                t[i].next_at += t[i].period;
            }
        }

        int idx = -1;
        int earliest_deadline = 1000;
        for (int i = 0; i < n; i++) 
            if (t[i].rt > 0 && t[i].deadline < earliest_deadline) {
                earliest_deadline = t[i].deadline;
                idx = i;
            }

        if (idx != -1) {
            gantt[time] = t[idx].id;
            t[idx].rt--;

            if (t[idx].rt == 0) {
                int finish = time + 1;
                t[idx].ct = finish;

                t[idx].tat += finish - t[idx].arrival_time;
                t[idx].wt += tat - t[idx].bt;

                t[idx].total_jobs++;
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
    for (int i = 0; i < n; i++)
        if (t[i].total_jobs > 0)
            printf("%d\t%d\t%.2f\t%.2f\n",
                   t[i].id,
                   t[i].ct,
                   (float)t[i].tat / t[i].total_jobs,
                   (float)t[i].wt / t[i].total_jobs);
}

void main() {
    int n;
    struct Process t[MAX];

    printf("Enter number of processes: ");
    scanf("%d", &n);
    printf("Enter BT and Period:\n");
    float CPU_utilization = 0.0;
    for (int i = 0; i < n; i++) {
        t[i].id = i;
        printf("\nProcess %d:\n", i);
        scanf("%d", &t[i].bt);
        scanf("%d", &t[i].period);
        CPU_utilization += (float)t[i].bt / t[i].period;
    }
    printf("\nCPU Utilization: %.2f", CPU_utilization);
    if (CPU_utilization <= 1)  printf("\nSchedulable (Valid)\n");
    else printf("\nNot Schedulable (Invalid)\n");

    EDF_Preemptive(t, n);
}
