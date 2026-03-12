/*
自旋锁是一种在等待释放锁的过程中持续检查锁状态的锁，不释放当前线程的执行权。
自旋锁适用于锁持有时间极短的情况，因为它可以避免线程上下文切换的开销。
然而，如果持有锁的时间较长，自旋锁可能导致CPU时间的浪费。
编译语句：g++ XXX.cpp -std=c++11 -pthread
 */

#include <atomic>
#include <thread>
#include <iostream>
#include <pthread.h>

/*
std::atomic_flag 作为原子类型，专为构建无锁的同步机制而设计。
尽管它本身不是锁，但它的这些特性使其成为实现自旋锁的理想选择。
自旋锁是一种忙等锁，其中线程反复检查锁的状态，而不是进入阻塞状态。
这在等待时间非常短的场景中非常有效，因为它避免了线程挂起和恢复带来的开销。
 */
class SpinLock
{
private:
    std::atomic_flag flag = ATOMIC_FLAG_INIT;

public:
    void lock()
    {
        while (flag.test_and_set(std::memory_order_acquire))
            ; // 等待直到锁被释放
    }
    void unlock()
    {
        flag.clear(std::memory_order_release);
    }
};

void task(SpinLock &spinlock)
{
    spinlock.lock();
    // 执行临界区代码
    std::cout << "Thread " << std::this_thread::get_id()
              << " entered critical section.\n";
    spinlock.unlock();
}

void func1()
{
    SpinLock spinlock;
    std::thread t1(task, std::ref(spinlock));
    std::thread t2(task, std::ref(spinlock));
    t1.join();
    t2.join();
}

/*
使用 UNIX/Linux 系统的时候，可以使用 POSIX 线程库提供的自旋锁。
其中 pthread_spinlock_t 是 POSIX 线程库中提供的一种自旋锁实现，专为多线程应用中的轻量级同步而设计。
 */
// 定义全局变量和自旋锁
int sharedVariable = 0;
pthread_spinlock_t spinlock;
// 线程函数
void *threadFunction(void *arg)
{
    int thread_id = *(int *)arg;
    // 加锁
    pthread_spin_lock(&spinlock);
    // 临界区
    std::cout << "Thread " << thread_id
              << " is incrementing sharedVariable..." << std::endl;
    sharedVariable++;
    // 解锁
    pthread_spin_unlock(&spinlock);
    pthread_exit(NULL);
}

void func2()
{
    // 初始化自旋锁
    pthread_spin_init(&spinlock, PTHREAD_PROCESS_PRIVATE);
    // 创建线程
    pthread_t thread1, thread2;
    int id1 = 1, id2 = 2;
    pthread_create(&thread1, NULL, threadFunction, &id1);
    pthread_create(&thread2, NULL, threadFunction, &id2);
    // 等待线程结束
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    // 销毁自旋锁
    pthread_spin_destroy(&spinlock);
    // 输出结果
    std::cout << "sharedVariable = " << sharedVariable << std::endl;
}

int main()
{
    // func1();
    func2();

    return 0;
}