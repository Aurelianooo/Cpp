#include <iostream>
#include <array>

/**
 * The Visitor Interface declares a set of visiting methods that correspond to
 * component classes. The signature of a visiting method allows the visitor to
 * identify the exact class of the component that it's dealing with.
 */
class ConcreteComponentA;
class ConcreteComponentB;

class Visitor
{
public:
    virtual void VisitConcreteComponentA(const ConcreteComponentA *element) const = 0;
    virtual void VisitConcreteComponentB(const ConcreteComponentB *element) const = 0;
};

/**
 * The Component interface declares an `accept` method that should take the base
 * visitor interface as an argument.
 */

class Component
{
public:
    virtual ~Component() {}
    virtual void Accept(Visitor *visitor) const = 0;
};
