#include <stdio.h>
#include <time.h>
#include <stdint.h>
#include <pthread.h>
#include <unistd.h>

#define TEST_DURATION 0.2

// Structure to pass data to threads
typedef struct {
    uint64_t operations;
    double dummy_val;
} ThreadData;

// The heavy-duty math function each thread will run
void* cpu_heavy_task(void* arg) {
    ThreadData* data = (ThreadData*)arg;
    struct timespec start, current;
    double elapsed = 0;
    double val = 1.0;
    uint64_t ops = 0;

    clock_gettime(CLOCK_MONOTONIC, &start);

    while (elapsed < TEST_DURATION) {
        val = (val + 0.1) * 0.999999; // Simple math to keep CPU busy
        ops++;

        clock_gettime(CLOCK_MONOTONIC, &current);
        elapsed = (current.tv_sec - start.tv_sec) + 
                  (current.tv_nsec - start.tv_nsec) / 1000000000.0;
    }

    data->operations = ops;
    data->dummy_val = val;
    return NULL;
}

int main() {
    int num_cores = sysconf(_SC_NPROCESSORS_ONLN);
    //num_cores = 20;
    printf("System detected: %d CPU cores\n\n", num_cores);

    // --- TEST 1: SINGLE-CORE ---
    printf("Running Single-Core Test (0.2s)...\n");
    ThreadData single_data = {0, 0};
    cpu_heavy_task(&single_data);
    printf("Single-Core Score: %.2f Million Ops/sec\n\n", (single_data.operations / TEST_DURATION) / 1e6);

    // --- TEST 2: MULTI-CORE ---
    printf("Running Multi-Core Test on %d cores (0.2s)...\n", num_cores);
    pthread_t threads[num_cores];
    ThreadData multi_data[num_cores];
    
    for (int i = 0; i < num_cores; i++) {
        multi_data[i].operations = 0;
        pthread_create(&threads[i], NULL, cpu_heavy_task, &multi_data[i]);
    }

    uint64_t total_multi_ops = 0;
    for (int i = 0; i < num_cores; i++) {
        pthread_join(threads[i], NULL);
        total_multi_ops += multi_data[i].operations;
    }

    double multi_score = (total_multi_ops / TEST_DURATION) / 1e6;
    printf("Multi-Core Total Score: %.2f Million Ops/sec\n", multi_score);
    printf("Multi-Core Speedup: %.2fx faster than single core\n", 
            (double)total_multi_ops / single_data.operations);

    return 0;
}
