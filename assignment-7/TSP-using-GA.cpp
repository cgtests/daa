#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <ctime>
#include <limits.h>

const int INF = INT_MAX;
const int POP_SIZE = 50;  
const int GEN_COUNT = 500;  
const double MUTATION_RATE = 0.1;  

int randomInt(int min, int max) {
    static std::mt19937 rng(time(0));
    std::uniform_int_distribution<int> dist(min, max - 1);
    return dist(rng);
}

// Calculate the cost of a tour
int calculateCost(const std::vector<int>& tour, const std::vector<std::vector<int>>& costMatrix) {
    int cost = 0;
    for (int i = 0; i < tour.size() - 1; i++) {
        cost += costMatrix[tour[i]][tour[i + 1]];
    }
    cost += costMatrix[tour.back()][tour[0]];  // Return to the starting point
    return cost;
}

// Initialize population with random tours
std::vector<std::vector<int>> initializePopulation(int n) {
    std::vector<std::vector<int>> population;
    std::vector<int> tour(n);
    iota(tour.begin(), tour.end(), 0);  // Generate {0, 1, 2, ..., n-1}
    for (int i = 0; i < POP_SIZE; i++) {
        shuffle(tour.begin() + 1, tour.end(), std::mt19937(time(0)));  // Random shuffle except the first city
        population.push_back(tour);
    }
    return population;
}

// Tournament selection
std::vector<int> selectParent(const std::vector<std::vector<int>>& population, const std::vector<int>& fitness) {
    int a = randomInt(0, POP_SIZE);
    int b = randomInt(0, POP_SIZE);
    return fitness[a] < fitness[b] ? population[a] : population[b];
}

// Order Crossover (OX)
std::vector<int> crossover(const std::vector<int>& parent1, const std::vector<int>& parent2) {
    int n = parent1.size();
    std::vector<int> child(n, -1);

    int start = randomInt(1, n - 1);
    int end = randomInt(start + 1, n);

    for (int i = start; i < end; i++) {
        child[i] = parent1[i];
    }

    int index = end % n;
    for (int i = 0; i < n; i++) {
        if (find(child.begin(), child.end(), parent2[i]) == child.end()) {
            child[index] = parent2[i];
            index = (index + 1) % n;
        }
    }
    return child;
}

// Swap Mutation
void mutate(std::vector<int>& tour) {
    if (randomInt(0, 100) < MUTATION_RATE * 100) {
        int i = randomInt(1, tour.size());
        int j = randomInt(1, tour.size());
        std::swap(tour[i], tour[j]);
    }
}

// Genetic Algorithm for TSP
std::vector<int> geneticAlgorithm(const std::vector<std::vector<int>>& costMatrix, int n) {
    std::vector<std::vector<int>> population = initializePopulation(n);

    std::vector<int> bestTour;
    int bestCost = INF;

    for (int gen = 0; gen < GEN_COUNT; gen++) {
        std::vector<int> fitness(POP_SIZE);
        for (int i = 0; i < POP_SIZE; i++) {
            fitness[i] = calculateCost(population[i], costMatrix);
            if (fitness[i] < bestCost) {
                bestCost = fitness[i];
                bestTour = population[i];
            }
        }

        std::vector<std::vector<int>> newPopulation;
        for (int i = 0; i < POP_SIZE; i++) {
            std::vector<int> parent1 = selectParent(population, fitness);
            std::vector<int> parent2 = selectParent(population, fitness);
            std::vector<int> child = crossover(parent1, parent2);
            mutate(child);
            newPopulation.push_back(child);
        }
        population = newPopulation;
    }
    return bestTour;
}

int main() {
    int n;
    std::cout << "Enter the number of cities: ";
    std::cin >> n;

    std::vector<std::vector<int>> costMatrix(n, std::vector<int>(n));
    std::cout << "Enter the cost matrix:\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            std::cin >> costMatrix[i][j];
        }
    }

    std::vector<int> bestTour = geneticAlgorithm(costMatrix, n);
    std::cout << "Best Tour: ";
    for (int city : bestTour) {
        std::cout << city + 1 << " ";
    }
    std::cout << "\nMinimum Cost: " << calculateCost(bestTour, costMatrix) << '\n';

    return 0;
}
