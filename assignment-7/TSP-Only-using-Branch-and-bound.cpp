#include <iostream>
#include <bits/stdc++.h>
#include <limits.h> 

const int INF = INT_MAX;

int rowReduction(std::vector<std::vector<int>>& costMatrix, int n, std::vector<bool>& row) {
    int minCost, cost = 0;
    for (int i{0}; i < n; i++) {
        if (!row[i]) {
            minCost = INF;
            for (int j{0}; j < n; j++) {
                if (costMatrix[i][j] < minCost)
                    minCost = costMatrix[i][j];
            }
            if (minCost != INF) {
                cost += minCost;
                for (int j{0}; j < n; j++) {
                    if (costMatrix[i][j] != INF)
                        costMatrix[i][j] -= minCost;
                }
            }
        }
    }
    return cost;
}

int colReduction(std::vector<std::vector<int>>& costMatrix, int n, std::vector<bool>& col) {
    int minCost, cost = 0;
    for (int i{0}; i < n; i++) {
        if (!col[i]) {
            minCost = INF;
            for (int j{0}; j < n; j++) {
                if (costMatrix[j][i] < minCost)
                    minCost = costMatrix[j][i];
            }
            if (minCost != INF) {
                cost += minCost;
                for (int j{0}; j < n; j++) {
                    if (costMatrix[j][i] != INF)
                        costMatrix[j][i] -= minCost;
                }
            }
        }
    }
    return cost;
}

int reduceMatrix(std::vector<std::vector<int>>& costMatrix, int n, std::vector<bool>& row, std::vector<bool>& col) {
    return rowReduction(costMatrix, n, row) + colReduction(costMatrix, n, col);
}

struct Node {
    int vertex, cost, level;
    std::vector<std::vector<int>> reducedMatrix;
    std::vector<int> path;
};

// Custom Comparator for Priority Queue
struct compare {
    bool operator()(const Node& a, const Node& b) const {
        return a.cost > b.cost;
    }
};

// print path
void printPath(const std::vector<int>& path) {
  std::cout << "Path: " << '\n';
    for (int i{0}; i < path.size(); i++) {
        std::cout << path[i] + 1 << "->";
    }
    std::cout << path[0] + 1 << '\n';
}

// TSP using Branch and Bound
int TSP(std::vector<std::vector<int>>& costMatrix, int n) {
    std::priority_queue<Node, std::vector<Node>, compare> pq;

    std::vector<bool> row(n, false);
    std::vector<bool> col(n, false);

    Node root;
    root.vertex = 0;
    root.path.push_back(0);
    root.level = 0;
    root.reducedMatrix = costMatrix;

    root.cost = reduceMatrix(root.reducedMatrix, n, row, col);
    pq.push(root);

    while (!pq.empty()) {
        Node minNode = pq.top();
        pq.pop();

        if (minNode.level == n - 1) {
            printPath(minNode.path);
            return minNode.cost;
        }

        for (int i = 1; i < n; i++) {
            if (find(minNode.path.begin(), minNode.path.end(), i) == minNode.path.end()) {
                Node child;
                child.vertex = i;
                child.path = minNode.path;
                child.path.push_back(i);
                child.level = minNode.level + 1;
                child.reducedMatrix = minNode.reducedMatrix;

                // validity of rows and columns
                for (int j = 0; j < n; j++) {
                    child.reducedMatrix[minNode.vertex][j] = INF;
                    child.reducedMatrix[j][i] = INF;
                }
                child.reducedMatrix[i][0] = INF;

                // cost for the child
                child.cost = minNode.cost + costMatrix[minNode.vertex][i];
                child.cost += reduceMatrix(child.reducedMatrix, n, row, col);
                pq.push(child);
            }
        }
    }
    return INF;
}

int main() {
  // number of cities
  int N;
  std::cout << "Enter the number of cities: ";
  std::cin >> N;

  std::vector<std::vector<int>> costMatrix(N, std::vector<int>(N));
  std::cout << "Enter the cost matrix:\n";
  for (int i{0}; i < N; i++)
  {
        for (int j{0}; j < N; j++)
        {
          if(i == j)
          {
            costMatrix[i][j] = INF;
            continue;
          }
          std::cout << "Cost of edge from city " <<  i+1 << " to " << "city " << j+1 << ": ";
          std::cin >> costMatrix[i][j];
        }
  }
  int minCost = TSP(costMatrix, N);
  std::cout << "Minimum cost: " << minCost << '\n';
  std::cout << INT_MAX;
  return 0;
}
