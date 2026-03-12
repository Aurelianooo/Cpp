#include <iostream>
#include <string>

/**
 * The Implementation defines the interface for all implementation classes. It
 * doesn't have to match the Abstraction's interface. In fact, the two
 * interfaces can be entirely different. Typically the Implementation interface
 * provides only primitive operations, while the Abstraction defines higher-
 * level operations based on those primitives.
 */
class Implementation
{
public:
    virtual ~Implementation() {}
    virtual std::string OperationImplementation() const = 0;
};

/**
 * The Abstraction defines the interface for the "control" part of the two class
 * hierarchies. It maintains a reference to an object of the Implementation
 * hierarchy and delegates all of the real work to this object.
 */
class Abstraction
{
    /**
     * @var Implementation
     */
protected:
    Implementation *implementation_;

public:
    Abstraction(Implementation *implementation) : implementation_(implementation)
    {
    }

    virtual ~Abstraction() {}
    virtual std::string Operation() const
    {
        return "Abstraction: Base operation with:\n" +
               this->implementation_->OperationImplementation();
    }
};
