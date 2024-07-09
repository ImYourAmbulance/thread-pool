#ifndef THREADS_POOL_H
#define THREADS_POOL_H

#include <iostream>
#include <string>
#include <thread>
#include <vector>
#include <queue>
#include <mutex>
#include <functional>
#include <condition_variable>
using namespace std::chrono_literals;


struct Task {
    uint64_t number;
    int priority;

    bool operator<(const Task& other) const {
        return priority < other.priority;
    }
};


class ThreadPool {
public:
    ThreadPool(int numThreads = 10);
    ~ThreadPool();
    void AddTask(uint64_t number, int priority);
    static std::string FindAllPrimes(uint64_t number);

private:
    void ThreadJob();

private:
    std::atomic<bool> run;
    std::mutex tasksMutex;
    std::condition_variable cv;

    std::priority_queue<Task> tasks;
    std::vector<std::thread> threads;
};
#endif