#include <stdio.h>
#include <stdlib.h> // Include this header for rand()
#include <omp.h>

#define BUFFER_SIZE 10
int buffer[BUFFER_SIZE];
int count = 0;

void producer() {
    while (1) {
        int item = rand() % 100;
        #pragma omp critical
        {
            if (count < BUFFER_SIZE) {
                buffer[count++] = item;
                printf("Produced: %d\n", item);
            }
        }
    }
}

void consumer() {
    while (1) {
        #pragma omp critical
        {
            if (count > 0) {
                int item = buffer[--count];
                printf("Consumed: %d\n", item);
            }
        }
    }
}

int main() {
    #pragma omp parallel sections
    {
        #pragma omp section
        producer();
        
        #pragma omp section
        consumer();
    }
    return 0;
}
