/*
事件驱动架构(EDA)是一种软件架构范式，其核心思想是系统中的各个组件（或服务）之间通过事件进行通信和交互，而不是直接的调用或请求－响应式的方式：

事件驱动：在事件驱动架构中，系统中的各个组件可以是事件的发布者、订阅者或者两者兼具。
        当一个组件执行某些操作时，它可以产生一个事件，并将其发布到系统中，其他组件可以订阅这些事件并做出相应的响应；
松耦合：EDA 鼓励松散耦合的设计，因为组件之间的通信是通过事件进行的，而不是直接的调用。
       这使得系统更加灵活，组件可以独立地演化和扩展，而不会影响到其他组件；
异步通信：事件驱动架构通常采用异步通信方式，组件发布事件后不需要等待其他组件的响应，而是继续执行自己的任务。
        这种方式可以提高系统的响应性能和可扩展性；
事件处理：在事件驱动架构中，系统中的事件可以被处理和转换成其他形式，从而触发新的事件或者更新系统状态。
        事件处理器通常用来监听特定类型的事件，并执行相应的逻辑；
事件流：在复杂的系统中，事件可以形成事件流，表示一系列相关联的事件。
       事件流可以用来分析系统的行为、监控系统的健康状态以及实现复杂的业务逻辑。

总的来说，事件驱动架构通过将系统的各个组件解耦，采用异步、事件驱动的方式来实现系统之间的通信和协作，从而提高了系统的灵活性、可扩展性和可维护性。

以下示例通过触发事件来调用相应的回调函数。这种设计使得组件之间的通信更加灵活，适用于简单的事件处理场景，但在复杂的系统中，可能需要考虑更多的因素，例如：
事件类型和分类：在实际系统中，可能存在多种类型的事件，需要对事件进行分类和管理。这可能涉及事件的层级结构、事件的优先级和相关性等方面；
事件的传递和路由：在大型系统中，事件可能需要在不同的组件之间进行传递和路由。这可能涉及事件的转发、过滤和路由策略的设计；
异步处理和并发控制：在高并发的环境下，可能需要考虑事件的异步处理和并发控制。这可能涉及多线程、线程池和同步机制的设计；
错误处理和容错机制：在复杂的系统中，可能会出现各种错误和异常情况，需要考虑事件的错误处理和容错机制。这可能涉及异常处理、事务管理和回滚机制的设计。
 */
#include <iostream>
#include <vector>
#include <functional>
// 事件类型枚举
enum class EventType
{
    EVENT_1,
    EVENT_2,
    EVENT_3
};
// 事件处理器
class EventHandler
{
public:
    // 注册回调函数
    void registerCallback(EventType event, std::function<void()> callback)
    {
        callbacks[static_cast<int>(event)].push_back(callback);
    }
    // 触发事件
    void triggerEvent(EventType event)
    {
        for (auto &callback : callbacks[static_cast<int>(event)])
        {
            callback();
        }
    }

private:
    std::vector<std::function<void()>> callbacks[3]; // 事件回调函数列表
};

int main()
{
    // 创建事件处理器
    EventHandler eventHandler;
    // 注册事件1的回调函数
    eventHandler.registerCallback(EventType::EVENT_1, []()
                                  { std::cout << "Event 1 occurred!" << std::endl; });
    // 注册事件2的回调函数
    eventHandler.registerCallback(EventType::EVENT_2, []()
                                  { std::cout << "Event 2 occurred!" << std::endl; });
    // 触发事件
    eventHandler.triggerEvent(EventType::EVENT_1);
    eventHandler.triggerEvent(EventType::EVENT_2);
    return 0;
}
