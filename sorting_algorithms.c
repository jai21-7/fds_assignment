/*
 * ============================================================
 *  SORTING ALGORITHMS IN C
 *  - Insertion Sort
 *  - Bucket Sort
 *  - Counting Sort
 *  - Radix Sort
 *
 *  To Compile:  gcc sorting_algorithms.c -o sorting
 *  To Run:      ./sorting
 * ============================================================
 */

#include <stdio.h>
#include <string.h>

/* ================================================d============
   HELPER: Print an integer array
   ============================================================ */
void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

/* ============================================================
   HELPER: Print a float array
   ============================================================ */
void printFloatArray(float arr[], int n) {
    for (int i = 0; i < n; i++)
        printf("%.2f ", arr[i]);
    printf("\n");
}


/* ============================================================
   1. INSERTION SORT
   - Pick one element at a time
   - Insert it into its correct position in the sorted part
   - Time:  Best O(n) | Average O(n^2) | Worst O(n^2)
   - Space: O(1)
   ============================================================ */
void insertionSort(int arr[], int n) {
    int i, key, j;

    for (i = 1; i < n; i++) {
        key = arr[i];   /* element to be inserted */
        j   = i - 1;

        /* shift elements greater than key one position to the right */
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;   /* place key at its correct position */
    }
}


/* ============================================================
   2. BUCKET SORT
   - Distribute elements into buckets (ranges)
   - Sort each bucket using insertion sort
   - Concatenate buckets in order
   - Time:  Best/Average O(n+k) | Worst O(n^2)
   - Space: O(n+k)
   - Works best for floats uniformly distributed in [0, 1)
   ============================================================ */
#define BUCKET_COUNT 10

/* Insertion sort for float buckets */
void insertionSortBucket(float arr[], int n) {
    for (int i = 1; i < n; i++) {
        float key = arr[i];
        int   j   = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

void bucketSort(float arr[], int n) {
    float buckets[BUCKET_COUNT][100];   /* each bucket holds up to 100 elements */
    int   bucketSize[BUCKET_COUNT];

    /* initialize all bucket sizes to 0 */
    for (int i = 0; i < BUCKET_COUNT; i++)
        bucketSize[i] = 0;

    /* put each element into the appropriate bucket */
    for (int i = 0; i < n; i++) {
        int idx = (int)(arr[i] * BUCKET_COUNT);   /* e.g., 0.42 * 10 = bucket 4 */
        buckets[idx][bucketSize[idx]] = arr[i];
        bucketSize[idx]++;
    }

    /* sort each non-empty bucket individually */
    for (int i = 0; i < BUCKET_COUNT; i++) {
        if (bucketSize[i] > 1)
            insertionSortBucket(buckets[i], bucketSize[i]);
    }

    /* concatenate all buckets back into the original array */
    int index = 0;
    for (int i = 0; i < BUCKET_COUNT; i++)
        for (int j = 0; j < bucketSize[i]; j++)
            arr[index++] = buckets[i][j];
}


/* ============================================================
   3. COUNTING SORT
   - Count how many times each value appears
   - Use cumulative counts to place elements directly
   - No comparisons needed!
   - Time:  O(n + k)  where k = range of values
   - Space: O(k)
   - Works only for non-negative integers
   ============================================================ */
void countingSort(int arr[], int n) {
    /* Step 1: Find maximum value */
    int max = arr[0];
    for (int i = 1; i < n; i++)
        if (arr[i] > max)
            max = arr[i];

    /* Step 2: Create count array, initialized to 0 */
    int count[max + 1];
    memset(count, 0, sizeof(count));

    /* Step 3: Count occurrences of each element */
    for (int i = 0; i < n; i++)
        count[arr[i]]++;

    /* Step 4: Convert to cumulative (prefix) sums */
    for (int i = 1; i <= max; i++)
        count[i] += count[i - 1];

    /* Step 5: Build the output array (reverse traversal = stable sort) */
    int output[n];
    for (int i = n - 1; i >= 0; i--) {
        output[count[arr[i]] - 1] = arr[i];
        count[arr[i]]--;
    }

    /* Copy sorted output back into original array */
    for (int i = 0; i < n; i++)
        arr[i] = output[i];
}


/* ============================================================
   4. RADIX SORT
   - Sort numbers digit by digit (units → tens → hundreds ...)
   - Uses counting sort at each digit position
   - Time:  O(d * (n + k))  where d = digits, k = base (10)
   - Space: O(n + k)
   - Works only for non-negative integers
   ============================================================ */

/* Helper: find maximum value in array */
int getMax(int arr[], int n) {
    int max = arr[0];
    for (int i = 1; i < n; i++)
        if (arr[i] > max)
            max = arr[i];
    return max;
}

/* Counting sort based on a specific digit position
   exp = 1   → units digit
   exp = 10  → tens digit
   exp = 100 → hundreds digit, and so on */
void countingSortByDigit(int arr[], int n, int exp) {
    int output[n];
    int count[10];
    memset(count, 0, sizeof(count));

    /* count occurrences of each digit at position 'exp' */
    for (int i = 0; i < n; i++) {
        int digit = (arr[i] / exp) % 10;
        count[digit]++;
    }

    /* cumulative count */
    for (int i = 1; i < 10; i++)
        count[i] += count[i - 1];

    /* build output (reverse for stability) */
    for (int i = n - 1; i >= 0; i--) {
        int digit = (arr[i] / exp) % 10;
        output[count[digit] - 1] = arr[i];
        count[digit]--;
    }

    /* copy output back to arr */
    for (int i = 0; i < n; i++)
        arr[i] = output[i];
}

void radixSort(int arr[], int n) {
    int max = getMax(arr, n);

    /* sort by each digit position: units, tens, hundreds, ... */
    for (int exp = 1; max / exp > 0; exp *= 10)
        countingSortByDigit(arr, n, exp);
}


/* ============================================================
   MAIN — Test all four sorting algorithms
   ============================================================ */
int main() {

    /* ---- 1. Insertion Sort ---- */
    printf("============================================\n");
    printf(" 1. INSERTION SORT\n");
    printf("============================================\n");
    int arr1[] = {5, 3, 8, 1, 4, 7, 2, 6};
    int n1 = sizeof(arr1) / sizeof(arr1[0]);
    printf("Before: "); printArray(arr1, n1);
    insertionSort(arr1, n1);
    printf("After:  "); printArray(arr1, n1);
    printf("\n");

    /* ---- 2. Bucket Sort ---- */
    printf("============================================\n");
    printf(" 2. BUCKET SORT\n");
    printf("============================================\n");
    float arr2[] = {0.42, 0.12, 0.78, 0.35, 0.65, 0.09, 0.51, 0.23};
    int n2 = sizeof(arr2) / sizeof(arr2[0]);
    printf("Before: "); printFloatArray(arr2, n2);
    bucketSort(arr2, n2);
    printf("After:  "); printFloatArray(arr2, n2);
    printf("\n");

    /* ---- 3. Counting Sort ---- */
    printf("============================================\n");
    printf(" 3. COUNTING SORT\n");
    printf("============================================\n");
    int arr3[] = {4, 2, 2, 8, 3, 3, 1, 7, 5};
    int n3 = sizeof(arr3) / sizeof(arr3[0]);
    printf("Before: "); printArray(arr3, n3);
    countingSort(arr3, n3);
    printf("After:  "); printArray(arr3, n3);
    printf("\n");

    /* ---- 4. Radix Sort ---- */
    printf("============================================\n");
    printf(" 4. RADIX SORT\n");
    printf("============================================\n");
    int arr4[] = {170, 45, 75, 90, 802, 24, 2, 66};
    int n4 = sizeof(arr4) / sizeof(arr4[0]);
    printf("Before: "); printArray(arr4, n4);
    radixSort(arr4, n4);
    printf("After:  "); printArray(arr4, n4);
    printf("\n");

    printf("============================================\n");
    printf(" All sorts complete!\n");
    printf("============================================\n");

    return 0;
}
