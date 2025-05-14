#include <stdio.h>

#define N 5

int forks[N] = {1, 1, 1, 1, 1}; // binary semaphores for forks
int mutex = 1; // for critical section

void wait(int *s) {
    while (*s <= 0);
    (*s)--;
}

void signal(int *s) {
    (*s)++;
}

void pickup(int i) {
    wait(&mutex);

    if (forks[i] == 1 && forks[(i + 1) % N] == 1) {
        wait(&forks[i]);
        wait(&forks[(i + 1) % N]);
        printf("Philosopher %d picks up forks %d and %d and starts EATING.\n", i, i, (i + 1) % N);
    } else {
        printf("Philosopher %d can't eat now. One or both forks not available.\n", i);
    }

    signal(&mutex);
}

void putdown(int i) {
    wait(&mutex);

    signal(&forks[i]);
    signal(&forks[(i + 1) % N]);
    printf("Philosopher %d puts down forks %d and %d and starts THINKING.\n", i, i, (i + 1) % N);

    signal(&mutex);
}

void showForks() {
    printf("Fork status: ");
    for (int i = 0; i < N; i++) {
        printf("%d ", forks[i]);
    }
    printf("\n");
}

int main() {
    int choice, id;
    while (1) {
        printf("\n1. Pickup fork\n2. Putdown fork\n3. Show fork status\n4. Exit\nChoose: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                printf("Enter philosopher ID (0-4): ");
                scanf("%d", &id);
                if (id >= 0 && id < N)
                    pickup(id);
                else
                    printf("Invalid ID\n");
                break;
            case 2:
                printf("Enter philosopher ID (0-4): ");
                scanf("%d", &id);
                if (id >= 0 && id < N)
                    putdown(id);
                else
                    printf("Invalid ID\n");
                break;
            case 3:
                showForks();
                break;
            case 4:
                return 0;
            default:
                printf("Invalid choice\n");
        }
    }
}
