#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <chrono>

// Number of philosophers
const int NUM_PHILOSOPHERS = 5;

// Mutexes to represent forks
std::mutex forks[NUM_PHILOSOPHERS];

// Philosopher function
void philosopher(int id) {
    int leftFork = id;
    int rightFork = (id + 1) % NUM_PHILOSOPHERS;

    while (true) {
        // Philosopher is thinking
        std::cout << "Philosopher " << id + 1 << " is thinking.\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));

        // Try to pick up forks (deadlock prevention using ordering)
        if (id % 2 == 0) {
            std::lock(forks[leftFork], forks[rightFork]);
        } else {
            std::lock(forks[rightFork], forks[leftFork]);
        }

        // Lock both forks
        std::lock_guard<std::mutex> leftLock(forks[leftFork], std::adopt_lock);
        std::lock_guard<std::mutex> rightLock(forks[rightFork], std::adopt_lock);

        // Philosopher is eating
        std::cout << "Philosopher " << id + 1 << " is eating.\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));

        // Release forks (automatically when lock_guard goes out of scope)
    }
}

int main() {
    std::vector<std::thread> philosophers;

    // Create threads for each philosopher
    for (int i = 0; i < NUM_PHILOSOPHERS; ++i) {
        philosophers.emplace_back(philosopher, i);
    }

    // Join all threads
    for (auto& p : philosophers) {
        p.join();
    }

    return 0;
}
