#include "thread_pool.h"
#include <memory>
#include <sstream>
#include <fstream>


#define PATH "../commands.txt"


int main() {
    int baseThreadsNum = 10;
    
    auto pool = std::make_unique<ThreadPool>(baseThreadsNum);

    std::string command;
    uint64_t number;
    int priority;

#ifdef READ_FROM_FILE
    std::ifstream file(PATH);
    if (!file.is_open()) {
        return 0;
    }
#endif

    while (pool) {
#ifdef READ_FROM_FILE
        std::getline(file, command);
#else
        std::getline(std::cin, command);
#endif
        if (command == "exit") {
            pool = nullptr;
        } else if (command == "restart") {
            pool = std::make_unique<ThreadPool>(++baseThreadsNum);
        } else {
            std::stringstream ss(command);
            auto start = std::istream_iterator<uint64_t>{ ss };
            auto end = std::istream_iterator<uint64_t>{};
            std::vector<uint64_t> input(start, end);
            
            if (input.size() != 2) {
                continue;
            }
            pool->AddTask(input[0], (int)input[1]); // TODO: wild hack
        }
    }

    return 0;
}