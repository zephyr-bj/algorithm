#include <stdio.h>
#include <stdbool.h>
/*
Comparison of Timing ConstraintsIn the industry, 
we categorize task sets based on this relationship:
1. Implicit: $D = P$ (The most common/simple).
2. Constrained: $D \leq P$ (The task must finish before the next one starts).
3. Arbitrary: No specific relationship between $D$ and $P$.
*/
// Task Function Pointer Type
// In a real system, you might pass a void *params pointer 
// to give the task access to specific data structures or hardware addresses.
typedef void (*TaskJob)(int id);

typedef struct {
    int id;
    int execution_time;
    int period;
    int deadline;
    int remaining_time;
    int current_deadline;
    TaskJob job;        // The "Work" this task does
} Task;

// --- Task Job Definitions ---

void sensorJob(int id) {
    printf(" [Task %d: Reading Temperature Sensor] ", id);
}

void logJob(int id) {
    printf(" [Task %d: Writing to SD Card]        ", id);
}

void alertJob(int id) {
    printf(" [Task %d: Checking System Alerts]    ", id);
}

// --- Scheduler Logic ---

void simulateEDF(Task tasks[], int num_tasks, int total_time) {
    printf("Time | Status | Task  | Job Output\n");
    printf("----------------------------------------------------------\n");

    for (int t = 0; t < total_time; t++) {
        // 1. Arrival & Deadline Miss Check
        for (int i = 0; i < num_tasks; i++) {
            if (tasks[i].remaining_time > 0 && t == tasks[i].current_deadline) {
                printf("\nCRITICAL FAILURE: Task %d missed deadline at %d\n", tasks[i].id, t);
                return;
            }
            if (t % tasks[i].period == 0) {
                tasks[i].remaining_time = tasks[i].execution_time;
                tasks[i].current_deadline = t + tasks[i].deadline;
            }
        }

        // 2. Earliest Deadline First Selection
        int selected_task = -1;
        int min_deadline = 9999;
        for (int i = 0; i < num_tasks; i++) {
            if (tasks[i].remaining_time > 0 && tasks[i].current_deadline < min_deadline) {
                min_deadline = tasks[i].current_deadline;
                selected_task = i;
            }
        }

        // 3. Execution & Callback
        printf("%4d | ", t);
        if (selected_task != -1) {
            printf("RUN    | T%d   |", tasks[selected_task].id);
            
            // Execute the specific job assigned to this task
            tasks[selected_task].job(tasks[selected_task].id);
            
            tasks[selected_task].remaining_time--;
        } else {
            printf("IDLE   | ---  | (Processor Sleep)");
        }
        printf("\n");
    }
}

int main() {
    // Initializing tasks with different function pointers
    Task tasks[] = {
        // ID, Exec, Period, Deadline, Rem, Curr, JobFunction
        {1, 1, 5,  3,  0, 0, sensorJob}, // High urgency, short deadline
        {2, 2, 8,  8,  0, 0, logJob},    // Medium priority
        {3, 1, 12, 12, 0, 0, alertJob}   // Low frequency
    };

    int num_tasks = sizeof(tasks) / sizeof(tasks[0]);
    simulateEDF(tasks, num_tasks, 25);

    return 0;
}
