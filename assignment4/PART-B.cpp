//Write a function to demonstrate Crossover of two chromosome representing solution
//of Traveling Salesperson Problem (TSP)

#include <iostream>
#include <vector>
#include <algorithm> // For find()

// Function to display a chromosome
void displayChromosome(const std::vector<int>& chromosome) {
    for (size_t i = 0; i < chromosome.size(); ++i) {
        std::cout << chromosome[i] << " ";
    }
    std::cout << std::endl;
}

// Function to perform Partially Mapped Crossover (PMX)
std::pair<std::vector<int>, std::vector<int>> crossover(const std::vector<int>& parent1, const std::vector<int>& parent2, int crossoverPoint1, int crossoverPoint2) {
    int n = parent1.size();
    std::vector<int> offspring1 = parent1;
    std::vector<int> offspring2 = parent2;

    // Perform crossover between crossoverPoint1 and crossoverPoint2
    for (int i = crossoverPoint1; i <= crossoverPoint2; ++i) {
        // Swap values between offspring
        std::swap(offspring1[i], offspring2[i]);
    }

    // Fix conflicts in offspring1
    for (int i = crossoverPoint1; i <= crossoverPoint2; ++i) {
        int value = offspring1[i];
        if (std::find(offspring1.begin() + crossoverPoint1, offspring1.begin() + crossoverPoint2 + 1, value) != offspring1.begin() + i) {
            // Resolve conflict
            for (int j = 0; j < n; ++j) {
                if (std::find(offspring1.begin() + crossoverPoint1, offspring1.begin() + crossoverPoint2 + 1, parent2[j]) == offspring1.end()) {
                    offspring1[i] = parent2[j];
                    break;
                }
            }
        }
    }

    // Fix conflicts in offspring2
    for (int i = crossoverPoint1; i <= crossoverPoint2; ++i) {
        int value = offspring2[i];
        if (std::find(offspring2.begin() + crossoverPoint1, offspring2.begin() + crossoverPoint2 + 1, value) != offspring2.begin() + i) {
            // Resolve conflict
            for (int j = 0; j < n; ++j) {
                if (std::find(offspring2.begin() + crossoverPoint1, offspring2.begin() + crossoverPoint2 + 1, parent1[j]) == offspring2.end()) {
                    offspring2[i] = parent1[j];
                    break;
                }
            }
        }
    }

    return {offspring1, offspring2};
}

int main() {
    // Example parent chromosomes
    std::vector<int> parent1 = {0, 11, 10, 9, 6};
    std::vector<int> parent2 = {8, 4, 7, 3, 6};

    // Define crossover points
    int crossoverPoint1 = 1; // Start of the crossover segment
    int crossoverPoint2 = 3; // End of the crossover segment

    std::cout << "Parent 1: ";
    displayChromosome(parent1);

    std::cout << "Parent 2: ";
    displayChromosome(parent2);

    // Perform crossover
    auto [offspring1, offspring2] = crossover(parent1, parent2, crossoverPoint1, crossoverPoint2);

    std::cout << "Offspring 1: ";
    displayChromosome(offspring1);

    std::cout << "Offspring 2: ";
    displayChromosome(offspring2);

    return 0;
}
