// Lab1Kharchenko.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#define _CRT_SECURE_NO_WARNING
#include <iostream>
#include <thread>
using namespace std;

int numbers = 0;

void increment_data() {
    while (true) {
        if (numbers == 1000 || numbers == -1000) {
            cout << numbers << "\n";
            break;
        }
        numbers++;
    }
}

void decrement_data() {
    while (true) {
        if (numbers == 1000 || numbers == -1000) {
            cout << numbers << "\n";
            break;
        }
        numbers--;
    }
}

int main()
{
    thread increment_thread(increment_data);
    thread decrement_thread(decrement_data);
    increment_thread.join();
    decrement_thread.join();
    return 0;
}
