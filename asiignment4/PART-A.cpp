//Implement Merge Sort using divide and conquer strategy. Note the time required
//for best and worst case situations on large number of values.


#include <iostream>
#include <vector>
#include <chrono> // For timing

// Function to merge two subarrays
void merge(std::vector<int>& arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    std::vector<int> L(n1), R(n2);

    for (int i = 0; i < n1; i++) L[i] = arr[left + i];
    for (int i = 0; i < n2; i++) R[i] = arr[mid + 1 + i];

    int i = 0, j = 0, k = left;

    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k++] = L[i++];
        } else {
            arr[k++] = R[j++];
        }
    }

    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];
}

// Merge Sort function
void mergeSort(std::vector<int>& arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

int main() {
    const int size = 100000; // Large input size
    std::vector<int> bestCase(size), worstCase(size);

    // Generate Best Case (Already Sorted)
    for (int i = 0; i < size; i++) bestCase[i] = i;

    // Generate Worst Case (Reverse Sorted)
    for (int i = 0; i < size; i++) worstCase[i] = size - i;

    // Measure Best Case Time
    std::cout << "Sorting Best Case Array...\n";
    auto startBest = std::chrono::high_resolution_clock::now();
    mergeSort(bestCase, 0, size - 1);
    auto endBest = std::chrono::high_resolution_clock::now();
    auto bestCaseDuration = std::chrono::duration_cast<std::chrono::microseconds>(endBest - startBest);

    // Measure Worst Case Time
    std::cout << "Sorting Worst Case Array...\n";
    auto startWorst = std::chrono::high_resolution_clock::now();
    mergeSort(worstCase, 0, size - 1);
    auto endWorst = std::chrono::high_resolution_clock::now();
    auto worstCaseDuration = std::chrono::duration_cast<std::chrono::microseconds>(endWorst - startWorst);

    // Display Results
    std::cout << "Best Case Time: " << bestCaseDuration.count() << " microseconds\n";
    std::cout << "Worst Case Time: " << worstCaseDuration.count() << " microseconds\n";

    return 0;
}
