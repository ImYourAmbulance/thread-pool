#include "thread_pool.h"


ThreadPool::ThreadPool(int numThreads) 
{
    run.store(true);
    threads.resize(numThreads);
    for (int i = 0; i < numThreads; ++i) {
        threads[i] = std::thread(&ThreadPool::ThreadJob, this);
    }
}


ThreadPool::~ThreadPool() {
    run.store(false);
    for (int i = 0; i < threads.size(); ++i) {
        if (threads[i].joinable()) {
            threads[i].join();
        }
	}
}


void ThreadPool::AddTask(uint64_t number, int priority) {
    if (priority < 0) {
        return;
    }

    {
        std::lock_guard<std::mutex> guard(tasksMutex);
        tasks.push(Task{ number, priority });
    }
}


void ThreadPool::ThreadJob()
{
    while (run.load()) {
        tasksMutex.lock();
        if (tasks.empty()) {
            tasksMutex.unlock();
            std::this_thread::sleep_for(200ms);
            continue;
        }
        auto curTask = tasks.top();
        tasks.pop();
        tasksMutex.unlock();

        std::string res = "Primes of " + std::to_string(curTask.number) + " are: " + FindAllPrimes(curTask.number) + " (Priority = " + std::to_string(curTask.priority) + ")\n";

        std::cout << res << std::endl;
    }
}


std::string ThreadPool::FindAllPrimes(uint64_t number)
{
    std::string res;

    while (number % 2 == 0) {
        res.append(std::to_string(2) + " ");
        number /= 2;
    }

    for (long long i = 3; i <= std::sqrt(number); i += 2) {
        while (number % i == 0) {
            res.append(std::to_string(i) + " ");
            number /= i;
        }
    }

    if (number > 2) {
        res.append(std::to_string(number) + " ");
    }

    return res;
}
