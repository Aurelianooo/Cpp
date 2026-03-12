#include <iostream>
#include <vector>

/**
 * The Builder interface specifies methods for creating the different parts of
 * the Product objects.
 */
class Builder
{
public:
    virtual ~Builder() {}
    virtual void ProducePartA() const = 0;
    virtual void ProducePartB() const = 0;
    virtual void ProducePartC() const = 0;
};

/**
 * The Director is only responsible for executing the building steps in a
 * particular sequence. It is helpful when producing products according to a
 * specific order or configuration. Strictly speaking, the Director class is
 * optional, since the client can control builders directly.
 */
class Director
{
    /**
     * @var Builder
     */
private:
    Builder *builder;

    /**
     * The Director works with any builder instance that the client code passes
     * to it. This way, the client code may alter the final type of the newly
     * assembled product.
     */
public:
    void set_builder(Builder *builder)
    {
        this->builder = builder;
    }

    /**
     * The Director can construct several product variations using the same
     * building steps.
     */
    void BuildMinimalViableProduct()
    {
        this->builder->ProducePartA();
    }

    void BuildFullFeaturedProduct()
    {
        this->builder->ProducePartA();
        this->builder->ProducePartB();
        this->builder->ProducePartC();
    }
};
