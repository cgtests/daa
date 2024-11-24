#include <iostream>
#include <chrono>
#include <cstdlib> // For generating random numbers
#include <ctime>   // For seeding the random number generator

// Utility function to swap elements
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
        while (i <= high && A[i] <= pivot) i++;
        while (A[j] > pivot) j--;
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

int main() {
    const int size = 1000; // Array size greater than 500
    int bestCaseArray[size];
    int worstCaseArray[size];

    // Generate Best-Case Array: Randomly shuffled array
    srand((unsigned)time(0));
    for (int i = 0; i < size; i++) {
        bestCaseArray[i] = rand() % 1000 + 1; // Random values between 1 and 1000
    }

    // Generate Worst-Case Array: Already sorted array
    for (int i = 0; i < size; i++) {
        worstCaseArray[i] = i + 1;
    }

    // Measure Best Case
    std::cout << "Sorting Best Case Array...\n";
    std::chrono::high_resolution_clock::time_point startBest = std::chrono::high_resolution_clock::now();
    quickSort(bestCaseArray, 0, size - 1);
    std::chrono::high_resolution_clock::time_point endBest = std::chrono::high_resolution_clock::now();
    std::chrono::microseconds bestCaseDuration = std::chrono::duration_cast<std::chrono::microseconds>(endBest - startBest);

    // Measure Worst Case
    std::cout << "Sorting Worst Case Array...\n";
    std::chrono::high_resolution_clock::time_point startWorst = std::chrono::high_resolution_clock::now();
    quickSort(worstCaseArray, 0, size - 1);
    std::chrono::high_resolution_clock::time_point endWorst = std::chrono::high_resolution_clock::now();
    std::chrono::microseconds worstCaseDuration = std::chrono::duration_cast<std::chrono::microseconds>(endWorst - startWorst);

    // Display Results
    std::cout << "Best Case Time: " << bestCaseDuration.count() << " microseconds\n";
    std::cout << "Worst Case Time: " << worstCaseDuration.count() << " microseconds\n";

    return 0;
}
