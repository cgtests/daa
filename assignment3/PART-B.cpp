// Write a function to demonstrate Mutation of a chromosome representing solution of
// Traveling Salesperson Problem (TSP)


#include <iostream>
#include <vector>
#include <cstdlib> // For rand() and srand()
#include <ctime>   // For time()

// Function to display a chromosome (path)
void displayChromosome(const std::vector<int>& chromosome) {
    for (size_t i = 0; i < chromosome.size(); ++i) {
        std::cout << chromosome[i] << " ";
    }
    std::cout << std::endl;
}

// Function to perform mutation on a chromosome
void mutateChromosome(std::vector<int>& chromosome) {
    int n = chromosome.size();
    if (n < 2) return; // No mutation possible for fewer than 2 cities

    // Randomly select two positions in the chromosome
    int pos1 = rand() % n;
    int pos2 = rand() % n;

    // Ensure the two positions are distinct
    while (pos1 == pos2) {
        pos2 = rand() % n;
    }

    // Swap the cities at the two positions
    std::swap(chromosome[pos1], chromosome[pos2]);

    std::cout << "Mutation performed: Swapped positions " << pos1 << " and " << pos2 << std::endl;
}

int main() {
    // Seed random number generator
    srand(static_cast<unsigned>(time(0)));

    // Example chromosome (path representing a TSP solution)
    std::vector<int> chromosome = {0, 11, 10, 9, 6};

    std::cout << "Original Chromosome: ";
    displayChromosome(chromosome);

    // Perform mutation
    mutateChromosome(chromosome);

    std::cout << "Mutated Chromosome: ";
    displayChromosome(chromosome);

    return 0;
}
