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
    cv.notify_all();
    for (int i = 0; i < threads.size(); ++i) {
        if (threads[i].joinable()) {
            threads[i].join();
        }
	}
}


void ThreadPool::AddTask(uint64_t number, int priority) {
    {
        std::lock_guard<std::mutex> guard(tasksMutex);
        tasks.push(Task{ number, priority });
    }
    cv.notify_one();
}


void ThreadPool::ThreadJob()
{
    while (run.load()) {

        Task curTask;
        {
            std::unique_lock<std::mutex> lock{ tasksMutex };

            if (tasks.empty()) {
                cv.wait(lock, [&]() { return !tasks.empty() || !run.load(); });
            }

            if (!tasks.empty() && run.load()) {
                curTask = tasks.top();
                tasks.pop();
            } else {
                continue;
            }
        }

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
