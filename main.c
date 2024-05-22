#include <stdio.h>
#include <stdbool.h>


void calculateFCFS(int n, int at[], int bt[]) {
   int ct[4]; //completion time
    int Tt[4]; //turnaround time
    int wt[4]; //waiting time

    int current_time = 0;
    float total_Tt = 0; //total turnaround time
    float total_wt = 0; //total waiting time

    printf("+--------+--------+-------+-----------+-----------+--------+\n");
    printf("| Process| Arrival| Burst | Completion| Turnaround| Waiting|\n");
    printf("+--------+--------+-------+-----------+-----------+--------+\n");

    for (int i = 0; i < n; i++) {
        if (current_time < at[i]) {
            current_time = at[i];
        }
        printf("| P%-6d| %-7d| %-6d|", i + 1, at[i], bt[i]);
        ct[i] = current_time + bt[i];
        Tt[i] = ct[i] - at[i];
        wt[i] = Tt[i] - bt[i];
        total_Tt += Tt[i];
        total_wt += wt[i];
        printf(" %-10d| %-10d| %-7d|\n", ct[i], Tt[i], wt[i]);
        current_time = ct[i];
    }

    printf("+--------+--------+-------+-----------+-----------+--------+\n");

    printf("Average Turnaround Time: %.2f\n", total_Tt / n);
    printf("Average Waiting Time: %.2f\n", total_wt / n);
}
void calculateSJF(int n, int at[], int bt[]) {
    int ct[4]; //completion time
    int Tt[4]; //turnaround time
    int wt[4]; //waiting time
    int completed[4] = {0}; //track if a process is completed

    int current_time = 0;
    float total_Tt = 0; //total turnaround time
    float total_wt = 0; //total waiting time

    printf("+--------+--------+-------+-----------+-----------+--------+\n");
    printf("| Process| Arrival| Burst | Completion| Turnaround| Waiting|\n");
    printf("+--------+--------+-------+-----------+-----------+--------+\n");

    for (int count = 0; count < n; count++) {
        int shortest = -1;
        for (int i = 0; i < n; i++) {
            if (at[i] <= current_time && !completed[i]) {
                if (shortest == -1 || bt[i] < bt[shortest]) {
                    shortest = i;
                }
            }
        }

        if (shortest == -1) {
            current_time++;
            count--;
            continue;
        }

        int i = shortest;
        completed[i] = 1;

        printf("| P%-6d| %-7d| %-6d|", i + 1, at[i], bt[i]);
        ct[i] = current_time + bt[i];
        Tt[i] = ct[i] - at[i];
        wt[i] = Tt[i] - bt[i];
        total_Tt += Tt[i];
        total_wt += wt[i];
        printf(" %-10d| %-10d| %-7d|\n", ct[i], Tt[i], wt[i]);
        current_time = ct[i];
    }

    printf("+--------+--------+-------+-----------+-----------+--------+\n");

    printf("Average Turnaround Time: %.2f\n", total_Tt / n);
    printf("Average Waiting Time: %.2f\n", total_wt / n);
}
void calculateRR(int n, int at[], int bt[], int quantum) {
    int remaining_bt[4];
    int ct[4]; //completion time
    int Tt[4]; //turnaround time
    int wt[4]; //waiting time

    for (int i = 0; i < n; i++) {
        remaining_bt[i] = bt[i];
    }

    int current_time = 0;
    float total_Tt = 0; //total turnaround time
    float total_wt = 0; //total waiting time
    bool done;

    printf("+--------+--------+-------+-----------+-----------+--------+\n");
    printf("| Process| Arrival| Burst | Completion| Turnaround| Waiting|\n");
    printf("+--------+--------+-------+-----------+-----------+--------+\n");

    while (1) {
        done = true;

        for (int i = 0; i < n; i++) {
            if (remaining_bt[i] > 0) {
                done = false;

                if (remaining_bt[i] > quantum) {
                    current_time += quantum;
                    remaining_bt[i] -= quantum;
                } else {
                    current_time += remaining_bt[i];
                    ct[i] = current_time;
                    Tt[i] = ct[i] - at[i];
                    wt[i] = Tt[i] - bt[i];
                    total_Tt += Tt[i];
                    total_wt += wt[i];
                    remaining_bt[i] = 0;

                    printf("| P%-6d| %-7d| %-6d| %-10d| %-10d| %-7d|\n", i + 1, at[i], bt[i], ct[i], Tt[i], wt[i]);
                }
            }
        }

        if (done) {
            break;
        }
    }

    printf("+--------+--------+-------+-----------+-----------+--------+\n");

    printf("Average Turnaround Time: %.2f\n", total_Tt / n);
    printf("Average Waiting Time: %.2f\n", total_wt / n);
}


int main() {
    int n = 4;
    int at[] = {0, 6, 7, 9}; //arrival time
    int bt[] = {10, 8, 4, 5}; //burst time
    int quantum = 3;
    
    // int gantt_ct[100] = {0}; 
    // int index = 0;
    printf("FCFS Scheduling Algorithm:\n");
    calculateFCFS(n, at, bt);

    printf("\nSJF Scheduling Algorithm:\n");
    calculateSJF(n, at, bt);

    printf("\nRound Robin Scheduling Algorithm:\n");
    calculateRR(n, at, bt, quantum);


    return 0;
}
