/*
接口隔离原则是 SOLID 设计原则中的第四个原则，它强调“客户端不应被迫依赖于它们不使用的接口”。
该原则建议将大的接口拆分成更小和更具体的接口，以确保实现类只需要关心它们真正需要的接口。
这样，实现类不会被迫实现它们不需要的方法，从而减少了接口的负担。
接口隔离原则鼓励将庞大的接口分解为更细小、专一的接口。
每个接口应该代表一个特定的角色或功能集合，只包含一个具体客户端（类或模块）所需的操作。
 */

#include <iostream>

/*
如下 MultiFunctionDevice 类，它代表了一个多功能设备，如打印机、扫描仪和复印机。
最初的设计是将所有功能都集中在一个接口中，这迫使实现该接口的类必须实现所有功能，即使某些功能对特定的设备来说是不必要的。
 */
class MultiFunctionDevice
{
public:
    virtual void print() = 0;
    virtual void scan() = 0;
    virtual void copy() = 0;
};

class PrinterScannerCopier1 : public MultiFunctionDevice
{
public:
    void print() override
    {
        std::cout << "Print document" << std::endl;
    }
    void scan() override
    {
        std::cout << "Scan document" << std::endl;
    }
    void copy() override
    {
        std::cout << "Copy document" << std::endl;
    }
};
// 假设需要一个只能打印的设备
class Printer1 : public MultiFunctionDevice
{
public:
    void print() override
    {
        std::cout << "Print document" << std::endl;
    }
    void scan() override
    {
        // 空实现，因为设备不支持
    }
    void copy() override
    {
        // 空实现，因为设备不支持
    }
};

/*
为了遵循接口隔离原则，可以将 MultiFunctionDevice 接口拆分为 3 个更小的接口：Printer、Scanner、Copier。
这样，不同的设备类可以只实现它们需要的接口。
 */
class Printer
{
public:
    virtual void print() = 0;
};

class Scanner
{
public:
    virtual void scan() = 0;
};

class Copier
{
public:
    virtual void copy() = 0;
};

class PrinterOnly : public Printer
{
public:
    void print() override
    {
        std::cout << "Print document" << std::endl;
    }
};

class PrinterScannerCopier2 : public Printer, public Scanner, public Copier
{
public:
    void print() override
    {
        std::cout << "Print document" << std::endl;
    }
    void scan() override
    {
        std::cout << "Scan document" << std::endl;
    }
    void copy() override
    {
        std::cout << "Copy document" << std::endl;
    }
};

int main()
{
    return 0;
}
