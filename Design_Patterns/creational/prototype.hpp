#include <iostream>
#include <string>
#include <unordered_map>

using std::string;

/**
 * Prototype Design Pattern
 * Intent: Lets you copy existing objects without making your code dependent on
 * their classes.
 */
enum Type
{
    PROTOTYPE_1 = 0,
    PROTOTYPE_2
};

/**
 * The example class that has cloning ability. We'll see how the values of field
 * with different types will be cloned.
 */
class Prototype
{
protected:
    string prototype_name_;
    float prototype_field_;

public:
    Prototype() {}
    Prototype(string prototype_name)
        : prototype_name_(prototype_name) {}
    virtual ~Prototype() {}
    virtual Prototype *Clone() const = 0;
    virtual void Method(float prototype_field)
    {
        this->prototype_field_ = prototype_field;
        std::cout << "Call Method from " << prototype_name_ << " with field: " << prototype_field << std::endl;
    }
};
