#include <iostream>
#include <vector>
#include <algorithm>
#include <iostream>

void knapSack01(std::vector<int> weights, std::vector<int> profits, int capacity, int n)
{
    int bu[n+1][capacity+1]{};
       for(int i{0}; i<n; ++i)
    {
        for(int j{0}; j<capacity; ++j)
            std::cout << bu[i][j] << ' ';
        std::cout << '\n';
    }
    
    std::cout << "\nlinebreak\n\n";
    for(int i{0}; i<n+1; ++i)
    {
        for(int j{0}; j<capacity+1; ++j)
        {
            if(i == 0 || j == 0)
                bu[i][j] = 0;
 else if(weights[i-1] <= j)
            {
                bu[i][j] = std::max(bu[i-1][j], (bu[i-1][j - weights[i-1]]+profits[i-1]));
            }
            else
            {
                bu[i][j] = bu[i-1][j];
            }
        }
    }
    std::cout << "\nDP Tabe:\n";
    for(int i{0}; i<n+1; ++i)
    {
        for(int j{0}; j<capacity+1; ++j)
            std::cout << bu[i][j] << ' ';
        std::cout << '\n';
    }
    std::cout << "\nMaximum Profit that can be obtained = " << bu[n][capacity];
    // return 0;
}
int main()
{
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
   knapSack01(weights, profits, maxWeight, n);
    std::cout<<"\nHi from prathamesh";

    return 0;
}
