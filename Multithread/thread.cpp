/*
在 C++11 之前，如果要进行多线程开发，则需要调用系统或者第三方提供的 API，
例如在 Linux 系统下需要调用 pthread 的一组 API，在 Windows 系统下则需要调用 CreateThread() 的一组 API。
这种操作导致代码需要在不同的操作系统上各个独立写一遍，造成代码量增加，从而使模块的通用性降低。

从 C++11 开始引入了对多线程编程的支持，包括头文件和相关的类和函数，使在 C++ 中使用多线程变得更加简便和安全。
通过 std::thread 类可以创建新的线程，并指定线程要执行的函数或函数对象，还可以将参数传递给线程函数。
std::thread 类提供了一些控制线程的方法，例如 join() 方法可以等待一个线程执行完成，
detach() 方法可以将一个线程分离，使线程的执行与主线程独立。
编译语句：g++ XXX.cpp -std=c++11 -pthread
 */

#include <iostream>
#include <thread>
// 线程函数 1
void threadFunc1()
{
    std::cout << "Thread 1 running" << std::endl;
    // 执行一些任务...
}
// 线程函数 2
void threadFunc2(int numIterations)
{
    std::cout << "Thread 2 running" << std::endl;
    for (int i = 0; i < numIterations; ++i)
    {
        // 执行一些任务...
    }
}
int main()
{
    // 创建线程 1，并执行 threadFunc1 函数
    std::thread t1(threadFunc1);
    // 创建线程 2，并执行 threadFunc2 函数，传递参数 10 作为 numIterations
    std::thread t2(threadFunc2, 10);
    // 等待线程 1 和线程 2 执行完成
    t1.join();
    t2.join();
    std::cout << "Main thread exiting" << std::endl;
    return 0;
}
