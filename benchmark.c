
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define SIZE 1000000

double get_time()
{
    return (double)clock() / CLOCKS_PER_SEC;
}

void cpu_test()
{
    volatile long long sum = 0;
    double start = get_time();

    for (long long i = 0; i < 50000000; i++)
        sum += i;

    double end = get_time();

    printf("\nCPU BENCHMARK\n");
    printf("Calculation result: %lld\n", sum);
    printf("Execution time: %.4f seconds\n", end - start);
}

void memory_test()
{
    double start = get_time();

    int *arr = malloc(SIZE * sizeof(int));

    if (arr == NULL) {
        printf("Memory allocation failed!\n");
        return;
    }

    for (int i = 0; i < SIZE; i++)
        arr[i] = i;

    double end = get_time();

    printf("\nMEMORY BENCHMARK\n");
    printf("Allocated memory: %zu bytes\n",
           (size_t)SIZE * sizeof(int));
    printf("Allocation and initialization time: %.4f seconds\n",
           end - start);

    free(arr);
    printf("Memory released successfully.\n");
}

void io_test()
{
    FILE *fp;
    char buffer[256];
    double start = get_time();

    fp = fopen("benchmark_test.txt", "w");

    if (fp == NULL) {
        perror("File open failed");
        return;
    }

    for (int i = 0; i < 100000; i++)
        fprintf(fp, "Operating Systems Benchmark Test\n");

    fclose(fp);

    fp = fopen("benchmark_test.txt", "r");

    if (fp == NULL) {
        perror("File read failed");
        return;
    }

    while (fgets(buffer, sizeof(buffer), fp) != NULL)
        ;

    fclose(fp);

    double end = get_time();

    printf("\nFILE I/O BENCHMARK\n");
    printf("Lines written and read: 100000\n");
    printf("Total read/write time: %.4f seconds\n", end - start);
    printf("Test file: benchmark_test.txt\n");
}

int main()
{
    int choice;

    while (1) {
        printf("\n=================================\n");
        printf(" LINUX PERFORMANCE BENCHMARK TOOL\n");
        printf("=================================\n");
        printf("1. CPU Benchmark\n");
        printf("2. Memory Benchmark\n");
        printf("3. File I/O Benchmark\n");
        printf("4. Run All Benchmarks\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1) {
            printf("Invalid input.\n");
            return 1;
        }

        switch (choice) {
            case 1:
                cpu_test();
                break;
            case 2:
                memory_test();
                break;
            case 3:
                io_test();
                break;
            case 4:
                cpu_test();
                memory_test();
                io_test();
                break;
            case 5:
                printf("Benchmark completed. Goodbye!\n");
                return 0;
            default:
                printf("Please enter a number from 1 to 5.\n");
        }
    }
}
