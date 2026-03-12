#include <iostream>
#include <string>
#include <algorithm>

/**
 * The Target defines the domain-specific interface used by the client code.
 */
class Target
{
public:
    virtual ~Target() = default;

    virtual std::string Request() const
    {
        return "Target: The default target's behavior.";
    }
};

/**
 * The Adaptee contains some useful behavior, but its interface is incompatible
 * with the existing client code. The Adaptee needs some adaptation before the
 * client code can use it.
 */
class Adaptee
{
public:
    std::string SpecificRequest() const
    {
        return ".eetpadA eht fo roivaheb laicepS";
    }
};
