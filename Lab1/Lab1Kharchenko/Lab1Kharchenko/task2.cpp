#include <iostream>
#include <list>
#include <thread>
#include <mutex>
#include <random>

std::list<int> mylist;
std::mutex mtx;

void addRandomValue() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(1, 100);

    while (true) {
        int random_value = dist(gen);

        std::lock_guard<std::mutex> lock(mtx); // Lock the mutex
        mylist.push_back(random_value);

        if (mylist.size() >= 10) {
            break;
        }
    }
}

void printList() {
    while (true) {
        std::lock_guard<std::mutex> lock(mtx); // Lock the mutex
        for (const int& val : mylist) {
            std::cout << val << " ";
        }
        std::cout << std::endl;

        if (mylist.size() >= 10) {
            break;
        }
    }
}

int main() {
    std::thread t1(addRandomValue);
    std::thread t2(printList);

    t1.join();
    t2.join();

    return 0;
}
