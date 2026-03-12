/*
std::future 和 std::async 这两个异步处理类提供了简单的接口用来处理异步任务和异步任务的返回值。
 */

#include <iostream>
#include <future> // 异步任务函数
int asyncFunc()
{
    // 执行一些耗时的任务...
    return 42;
}
int main()
{
    // 创建一个异步任务并执行 asyncFunc 函数
    std::future<int> fut = std::async(std::launch::async, asyncFunc);
    // 执行其他的操作...
    // 等待异步任务执行完成，并获取结果
    fut.wait();
    int result = fut.get();
    std::cout << "Async task completed with result: " << result << std::endl;
    return 0;
}
