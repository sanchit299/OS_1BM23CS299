#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> // for sleep()

#define SIZE 5

int buffer[SIZE];
int in = 0, out = 0;
int empty = SIZE;  // semaphore: counts empty slots
int full = 0;      // semaphore: counts full slots
int mutex = 1;     // binary semaphore for mutual exclusion

void wait(int *s) {
    while (*s <= 0); // busy wait
    (*s)--;  // decrement semaphore value
}

void signal(int *s) {
    (*s)++;  // increment semaphore value
}

void produce(int item) {
    wait(&empty);  // wait for an empty slot
    wait(&mutex);  // enter critical section

    buffer[in] = item;
    printf("Produced: %d at %d\n", item, in);
    in = (in + 1) % SIZE;

    signal(&mutex);  // leave critical section
    signal(&full);   // signal that there is a full slot
}

void consume() {
    wait(&full);  // wait for a full slot
    wait(&mutex); // enter critical section

    int item = buffer[out];
    printf("Consumed: %d from %d\n", item, out);
    out = (out + 1) % SIZE;

    signal(&mutex);  // leave critical section
    signal(&empty);   // signal that there is an empty slot
}

int main() {
    int item = 1;

    // Simulate producer and consumer running automatically
    while (1) {
        produce(item);  // produce an item
        item++;         // increment item for next production
        sleep(1);       // simulate time taken to produce an item

        consume();      // consume an item
        sleep(1);       // simulate time taken to consume an item
    }

    return 0;
}

// int main() {
//     int choice, item;

//     while (1) {
//         printf("\n1. Produce\n2. Consume\n3. Exit\nChoose: ");
//         scanf("%d", &choice);

//         switch (choice) {
//             case 1:
//                 printf("Enter item to produce: ");
//                 scanf("%d", &item);
//                 produce(item);
//                 break;
//             case 2:
//                 consume();
//                 break;
//             case 3:
//                 return 0;
//             default:
//                 printf("Invalid choice.\n");
//         }
//     }
// }
