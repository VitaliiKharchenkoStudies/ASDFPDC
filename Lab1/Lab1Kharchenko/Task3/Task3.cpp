#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
#include <chrono>

const int N = 5; // Number of philosophers and forks
std::mutex forks[N];

void philosopher(int id) {
    int left_fork = id;
    int right_fork = (id + 1) % N;

    // Simulate philosophers thinking
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));

    while (true) {
        std::unique_lock<std::mutex> left_lock(forks[left_fork]);
        std::this_thread::sleep_for(std::chrono::milliseconds(100)); // Simulate picking up the left fork

        std::unique_lock<std::mutex> right_lock(forks[right_fork]);
        std::this_thread::sleep_for(std::chrono::milliseconds(100)); // Simulate picking up the right fork

        std::cout << "Philosopher " << id << " is eating." << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(1000)); // Simulate eating

        right_lock.unlock(); // Release the right fork
        left_lock.unlock();  // Release the left fork

        // Simulate philosophers thinking before the next meal
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
}

int main() {
    std::vector<std::thread> philosophers;

    for (int i = 0; i < N; ++i) {
        philosophers.emplace_back(philosopher, i);
    }

    for (std::thread& t : philosophers) {
        t.join();
    }

    return 0;
}
