#include <iostream>
#include <vector>
#include <thread>
#include <chrono> // For timing

// Function to multiply a single row of matrix A with all columns of matrix B
void multiplyRow(const std::vector<std::vector<int>>& A, 
                 const std::vector<std::vector<int>>& B, 
                 std::vector<std::vector<int>>& C, 
                 int row, int n, int m) {
    for (int j = 0; j < m; ++j) {
        C[row][j] = 0;
        for (int k = 0; k < n; ++k) {
            C[row][j] += A[row][k] * B[k][j];
        }
    }
}

// Multithreaded matrix multiplication
void multithreadedMatrixMultiplication(const std::vector<std::vector<int>>& A, 
                                       const std::vector<std::vector<int>>& B, 
                                       std::vector<std::vector<int>>& C, int numThreads) {
    int rows = A.size();
    int cols = B[0].size();
    int n = B.size();

    std::vector<std::thread> threads;

    for (int i = 0; i < rows; ++i) {
        threads.push_back(std::thread(multiplyRow, std::ref(A), std::ref(B), std::ref(C), i, n, cols));
        if (threads.size() == numThreads || i == rows - 1) {
            for (auto& t : threads) t.join(); // Wait for all threads to finish
            threads.clear();
        }
    }
}

// Sequential matrix multiplication
void sequentialMatrixMultiplication(const std::vector<std::vector<int>>& A, 
                                    const std::vector<std::vector<int>>& B, 
                                    std::vector<std::vector<int>>& C) {
    int rows = A.size();
    int cols = B[0].size();
    int n = B.size();

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            C[i][j] = 0;
            for (int k = 0; k < n; ++k) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

int main() {
    const int N = 500; // Matrix size (NxN)
    int numThreads = 8; // Number of threads

    // Initialize matrices A and B with random values
    std::vector<std::vector<int>> A(N, std::vector<int>(N, 1));
    std::vector<std::vector<int>> B(N, std::vector<int>(N, 1));
    std::vector<std::vector<int>> C(N, std::vector<int>(N, 0));

    // Measure time for sequential matrix multiplication
    auto startSeq = std::chrono::high_resolution_clock::now();
    sequentialMatrixMultiplication(A, B, C);
    auto endSeq = std::chrono::high_resolution_clock::now();
    auto seqDuration = std::chrono::duration_cast<std::chrono::milliseconds>(endSeq - startSeq);

    std::cout << "Time taken for sequential matrix multiplication: " << seqDuration.count() << " ms\n";

    // Measure time for multithreaded matrix multiplication
    auto startMT = std::chrono::high_resolution_clock::now();
    multithreadedMatrixMultiplication(A, B, C, numThreads);
    auto endMT = std::chrono::high_resolution_clock::now();
    auto mtDuration = std::chrono::duration_cast<std::chrono::milliseconds>(endMT - startMT);

    std::cout << "Time taken for multithreaded matrix multiplication: " << mtDuration.count() << " ms\n";

    return 0;
}
