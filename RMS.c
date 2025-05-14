#include <stdio.h>
#include <stdlib.h>

#define MAX_TASKS 10

typedef struct {
    int id, period, RT, CT;  // RT = Remaining Time, CT = Completion Time (Execution Time)
} Process;

// Sort tasks based on their period (shorter period means higher priority in RMS)
void sorted(Process p[], int n) {
    int i, j;
    for (i = 1; i < n; i++) {
        for (j = 0; j < n - i; j++) {
            if (p[j].period > p[j + 1].period || (p[j].period == p[j + 1].period && p[j].id > p[j + 1].id)) {
                Process temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
            }
        }
    }
}

// Rate Monotonic Scheduling
void RMS(Process p[], int n, int totaltime) {
    sorted(p, n);  // Sort tasks based on their period

    // Initialize remaining times (RT) and set all tasks to their execution time
    for (int i = 0; i < n; i++) {
        p[i].RT = p[i].CT;  // Set RT to the execution time initially
    }

    for (int t = 0; t < totaltime; t++) {
        int executed = 0;

        // Check for each task and run it if ready
        for (int i = 0; i < n; i++) {
            // Release task at the start of its period (every t % period == 0) and if RT > 0
            if (t % p[i].period == 0 && p[i].RT == 0) {
                p[i].RT = p[i].CT;  // Reset remaining time when a task finishes its period
                printf("Time %d: Task %d released\n", t, p[i].id);
            }

            // If time `t` is a multiple of the task's period and the task still has remaining time
            if (t % p[i].period == 0 && p[i].RT > 0) {
                printf("Time %d: Executing Task %d\n", t, p[i].id);
                p[i].RT--;  // Decrease remaining time of the task
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
        {1, 3, 2, 2}, // Task 1: period=3, RT=2, CT=2
        {2, 5, 2, 2}, // Task 2: period=5, RT=2, CT=2
        {3, 7, 2, 2}  // Task 3: period=7, RT=2, CT=2
    };

    int numofTask = 3;
    int TotalTime = 15; // Total simulation time

    RMS(p, numofTask, TotalTime);

    return 0;
}
