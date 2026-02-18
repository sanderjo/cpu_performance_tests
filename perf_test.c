#include <stdio.h>
#include <time.h>
#include <stdint.h>

int main() {
    struct timespec start, current;
    double elapsed = 0;
    uint64_t operations = 0;
    double dummy = 1.0;

    printf("Measuring CPU performance for 0.2 seconds...\n");

    // Get the starting CPU time
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &start);

    // Perform operations until 0.2 seconds have passed
    while (elapsed < 0.2) {
        // High-intensity math operation
        dummy = (dummy + 0.1) * 0.999999;
        operations++;

        // Update current CPU time
        clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &current);
        elapsed = (current.tv_sec - start.tv_sec) + 
                  (current.tv_nsec - start.tv_nsec) / 1000000000.0;
    }

    printf("--- Results ---\n");
    printf("Actual time elapsed: %.6f seconds\n", elapsed);
    printf("Total operations:    %lu\n", operations);
    printf("Performance:         %.2f Million Ops/sec\n", (operations / elapsed) / 1e6);
    
    // Use dummy to prevent the compiler from optimizing the loop away
    if (dummy == 0.0) printf("%f", dummy); 

    return 0;
}

