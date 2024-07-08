#include <iostream>
#include <string>
#include <thread>
#include <vector>
#include <queue>
#include <mutex>
#include <functional>


extern std::atomic<bool> run;


struct Task {
    uint64_t number;
    int priority;
};


struct TaskComp
{
    bool operator()(const Task& lhs, const Task& rhs) const
    {
      return lhs.priority < rhs.priority;
    }
};

class ThreadPool {
public:
    ThreadPool(int numThreads = 10);

    void AddTask(uint64_t number, int priority);

    void ThreadJob(); 

    static std::string FindAllPrimes(uint64_t number);

    ~ThreadPool();

private:
    std::priority_queue<Task, std::vector<Task>, TaskComp> tasks;
    std::vector<std::thread> threads;
};