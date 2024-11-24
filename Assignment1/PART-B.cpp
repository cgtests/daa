#include <iostream>
#include <chrono> // For measuring time
#include <cstdlib> // For generating random numbers

// Utility function to swap elements:
void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// QuickSort Partitioning function
int partition(int A[], int low, int high) {
    int pivot = A[low];
    int i = low, j = high;

    do {
        do { i++; } while (i <= high && A[i] <= pivot);
        do { j--; } while (A[j] > pivot);
        if (i < j) swap(&A[i], &A[j]);
    } while (i < j);

    swap(&A[low], &A[j]);
    return j;
}

// QuickSort function
void quickSort(int A[], int low, int high) {
    if (low < high) {
        int pi = partition(A, low, high);
        quickSort(A, low, pi - 1);
        quickSort(A, pi + 1, high);
    }
}

// Merge function for MergeSort
void merge(int A[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    int* L = new int[n1];
    int* R = new int[n2];

    for (int i = 0; i < n1; ++i) L[i] = A[left + i];
    for (int i = 0; i < n2; ++i) R[i] = A[mid + 1 + i];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            A[k++] = L[i++];
        } else {
            A[k++] = R[j++];
        }
    }

    while (i < n1) A[k++] = L[i++];
    while (j < n2) A[k++] = R[j++];

    delete[] L;
    delete[] R;
}

// MergeSort function
void mergeSort(int A[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(A, left, mid);
        mergeSort(A, mid + 1, right);
        merge(A, left, mid, right);
    }
}

int main() {
    const int size = 500;
    int* original = new int[size]; // Original data array
    int* quickSortArray = new int[size]; // Array for QuickSort
    int* mergeSortArray = new int[size]; // Array for MergeSort

    // Generate random values for the array
    srand(static_cast<unsigned>(time(0)));
    for (int i = 0; i < size; ++i) {
        original[i] = rand() % 1000; // Random values between 0 and 999
    }

    // Copy data for both algorithms
    std::copy(original, original + size, quickSortArray);
    std::copy(original, original + size, mergeSortArray);

    std::cout << "Sorting 500 values...\n";

    // QuickSort
    auto startQuickSort = std::chrono::high_resolution_clock::now();
    quickSort(quickSortArray, 0, size - 1);
    auto endQuickSort = std::chrono::high_resolution_clock::now();
    auto quickSortDuration = std::chrono::duration_cast<std::chrono::microseconds>(endQuickSort - startQuickSort);

    // MergeSort
    auto startMergeSort = std::chrono::high_resolution_clock::now();
    mergeSort(mergeSortArray, 0, size - 1);
    auto endMergeSort = std::chrono::high_resolution_clock::now();
    auto mergeSortDuration = std::chrono::duration_cast<std::chrono::microseconds>(endMergeSort - startMergeSort);

    // Display Results
    std::cout << "QuickSort time: " << quickSortDuration.count() << " microseconds\n";
    std::cout << "MergeSort time: " << mergeSortDuration.count() << " microseconds\n";

    // (Optional) Verify sorted arrays
    std::cout << "\nSorted values (QuickSort):\n";
    for (int i = 0; i < size; ++i) std::cout << quickSortArray[i] << " ";
    std::cout << "\n\nSorted values (MergeSort):\n";
    for (int i = 0; i < size; ++i) std::cout << mergeSortArray[i] << " ";
    std::cout << "\n";

    // Free allocated memory
    delete[] original;
    delete[] quickSortArray;
    delete[] mergeSortArray;

    return 0;
}
