//: Implement Quicksort using divide and conquer strategy and display time for sorting
//for 500 values

#include <iostream>
#include <chrono> // For measuring time
#include <cstdlib> // For generating random numbers

// Utility function to swap elements:
void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Partitioning function
int partition(int A[], int low, int high) {
    int pivot = A[low];
    int i = low, j = high;

    do {
        do { i++; } while (i <= high && A[i] <= pivot); // Skip smaller elements
        do { j--; } while (A[j] > pivot);              // Skip larger elements
        if (i < j) swap(&A[i], &A[j]);                 // Swap misplaced elements
    } while (i < j);

    swap(&A[low], &A[j]); // Move pivot to its correct position
    return j;             // Return partition index
}

// QuickSort function using divide and conquer strategy
void quickSort(int A[], int low, int high) {
    if (low < high) {
        int pi = partition(A, low, high); // Find partition index
        quickSort(A, low, pi - 1);        // Apply QuickSort on left subarray
        quickSort(A, pi + 1, high);       // Apply QuickSort on right subarray
    }
}

int main() {
    const int size = 500; // Size of the array
    int* A = new int[size]; // Dynamically allocated array

    // Generate random values for the array
    srand(static_cast<unsigned>(time(0)));
    for (int i = 0; i < size; ++i) {
        A[i] = rand() % 1000; // Random values between 0 and 999
    }

    std::cout << "Sorting 500 values using QuickSort...\n";

    // Measure sorting time
    auto start = std::chrono::high_resolution_clock::now();
    quickSort(A, 0, size);
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

    // Display sorted output (optional)
    std::cout << "Sorted values:\n";
    for (int i = 0; i < size; ++i) {
        std::cout << A[i] << " ";
    }
    std::cout << "\n";

    // Display time taken
    std::cout << "Time taken to sort: " << duration.count() << " microseconds\n";

    delete[] A; // Free allocated memory
    return 0;
}
