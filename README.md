# thread-pool test assignment

You need to implement a ThreadPool that can do any work in one of the pre-created worker threads, as well as a console application that demonstrates how the ThreadPool works. If the user enters "restart", then the existing ThreadPool is destroyed and a new one is created with a larger number of worker threads.

If the user enters "exit", the application ends. If the user entered two numbers, then the application sends work to the ThreadPool to calculate all prime factors of the first number (uint64), and the second number is needed to set the priority for this task. After completing the work, you need to output the result to the console.

The program is better off written in the new C++, because the new C++ has threads, synchronization primitives and a lot of other good things. The best way to build is to use CMake.

# Solution explained (Russian)
Создан класс `ThreadPool`, который содержит в себе очередь с приоритетом для задач `std::priority_queue<Task> tasks`, а также массив потоков `std::vector<std::thread> threads`. 
Для доступа к массиву задач используется мьютекс `std::mutex tasksMutex`, а для передачи информации о необходимости потокам продолжать или заканчивать работу задействован `std::atomic<bool> run`.

Также создана структура для данных каждой задачи `struct Task`. В функции `ThreadPool::ThreadJob()` реализованы инструкции, которые поток будет выполнять все время жизненного цикла пула потоков. Как только у потока "пропадает работа", он останавливается при помощи условной переменной `cv` - `cv.wait` до того момента, когда при добавлении новой задачи в `ThreadPool::AddTask` его разбудят с помощью `cv.notify_one()`. Если задачи в пуле задач `tasks` обнаруживаются, то берется самая приоритетная задача на выполнение. 

При завершении работы или перезагрузке для завершения работы потоков, все потоки "будятся" с помощью `cv.notify_all()` и атомик переменная `run` получает значение `false`. 

В основной программе `src/main.cpp` существует 2 варианта работы, что контроллируется макросом `READ_FROM_FILE`, задающимся в `CMakeLists.txt` : 
- Ввод из консоли (команда сборки: `Cmake -DDEFINE_READ_FROM_FILE=OFF`)
- Чтение данных из файла (команда сборки:`Cmake`)

Приложение собирается с помощью CMake и должно работать на Windows, macOS, linux. 

