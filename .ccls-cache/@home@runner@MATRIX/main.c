#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void quickSort(long arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

int partition(long arr[], int low, int high) {
    long pivot = arr[high];
    int i = (low - 1);
    for (int j = low; j <= high - 1; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

void shellSort(long arr[], int n) {
    for (int gap = n / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; i += 1) {
            long temp = arr[i];
            int j;
            for (j = i; j >= gap && arr[j - gap] > temp; j -= gap)
                arr[j] = arr[j - gap];
            arr[j] = temp;
        }
    }
}

void insertionSort(long arr[], int n) {
    int i, key, j;
    for (i = 1; i < n; i++) {
        key = arr[i];
        j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

void swap(long *a, long *b) {
    long temp = *a;
    *a = *b;
    *b = temp;
}

void generateRandomArray(long arr[], int size, long minVal, long maxVal) {
    srand(time(NULL));
    for (int i = 0; i < size; i++) {
        arr[i] = rand() % (maxVal - minVal + 1) + minVal;
    }
}

void printArray(long arr[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%ld ", arr[i]);
    }
    printf("\n");
}

int main() {
    int sizes[] = {20, 1000, 4000, 10000, 40000, 500000};
    long minVal = 10000, maxVal = 80000;

    for (int i = 0; i < sizeof(sizes) / sizeof(sizes[0]); i++) {
        int size = sizes[i];
        long *arr = (long *)malloc(size * sizeof(long));
        generateRandomArray(arr, size, minVal, maxVal);

        printf("Array size: %d\n", size);
        if (size < 40) {
            printf("Before sorting: ");
            printArray(arr, size);
        }

        clock_t start = clock();
        quickSort(arr, 0, size - 1);
        clock_t end = clock();
        double time_spent = ((double)(end - start)) / CLOCKS_PER_SEC;
        printf("Quick Sort: Time taken: %f seconds\n", time_spent);

        start = clock();
        shellSort(arr, size);
        end = clock();
        time_spent = ((double)(end - start)) / CLOCKS_PER_SEC;
        printf("Shell Sort: Time taken: %f seconds\n", time_spent);

        start = clock();
        insertionSort(arr, size);
        end = clock();
        time_spent = ((double)(end - start)) / CLOCKS_PER_SEC;
        printf("Insertion Sort: Time taken: %f seconds\n", time_spent);

        if (size < 40) {
            printf("After sorting: ");
            printArray(arr, size);
        }
        printf("\n");

        free(arr);
    }

    return 0;
}
