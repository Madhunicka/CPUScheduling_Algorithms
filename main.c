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
    int ct[4]; // completion time
    int Tt[4]; // turnaround time
    int wt[4]; // waiting time
    int completed[4] = {0}; // track if a process is completed

    int current_time = 0;
    float total_Tt = 0; // total turnaround time
    float total_wt = 0; // total waiting time

    printf("+--------+--------+-------+-----------+-----------+--------+\n");
    printf("| Process| Arrival| Burst | Completion| Turnaround| Waiting|\n");
    printf("+--------+--------+-------+-----------+-----------+--------+\n");

    for (int count = 0; count < n; count++) {
        int shortest = -1;
        for (int i = 0; i < n; i++) {
            if (at[i] <= current_time && !completed[i]) {
                //if next CPU burst are same select the process with the smallest arrival time
                if (shortest == -1 || bt[i] < bt[shortest] || (bt[i] == bt[shortest] && at[i] < at[shortest])) {
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
        //total turnaround time
        total_Tt += Tt[i];
        //total waiting time
        total_wt += wt[i];
        printf(" %-10d| %-10d| %-7d|\n", ct[i], Tt[i], wt[i]);
        current_time = ct[i];
    }

    printf("+--------+--------+-------+-----------+-----------+--------+\n");

    printf("Average Turnaround Time: %.2f\n", total_Tt / n);
    printf("Average Waiting Time: %.2f\n", total_wt / n);
}
void calculateRR(int n, int at[], int bt[], int quantum) {
    int remaining_bt[4];  // array to keep track of remaining burst times for each process
    int ct[4];  // array to store completion time for each process
    int Tt[4];  // array to store turnaround time for each process
    int wt[4];  // array to store waiting time for each process
    int queue[4];  // queue to maintain the order of process execution
    int front = 0, rear = 0;  // queue pointers
    int process_count = 0;

    // Initialize remaining burst times
    for (int i = 0; i < n; i++) {
        remaining_bt[i] = bt[i];
    }

    int current_time = 0;  // current time in the scheduling simulation
    float total_Tt = 0;  // total turnaround time for all processes
    float total_wt = 0;  // total waiting time for all processes

    // Add processes to the queue based on arrival times
    for (int i = 0; i < n; i++) {
        if (at[i] <= current_time) {
            queue[rear++] = i;
        }
    }

    // Print table headers
    printf("+--------+--------+-------+-----------+-----------+--------+\n");
    printf("| Process| Arrival| Burst | Completion| Turnaround| Waiting|\n");
    printf("+--------+--------+-------+-----------+-----------+--------+\n");

    while (process_count < n) {
        if (front != rear) {
            int i = queue[front++ % n];

            if (remaining_bt[i] > 0) {
                if (remaining_bt[i] > quantum) {
                    current_time += quantum;  // Increment current time by quantum
                    remaining_bt[i] -= quantum;  // Decrease remaining burst time

                    // Add newly arrived processes to the queue
                    for (int j = 0; j < n; j++) {
                        if (at[j] > current_time - quantum && at[j] <= current_time && remaining_bt[j] > 0) {
                            queue[rear++ % n] = j;
                        }
                    }

                    // Re-add the current process to the queue if it's not completed
                    queue[rear++ % n] = i;
                } else {
                    current_time += remaining_bt[i];  // Increment current time by remaining burst time
                    ct[i] = current_time;  // Set completion time for process i
                    Tt[i] = ct[i] - at[i];  // Calculate turnaround time for process i
                    wt[i] = Tt[i] - bt[i];  // Calculate waiting time for process i
                    total_Tt += Tt[i];  // Accumulate total turnaround time
                    total_wt += wt[i];  // Accumulate total waiting time
                    remaining_bt[i] = 0;  // Process i is now done
                    process_count++;  // Increment the number of completed processes

                    // Print process information
                    printf("| P%-6d| %-7d| %-6d| %-10d| %-10d| %-7d|\n", i + 1, at[i], bt[i], ct[i], Tt[i], wt[i]);
                }
            }
        } else {
            current_time++;
        }
    }

    // Print table footer
    printf("+--------+--------+-------+-----------+-----------+--------+\n");

    // Print average turnaround time and waiting time
    printf("Average Turnaround Time: %.2f\n", total_Tt / n);
    printf("Average Waiting Time: %.2f\n", total_wt / n);
}


int main() {
    int n = 4;
    int at[] = {0, 6, 7, 9}; //arrival time
    int bt[] = {10, 8, 4, 5}; //burst time
    int quantum = 4;
    
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
