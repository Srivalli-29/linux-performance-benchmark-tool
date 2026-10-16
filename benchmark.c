
#define _POSIX_C_SOURCE 199309L
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>

#define SIZE 1000000
#define CPU_ITERATIONS 20000000LL
#define IO_LINES 50000
#define REPEATS 3

double now_seconds(void)
{
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return ts.tv_sec + ts.tv_nsec / 1000000000.0;
}

void save_result(const char *test, int run, double seconds,
                 long long metric)
{
    FILE *fp = fopen("benchmark_results.csv", "a");
    if (fp == NULL) {
        perror("Cannot save CSV result");
        return;
    }

    fprintf(fp, "%s,%d,%.6f,%lld\n",
            test, run, seconds, metric);
    fclose(fp);
}

double cpu_test(int run)
{
    volatile long long sum = 0;
    double start = now_seconds();

    for (long long i = 0; i < CPU_ITERATIONS; i++)
        sum += i;

    double elapsed = now_seconds() - start;

    printf("CPU: %.6f seconds | Result: %lld\n",
           elapsed, (long long)sum);
    save_result("CPU", run, elapsed, (long long)sum);
    return elapsed;
}

double memory_test(int run)
{
    double start = now_seconds();
    int *arr = malloc(SIZE * sizeof(int));

    if (arr == NULL) {
        printf("Memory allocation failed.\n");
        return -1.0;
    }

    for (int i = 0; i < SIZE; i++)
        arr[i] = i;

    double elapsed = now_seconds() - start;

    printf("Memory: %.6f seconds | Allocated: %zu bytes\n",
           elapsed, (size_t)SIZE * sizeof(int));

    save_result("Memory", run, elapsed,
                (long long)SIZE * sizeof(int));

    free(arr);
    return elapsed;
}

double io_test(int run)
{
    char buffer[128];
    double start = now_seconds();

    FILE *fp = fopen("benchmark_test.txt", "w");
    if (fp == NULL) {
        perror("Cannot write test file");
        return -1.0;
    }

    for (int i = 0; i < IO_LINES; i++)
        fprintf(fp, "Operating Systems benchmark test %d\n", i);

    if (fclose(fp) != 0) {
        perror("Cannot close test file");
        return -1.0;
    }

    fp = fopen("benchmark_test.txt", "r");
    if (fp == NULL) {
        perror("Cannot read test file");
        return -1.0;
    }

    int lines = 0;
    while (fgets(buffer, sizeof(buffer), fp) != NULL)
        lines++;

    fclose(fp);

    double elapsed = now_seconds() - start;

    printf("File I/O: %.6f seconds | Lines read: %d\n",
           elapsed, lines);
    save_result("FileIO", run, elapsed, lines);
    return elapsed;
}

void run_all(void)
{
    double cpu_total = 0, mem_total = 0, io_total = 0;
    int cpu_count = 0, mem_count = 0, io_count = 0;

    printf("\nRunning %d benchmark rounds...\n", REPEATS);

    for (int r = 1; r <= REPEATS; r++) {
        printf("\n--- Run %d ---\n", r);

        double t = cpu_test(r);
        if (t >= 0) {
            cpu_total += t;
            cpu_count++;
        }

        t = memory_test(r);
        if (t >= 0) {
            mem_total += t;
            mem_count++;
        }

        t = io_test(r);
        if (t >= 0) {
            io_total += t;
            io_count++;
        }
    }

    printf("\n===== AVERAGE RESULTS =====\n");
    if (cpu_count)
        printf("CPU average: %.6f seconds\n",
               cpu_total / cpu_count);
    if (mem_count)
        printf("Memory average: %.6f seconds\n",
               mem_total / mem_count);
    if (io_count)
        printf("File I/O average: %.6f seconds\n",
               io_total / io_count);

    printf("Detailed results saved in benchmark_results.csv\n");
}

int main(void)
{
    int choice;

    FILE *fp = fopen("benchmark_results.csv", "r");
    if (fp == NULL) {
        fp = fopen("benchmark_results.csv", "w");
        if (fp == NULL) {
            perror("Cannot create results file");
            return 1;
        }
        fprintf(fp, "Test,Run,Seconds,Metric\n");
    }
    if (fp != NULL)
        fclose(fp);

    while (1) {
        printf("\n=================================\n");
        printf(" LINUX PERFORMANCE BENCHMARK TOOL\n");
        printf("=================================\n");
        printf("1. CPU Benchmark\n");
        printf("2. Memory Benchmark\n");
        printf("3. File I/O Benchmark\n");
        printf("4. Run All (3 rounds + averages)\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1) {
            printf("Invalid input.\n");
            return 1;
        }

        switch (choice) {
            case 1: cpu_test(1); break;
            case 2: memory_test(1); break;
            case 3: io_test(1); break;
            case 4: run_all(); break;
            case 5:
                printf("Benchmark completed. Goodbye!\n");
                return 0;
            default:
                printf("Choose a number from 1 to 5.\n");
        }
    }
}

