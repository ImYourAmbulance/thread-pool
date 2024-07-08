# thread-pool test assignment

You need to implement a ThreadPool that can do any work in one of the pre-created worker threads, as well as a console application that demonstrates how the ThreadPool works. If the user enters restart, then the existing ThreadPool is destroyed and a new one is created with a larger number of worker threads.

If the user enters exit, the application ends. If the user entered two numbers, then the application sends work to the ThreadPool to calculate all prime factors of the first number (uint64), and the second number is needed to set the priority for this task. After completing the work, you need to output the result to the console.

The program is better off written in the new C++, because the new C++ has threads, synchronization primitives and a lot of other good things. The best way to build is to use CMake.
