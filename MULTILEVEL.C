#include <stdio.h>
#include <stdlib.h>

#define TIME_QUANTUM 4

typedef struct {
    int pid;
    int arrival_time;
    int burst_time;
    int remaining_time;
    int completion_time;
    int waiting_time;
    int turnaround_time;
} Process;

// Function to perform FCFS Scheduling (Higher Priority)
void fcfs_scheduling(Process queue1[], int n1, int *current_time) {
    printf("\nQueue 1 (FCFS - Higher Priority) Execution Order:\n");

    for (int i = 0; i < n1; i++) {
        if (*current_time < queue1[i].arrival_time)
            *current_time = queue1[i].arrival_time;  // Handle idle CPU time

        queue1[i].completion_time = *current_time + queue1[i].burst_time;
        queue1[i].turnaround_time = queue1[i].completion_time - queue1[i].arrival_time;
        queue1[i].waiting_time = queue1[i].turnaround_time - queue1[i].burst_time;

        printf("P%d -> ", queue1[i].pid);
        *current_time = queue1[i].completion_time;
    }
    printf("End\n");
}

// Function to perform Round Robin Scheduling (Lower Priority)
void round_robin_scheduling(Process queue2[], int n2, int current_time) {
    int completed = 0;
    printf("\nQueue 2 (Round Robin - Lower Priority) Execution Order:\n");

    while (completed < n2) {
        int executed = 0;
        for (int i = 0; i < n2; i++) {
            if (queue2[i].remaining_time > 0) {
                executed = 1;

                if (current_time < queue2[i].arrival_time)
                    current_time = queue2[i].arrival_time;

                printf("P%d -> ", queue2[i].pid);

                if (queue2[i].remaining_time > TIME_QUANTUM) {
                    current_time += TIME_QUANTUM;
                    queue2[i].remaining_time -= TIME_QUANTUM;
                } else {
                    current_time += queue2[i].remaining_time;
                    queue2[i].completion_time = current_time;
                    queue2[i].turnaround_time = queue2[i].completion_time - queue2[i].arrival_time;
                    queue2[i].waiting_time = queue2[i].turnaround_time - queue2[i].burst_time;
                    queue2[i].remaining_time = 0;
                    completed++;
                }
            }
        }
        if (!executed) break;  // Stop if all are completed
    }
    printf("End\n");
}

// Function to display results
void display_results(Process processes[], int n) {
    printf("\nPID\tArrival\tBurst\tCompletion\tTurnaround\tWaiting\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t\t%d\t\t%d\n", processes[i].pid, processes[i].arrival_time,
               processes[i].burst_time, processes[i].completion_time, processes[i].turnaround_time, processes[i].waiting_time);
    }
}

// Main Function
int main() {
    int n, n1 = 0, n2 = 0;
    printf("Enter the total number of processes: ");
    scanf("%d", &n);

    Process queue1[n], queue2[n];  // Separate queues for FCFS and Round Robin

    // Input process details
    for (int i = 0; i < n; i++) {
        int priority;
        printf("\nEnter details for Process %d\n", i + 1);
        printf("Arrival Time: ");
        int arrival;
        scanf("%d", &arrival);
        printf("Burst Time: ");
        int burst;
        scanf("%d", &burst);
        printf("Priority (1 for FCFS - High Priority, 2 for Round Robin - Low Priority): ");
        scanf("%d", &priority);

        if (priority == 1) {
            queue1[n1].pid = i + 1;
            queue1[n1].arrival_time = arrival;
            queue1[n1].burst_time = burst;
            queue1[n1].remaining_time = burst;
            n1++;
        } else {
            queue2[n2].pid = i + 1;
            queue2[n2].arrival_time = arrival;
            queue2[n2].burst_time = burst;
            queue2[n2].remaining_time = burst;
            n2++;
        }
    }

    // Scheduling
    int current_time = 0;
    fcfs_scheduling(queue1, n1, &current_time);
    round_robin_scheduling(queue2, n2, current_time);

    // Display results
    printf("\nFinal Results for Queue 1 (FCFS - High Priority):");
    display_results(queue1, n1);

    printf("\nFinal Results for Queue 2 (Round Robin - Low Priority):");
    display_results(queue2, n2);

    return 0;
}

