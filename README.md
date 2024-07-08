# thread-pool test assignment

You need to implement a ThreadPool that can do any work in one of the pre-created worker threads, as well as a console application that demonstrates how the ThreadPool works. If the user enters "restart", then the existing ThreadPool is destroyed and a new one is created with a larger number of worker threads.

If the user enters "exit", the application ends. If the user entered two numbers, then the application sends work to the ThreadPool to calculate all prime factors of the first number (uint64), and the second number is needed to set the priority for this task. After completing the work, you need to output the result to the console.

The program is better off written in the new C++, because the new C++ has threads, synchronization primitives and a lot of other good things. The best way to build is to use CMake.

# Solution explained (in Russian)
Создан класс ```ThreadPool```, который содержит в себе очередь с приоритетом для задач ```std::priority_queue<Task> tasks```, а также массив потоков ```std::vector<std::thread> threads```. 
Для доступа к массиву задач используется мьютекс ```std::mutex tasksMutex```, а для передачи информации о необходимости потокам продолжать или заканчивать работу задействован ```std::atomic<bool> run```.

Также создана структура для данных каждой задачи ```struct Task```. В функции ```ThreadJob()``` реализованы инструкции, которые поток будет выполнять все время жизненного цикла пула потоков. Как только у потока "пропадает работа", т.е. отсутствуют задачи, он засыпает. В противном случае он, используя мьютекс, берет самую приоритетную задачу и выполняет ее. 
> Надо заметить, что идея с засыпанием - не самая удачная. Автор имеет некоторое представление о conditional variables, но он немного устал и решил не мудрствовать лукаво, оставив эту часть, как есть. 

В основной программе `src/main.cpp` существует 2 варианта работы, что контроллируется макросом `READ_FROM_FILE`, задающимся в `CMakeLists.txt` : 
- Ввод из консоли 
- Чтение данных из файла

Приложение собирается с помощью CMake и должно работать на Windows, macOS, linux. 


