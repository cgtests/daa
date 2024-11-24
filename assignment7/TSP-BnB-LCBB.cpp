#include <iostream>
#include <vector>
#include <limits.h> 

// Number of cities
int N {};

// Find minimum cost edge from C
int findMinEdgeCost(int city, std::vector<std::vector<int>>& costMatrix) {
    int minCost = INT_MAX;
    for (int i{0}; i < N; i++) {
        if (city != i && costMatrix[city][i] < minCost) {
            minCost = costMatrix[city][i];
        }
    }
    return minCost;
}

// Find Lower Bound for Partial search
int calculateLowerBound(std::vector<std::vector<int>>& costMatrix, std::vector<bool>& visited, int currentCity) {
    int bound = 0;

    bound += findMinEdgeCost(currentCity, costMatrix);

    for (int i{0}; i < N; i++) {
        if (!visited[i]) {
            bound += findMinEdgeCost(i, costMatrix);
        }
    }

    return bound;
}

// B&B
void tspBranchAndBound(int level, int currentCost, std::vector<int>& currentPath, std::vector<bool>& visited,
                       int& minCost, std::vector<int>& bestPath, std::vector<std::vector<int>>& costMatrix) {
 
    if (level == N && costMatrix[currentPath[level - 1]][currentPath[0]] > 0) {
        int totalCost = currentCost + costMatrix[currentPath[level - 1]][currentPath[0]];
        if (totalCost < minCost) {
            minCost = totalCost;
            bestPath = currentPath;
        }
        return;
    }


    for (int i{0}; i < N; i++) {
        if (!visited[i] && costMatrix[currentPath[level - 1]][i] > 0) {
            int tempCost = currentCost + costMatrix[currentPath[level - 1]][i];

            // Calculate lower bound
            int bound = tempCost + calculateLowerBound(costMatrix, visited, i);

            // Prune the branch if LB >= minCOst
            if (bound < minCost) {
                currentPath[level] = i;
                visited[i] = true;
                tspBranchAndBound(level + 1, tempCost, currentPath, visited, minCost, bestPath, costMatrix);

                // Backtrack
                visited[i] = false; 
            }
        }
    }
}

int main() {
  std::cout << "Enter no. of cities: " << '\n';
  std::cin >> N;
  std::vector<std::vector<int>> costMatrix(N, std::vector<int>(N));

  std::cout << "Enter the cost matrix: " << '\n';

  for(int i{0}; i<N; ++i)
    for(int j{0}; j<N; ++j)
      std::cin >> costMatrix[i][j];

  int minCost = INT_MAX;
  std::vector<int> bestPath(N);

  std::vector<int> currentPath(N);
  std::vector<bool> visited(N, false);

  currentPath[0] = 0;
  visited[0] = true;

  tspBranchAndBound(1, 0, currentPath, visited, minCost, bestPath, costMatrix);

  std::cout << "Minimum Cost: " << minCost << '\n';
  std::cout << "Best Path: ";
  
  for (int i{0}; i < N; i++)
    std::cout << bestPath[i] << " ";
  
  std::cout << bestPath[0] << '\n';
  
  return 0;
}
