/*
条件变量 condition_variable 用于线程之间的等待和通知。
它可以让一个线程等待，直到满足某个条件然后由另一个线程通知它继续执行。
condition_variable 需要配合 mutex 一起使用以确保线程安全。
当线程等待某个条件时，它会释放已经持有的锁，进入等待状态。
当另一个线程满足了条件并进行通知时，等待的线程被唤醒，重新获取锁，并继续执行。
 */

#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
using namespace std;

mutex mtx;                     // 互斥量，用于保护共享数据
condition_variable cv;         // 条件变量
bool is_consume_ready = false; // 消费者准备好的标志
int data = 0;                  // 共享数据

/*
lock_guard 是简单锁：只能在作用域内自动加锁/解锁，没有任何额外操作，适合逻辑简单的临界区。
 */
void producer()
{
    this_thread::sleep_for(chrono::seconds(1)); // 模拟生产过程
    lock_guard<mutex> lock(mtx);                // 加锁
    // 更新共享数据
    data = 42;
    is_consume_ready = true;
    cv.notify_one(); // 通知等待的消费者线程
}

/*
unique_lock 是全能锁：可以手动解锁、支持条件变量等待，适合需要灵活控制锁的场景。
另外 cv.wait() 的参数要求必须是 unique_lock 类型。
 */
void consumer()
{
    unique_lock<mutex> lock(mtx); // 加锁
    cv.wait(lock, []
            { return is_consume_ready; }); // 等待条件满足
    // 执行消费操作
    cout << "Consumed data: " << data << endl;
}

int main()
{
    thread t1(producer);
    thread t2(consumer);
    t1.join();
    t2.join();
    return 0;
}
