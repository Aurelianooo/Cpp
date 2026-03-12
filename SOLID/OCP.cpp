/*
开闭原则是 SOLID 设计原则中的第二个原则，其核心思想是“软件实体应该对扩展开放，对修改关闭”。
这意味着一个系统的设计和实现应该使得它可以在不修改现有代码的情况下进行扩展。
开闭原则强调了设计的灵活性和可维护性，是构建大型复杂系统的关键方面。
开闭原则鼓励我们通过抽象来设计组件，使得组件的行为可以通过新增派生类来扩展，而不是通过修改现有的代码。
这种方法帮助开发者在不触碰原有代码的前提下，添加新功能或改变程序的行为。
 */

#include <iostream>
#include <string>

/*
如下 PaymentProcessor 类用于处理支付。最初的设计中，PaymentProcessor 直接实现了信用卡支付的处理逻辑。
随着系统的发展，如果需要支持新的支付方式，就需要修改 PaymentProcessor 类的代码，这违反了开闭原则。
 */
class PaymentProcessor1
{
public:
    void processPayment(const std::string &paymentType, double amount)
    {
        if (paymentType == "CreditCard")
        {
            std::cout << "Processing credit card payment of $" << amount << std::endl;
        }
        // 随着新支付方式的增加，这里需要不断修改和添加新的条件判断
    }
};

void func1()
{
    PaymentProcessor1 processor;
    processor.processPayment("CreditCard", 100.0);
}

/*
为了遵循开闭原则，引入一个抽象基类 PaymentMethod，它定义了一个纯虚函数 processPayment。
然后，为每种支付方式创建一个派生类。这样 PaymentProcessor 类可以使用这些派生类来处理具体的支付方式，而无须修改其代码。
 */
class PaymentMethod
{
public:
    virtual ~PaymentMethod() {}
    virtual void processPayment(double amount) = 0;
};

class CreditCardPayment : public PaymentMethod
{
public:
    void processPayment(double amount) override
    {
        std::cout << "Processing credit card payment of $" << amount << std::endl;
    }
};

class PayPalPayment : public PaymentMethod
{
public:
    void processPayment(double amount) override
    {
        std::cout << "Processing PayPal payment of $" << amount << std::endl;
    }
};

class PaymentProcessor2
{
public:
    void processPayment(PaymentMethod *method, double amount)
    {
        method->processPayment(amount);
    }
};

void func2()
{
    CreditCardPayment creditCard;
    PayPalPayment payPal;
    PaymentProcessor2 processor;
    processor.processPayment(&creditCard, 100.0);
    processor.processPayment(&payPal, 200.0);
}

int main()
{
    // func1();
    func2();

    return 0;
}