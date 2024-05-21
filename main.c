#include <stdio.h>

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

int main() {
    int n = 4;
    int at[] = {0, 6, 7, 9}; //arrival time
    int bt[] = {10, 8, 4, 5}; //burst time
    
    // int gantt_ct[100] = {0}; 
    // int index = 0;
    printf("FCFS Scheduling Algorithm:\n");
    calculateFCFS(n, at, bt);

   

    
//     printf("\nGantt Chart:\n");
//     printf(" ");
//     for (int i = 0; i < index; i++) {
//     int diff;
//     if (i == 0) {
//         diff = gantt_ct[i];
//     } else {
//         diff = gantt_ct[i] - gantt_ct[i - 1];
//     }
//     for (int j = 0; j < diff; j++) {
//         printf("-");
//     }
//     printf(" ");
//     }
 
//     printf("\n");
//     for (int i = 0; i < index; i++) {
//     printf("%d", gantt_ct[i]);
//     int spaces;
//     if (i == 0) {
//         spaces = gantt_ct[i] - 1;
//     } else {
//         spaces = gantt_ct[i] - gantt_ct[i - 1] - 1;
//     }
//     for (int j = 0; j < spaces; j++) {
//         printf(" ");
//     }
//     printf(" ");
// }

//     printf("\n");

    return 0;
}
