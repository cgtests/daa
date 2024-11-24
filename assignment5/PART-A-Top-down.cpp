#include <iostream>
#include <vector>
#include <algorithm>

std::vector<std::vector<int>> memo;
std::vector<int> included;

int knapsack01td(const std::vector<int>& weights, const std::vector<int>& profits, int i, int j) {
    if (i == 0 || j == 0)
        return 0;
    
 if (memo[i][j] != -1)
        return memo[i][j];
    
    if (weights[i-1] > j) {
        memo[i][j] = knapsack01td(weights, profits, i - 1, j);
    } else {
        int include = profits[i-1] + knapsack01td(weights, profits, i - 1, j - weights[i-1]);
        int exclude = knapsack01td(weights, profits, i - 1, j);
        memo[i][j] = std::max(include, exclude);
    }
    
    return memo[i][j];
}

void knapsack01TopDown(const std::vector<int>& weights, const std::vector<int>& profits, int capacity, int n) {
    memo.assign(n + 1, std::vector<int>(capacity + 1, -1));
    
    included.assign(n, 0);

    int maxProfit = knapsack01td(weights, profits, n, capacity);

    int i = n, j = capacity;
    while (i > 0 && j > 0) {
        if (memo[i][j] != memo[i-1][j]) {
            included[i-1] = 1;
            j -= weights[i-1];
        }
        i--;
    }

    std::cout << "\nDP Table:\n";
    for (const auto& row : memo) {
        for (int val : row) {
            std::cout << val << ' ';
 }
        std::cout << '\n';
    }
    
    std::cout << "\nMaximum Profit that can be obtained = " << maxProfit << std::endl;
    std::cout << "Final Objects Array: ";
    for (int item : included) {
        std::cout << item << ' ';
    }
    std::cout << std::endl;
}

int main() {
    int n{};
    std::cout << "Enter the number of objects: ";
    std::cin >> n;
    
    std::vector<int> weights(n);
    std::vector<int> profits(n);
    
    for(int i{0}; i<n; ++i)
    {
        std::cout << "Enter the weight and profit of " << i+1 << "th object: ";
        std::cin >> weights[i] >> profits[i];
    }
    int maxWeight{};
    std::cout << "Enter max weight capacity of knapsack: ";
    std::cin >> maxWeight;
    
    knapsack01TopDown(weights, profits, maxWeight, n);
    std::cout << "\n Hi from prathamesh";
    return 0;
}
