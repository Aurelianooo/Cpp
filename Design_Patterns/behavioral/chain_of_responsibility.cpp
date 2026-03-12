#include "chain_of_responsibility.hpp"

/**
 * All Concrete Handlers either handle a request or pass it to the next handler
 * in the chain.
 */
class MonkeyHandler : public AbstractHandler
{
public:
    std::string Handle(std::string request) override
    {
        if (request == "Banana")
        {
            return "Monkey: I'll eat the " + request + ".\n";
        }
        else
        {
            return AbstractHandler::Handle(request);
        }
    }
};

class SquirrelHandler : public AbstractHandler
{
public:
    std::string Handle(std::string request) override
    {
        if (request == "Nut")
        {
            return "Squirrel: I'll eat the " + request + ".\n";
        }
        else
        {
            return AbstractHandler::Handle(request);
        }
    }
};

class DogHandler : public AbstractHandler
{
public:
    std::string Handle(std::string request) override
    {
        if (request == "MeatBall")
        {
            return "Dog: I'll eat the " + request + ".\n";
        }
        else
        {
            return AbstractHandler::Handle(request);
        }
    }
};

/**
 * The client code is usually suited to work with a single handler. In most
 * cases, it is not even aware that the handler is part of a chain.
 */
void ClientCode(Handler &handler)
{
    std::vector<std::string> food = {"Nut", "Banana", "Cup of coffee", "MeatBall"};
    for (const std::string &f : food)
    {
        std::cout << "Client: Who wants a " << f << "?\n";
        const std::string result = handler.Handle(f);
        if (!result.empty())
        {
            std::cout << "  " << result;
        }
        else
        {
            std::cout << "  " << f << " was left untouched.\n";
        }
    }
}
/**
 * The other part of the client code constructs the actual chain.
 */

int main()
{
    MonkeyHandler *monkey = new MonkeyHandler;
    SquirrelHandler *squirrel = new SquirrelHandler;
    DogHandler *dog = new DogHandler;
    monkey->SetNext(squirrel)->SetNext(dog);

    /**
     * The client should be able to send a request to any handler, not just the
     * first one in the chain.
     */
    std::cout << "Chain: Monkey > Squirrel > Dog\n";
    ClientCode(*monkey);
    std::cout << "Subchain: Squirrel > Dog\n";
    ClientCode(*squirrel);

    delete monkey;
    delete squirrel;
    delete dog;

    return 0;
}
