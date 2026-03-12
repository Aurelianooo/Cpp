#include "strategy.hpp"

/**
 * The Context defines the interface of interest to clients.
 */
class Context
{
private:
    std::unique_ptr<Strategy> strategy_;

public:
    explicit Context(std::unique_ptr<Strategy> &&strategy = {})
        : strategy_(std::move(strategy))
    {
    }

    void set_strategy(std::unique_ptr<Strategy> &&strategy)
    {
        strategy_ = std::move(strategy);
    }

    void doSomeBusinessLogic() const
    {
        if (strategy_)
        {
            std::cout << "Context: Sorting data using the strategy (not sure how it works)\n";
            std::string result = strategy_->doAlgorithm("aecbd");
            std::cout << result << "\n";
        }
        else
        {
            std::cout << "Context: Strategy isn't set\n";
        }
    }
};

/**
 * Concrete Strategies implement the algorithm while following the base Strategy
 * interface. The interface makes them interchangeable in the Context.
 */
class ConcreteStrategyA : public Strategy
{
public:
    std::string doAlgorithm(const std::string &data) const override
    {
        std::string result(data);
        std::sort(std::begin(result), std::end(result));

        return result;
    }
};

class ConcreteStrategyB : public Strategy
{
public:
    std::string doAlgorithm(const std::string &data) const override
    {
        std::string result(data);
        std::sort(std::begin(result), std::end(result), std::greater<char>());

        return result;
    }
};

/**
 * The client code picks a concrete strategy and passes it to the context. The
 * client should be aware of the differences between strategies in order to make
 * the right choice.
 */
void clientCode()
{
    Context context(std::unique_ptr<ConcreteStrategyA>(new ConcreteStrategyA()));
    std::cout << "Client: Strategy is set to normal sorting.\n";
    context.doSomeBusinessLogic();
    std::cout << "Client: Strategy is set to reverse sorting.\n";
    context.set_strategy(std::unique_ptr<ConcreteStrategyB>(new ConcreteStrategyB()));
    context.doSomeBusinessLogic();
}

int main()
{
    clientCode();
    return 0;
}
