/*
当多个线程同时访问和修改共享数据时，可能会导致数据竞争和不确定的行为。
为了确保线程之间的数据同步和避免竞态条件，可以使用互斥量（Mutex）。

互斥量是一种同步原语，用于保护共享数据，只允许一个线程在任意时刻访问共享数据。
互斥量通过 lock() 和 unlock() 方法实现加锁和解锁操作。
 */

#include <iostream>
#include <thread>
#include <mutex> // 互斥量，用于保护共享数据
std::mutex mtx;  // 共享数据
int counter = 0;
void increment()
{
    std::lock_guard<std::mutex> lock(mtx); // 加锁
    // 修改共享数据
    counter++;
    // 执行其他操作...
} // 函数结束时，lock对象生命周期结束，std::lock_guard的析构函数会自动调用 unlock()

int main()
{
    std::thread t1(increment);
    std::thread t2(increment);
    t1.join();
    t2.join();
    std::cout << "Counter value: " << counter << std::endl;
    return 0;
}
