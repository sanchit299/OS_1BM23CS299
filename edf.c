#include <stdio.h>
#include <stdlib.h>

#define MAX_TASKS 10

typedef struct {
    int id, RT, CT, deadline, release_time;  // RT = Remaining Time, CT = Completion Time
} Process;

// Sort tasks by their absolute deadline (earliest first)
void sorted(Process p[], int n) {
    int i, j;
    for (i = 1; i < n; i++) {
        for (j = 0; j < n - i; j++) {
            if (p[j].deadline > p[j + 1].deadline || (p[j].deadline == p[j + 1].deadline && p[j].id > p[j + 1].id)) {
                Process temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
            }
        }
    }
}

// Earliest Deadline First Scheduling (without using period or next_release)
void EDF(Process p[], int n, int totaltime) {
    // Initialize remaining time (RT) to completion time (CT)
    for (int i = 0; i < n; i++) {
        p[i].RT = p[i].CT;  // Set RT to the execution time initially
        p[i].release_time = 0;  // Assume all tasks are released at time 0
        p[i].deadline = p[i].CT; // Deadline = CT for simplicity (can be adjusted if needed)
    }

    for (int t = 0; t < totaltime; t++) {
        int executed = 0;

        // Sort tasks by their absolute deadline (earliest first)
        sorted(p, n);

        // Execute the task with the earliest deadline
        for (int i = 0; i < n; i++) {
            if (p[i].RT > 0 && p[i].release_time <= t) {  // Task has remaining time to execute and is released
                printf("Time %d: Executing Task %d\n", t, p[i].id);
                p[i].RT--;  // Decrease the remaining time of the task
                executed = 1;

                if (p[i].RT == 0) {  // Task is finished after execution
                    printf("Time %d: Task %d completed\n", t + 1, p[i].id);
                }
                break;  // Task executed, break out of loop
            }
        }

        // If no task was executed, CPU is idle
        if (!executed) {
            printf("Time %d: Idle\n", t);
        }
    }
}

int main() {
    Process p[MAX_TASKS] = {
        {1, 2, 2, 0, 0}, // Task 1: RT=2, CT=2, Deadline=2
        {2, 3, 3, 0, 0}, // Task 2: RT=3, CT=3, Deadline=3
        {3, 1, 1, 0, 0}  // Task 3: RT=1, CT=1, Deadline=1
    };

    int numofTask = 3;
    int TotalTime = 10; // Total simulation time

    EDF(p, numofTask, TotalTime);

    return 0;
}
