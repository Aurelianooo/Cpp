/*
依赖注入（dependency injection，DI）是一种设计模式，用于实现对象间的松耦合。
通过将对象的依赖关系外部化并由容器进行管理，DI可以有效地提高模块的可维护性和灵活性。
依赖注入是控制反转（inversion of control，IoC）的一种实现形式，它将对象的依赖关系从内部转移到外部，
使得对象不再直接依赖具体的实现类，而是依赖抽象接口。

依赖注入通常有 3 种实现方式：构造函数注入，Setter 方法注入和接口注入。
 */

#include <iostream>

/* 构造函数注入是最常见的依赖注入方式，通过构造函数显式地将依赖传递给目标对象。 */
class IService
{ // 抽象接口
public:
    virtual void execute() = 0;
};

class ConcreteService : public IService
{ // 具体实现
public:
    void execute() override
    {
        // 实现具体逻辑
    }
};

class Client1
{ // 客户端类
private:
    IService *service;

public:
    // 通过构造函数注入依赖
    Client1(IService *svc) : service(svc) {}
    void doSomething()
    {
        service->execute();
    }
};

void func1()
{
    ConcreteService service;
    Client1 client(&service);
    client.doSomething();
}

/* 抽象接口和具体实现都是一致的，而 Setter 方法注入允许依赖对象在实例化之后进行设置，从而提供了更大的灵活性。 */
class Client2
{
private:
    IService *service;

public:
    Client2() : service(nullptr) {}

    void setService(IService *svc)
    {
        service = svc;
    }

    void doSomething()
    {
        if (service)
        {
            service->execute();
        }
    }
};

void func2()
{
    ConcreteService service;
    Client2 client;
    client.setService(&service);
    client.doSomething();
}

/* 接口注入是一种更为高级的依赖注入方式，通过实现特定的接口将依赖传递给目标对象。 */
class IClient
{
public:
    virtual void setService(IService *svc) = 0;
};

class Client3 : public IClient
{
private:
    IService *service;

public:
    Client3() : service(nullptr) {}

    void setService(IService *svc) override
    {
        service = svc;
    }

    void doSomething()
    {
        if (service)
        {
            service->execute();
        }
    }
};

void func3()
{
    ConcreteService service;
    Client3 client;
    client.setService(&service);
    client.doSomething();
}

int main()
{
    // func1();
    // func2();
    func3();

    return 0;
}
