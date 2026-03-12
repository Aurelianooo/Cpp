#include "template_method.hpp"

/**
 * Concrete classes have to implement all abstract operations of the base class.
 * They can also override some operations with a default implementation.
 */
class ConcreteClass1 : public AbstractClass
{
protected:
    void RequiredOperations1() const override
    {
        std::cout << "ConcreteClass1 says: Implemented Operation1\n";
    }
    void RequiredOperation2() const override
    {
        std::cout << "ConcreteClass1 says: Implemented Operation2\n";
    }
};
/**
 * Usually, concrete classes override only a fraction of base class' operations.
 */
class ConcreteClass2 : public AbstractClass
{
protected:
    void RequiredOperations1() const override
    {
        std::cout << "ConcreteClass2 says: Implemented Operation1\n";
    }
    void RequiredOperation2() const override
    {
        std::cout << "ConcreteClass2 says: Implemented Operation2\n";
    }
    void Hook1() const override
    {
        std::cout << "ConcreteClass2 says: Overridden Hook1\n";
    }
};

/**
 * The client code calls the template method to execute the algorithm. Client
 * code does not have to know the concrete class of an object it works with, as
 * long as it works with objects through the interface of their base class.
 */
void ClientCode(AbstractClass *class_)
{
    // ...
    class_->TemplateMethod();
    // ...
}

int main()
{
    std::cout << "Same client code can work with different subclasses:\n";
    ConcreteClass1 *concreteClass1 = new ConcreteClass1;
    ClientCode(concreteClass1);
    std::cout << "Same client code can work with different subclasses:\n";
    ConcreteClass2 *concreteClass2 = new ConcreteClass2;
    ClientCode(concreteClass2);
    delete concreteClass1;
    delete concreteClass2;
    return 0;
}
