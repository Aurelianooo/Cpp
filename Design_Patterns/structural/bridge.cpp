#include "bridge.hpp"

/**
 * Each Concrete Implementation corresponds to a specific platform and
 * implements the Implementation interface using that platform's API.
 */
class ConcreteImplementationA : public Implementation
{
public:
    std::string OperationImplementation() const override
    {
        return "ConcreteImplementationA: Here's the result on the platform A.\n";
    }
};

class ConcreteImplementationB : public Implementation
{
public:
    std::string OperationImplementation() const override
    {
        return "ConcreteImplementationB: Here's the result on the platform B.\n";
    }
};

/**
 * You can extend the Abstraction without changing the Implementation classes.
 */
class ExtendedAbstraction : public Abstraction
{
public:
    ExtendedAbstraction(Implementation *implementation) : Abstraction(implementation)
    {
    }
    std::string Operation() const override
    {
        return "ExtendedAbstraction: Extended operation with:\n" +
               this->implementation_->OperationImplementation();
    }
};

/**
 * Except for the initialization phase, where an Abstraction object gets linked
 * with a specific Implementation object, the client code should only depend on
 * the Abstraction class. This way the client code can support any abstraction-
 * implementation combination.
 *
 * The client code should be able to work with any pre-configured abstraction-
 * implementation combination.
 */
void ClientCode(const Abstraction &abstraction)
{
    // ...
    std::cout << abstraction.Operation();
    // ...
}

int main()
{
    Implementation *implementation = new ConcreteImplementationA;
    Abstraction *abstraction = new Abstraction(implementation);
    ClientCode(*abstraction);
    delete implementation;
    delete abstraction;

    implementation = new ConcreteImplementationB;
    abstraction = new ExtendedAbstraction(implementation);
    ClientCode(*abstraction);
    delete implementation;
    delete abstraction;

    return 0;
}
