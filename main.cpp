#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
#include "Fork.cpp"

std::vector<std::thread> philosopher;
std::vector<Fork> forks;
std::mutex print;
const int min_time = 50;
const int max_time = 100;


void eat(int numberOfPhilosopher, int iter) {
    int count = 0;
    while (count < iter) {
        int first_fork, second_fork;
        if (numberOfPhilosopher == philosopher.size() - 1) {
            first_fork = 0;
            second_fork = numberOfPhilosopher;
        } else {
            first_fork = numberOfPhilosopher;
            second_fork = numberOfPhilosopher + 1;
        }

        std::chrono::duration<long long int, std::milli> milliseconds = std::chrono::milliseconds(min_time + (rand() % static_cast<int>(max_time - min_time + 1)));

        forks[first_fork].lock();
        forks[second_fork].lock();

        print.lock();
        std::cout << "Philosopher " << numberOfPhilosopher + 1 <<
                  " started eating for " << milliseconds.count() << " ms" << "\n";
        print.unlock();

        std::this_thread::sleep_for(milliseconds);

        print.lock();
        std::cout << "Philosopher " << numberOfPhilosopher + 1 << " finished eating." << "\n";
        print.unlock();

        forks[first_fork].unlock();
        forks[second_fork].unlock();

        std::this_thread::sleep_for(std::chrono::milliseconds(10));
        ++count;
    }
}

int main(int argc, char *argv[]) {
    int iter;
    std::cout << "Please, enter  the number of servings that every philosopher can eat: " << "\n";
    std::cin >> iter;

    srand(std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch()).count());

    for (int i = 0; i < 5; ++i) {
        forks.emplace_back();
    }

    for (int i = 0; i < 5; ++i) {
        philosopher.emplace_back(eat, i, iter);
    }

    for (int i = 0; i < 5; ++i) {
        philosopher[i].join();
    }

    return 0;
}