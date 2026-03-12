#include <iostream>
#include <string>
#include <vector>

/**
 * The Handler interface declares a method for building the chain of handlers.
 * It also declares a method for executing a request.
 */
class Handler
{
public:
    virtual Handler *SetNext(Handler *handler) = 0;
    virtual std::string Handle(std::string request) = 0;
};

/**
 * The default chaining behavior can be implemented inside a base handler class.
 */
class AbstractHandler : public Handler
{
    /**
     * @var Handler
     */
private:
    Handler *next_handler_;

public:
    AbstractHandler() : next_handler_(nullptr)
    {
    }
    Handler *SetNext(Handler *handler) override
    {
        this->next_handler_ = handler;
        // Returning a handler from here will let us link handlers in a convenient
        // way like this:
        // $monkey->setNext($squirrel)->setNext($dog);
        return handler;
    }
    std::string Handle(std::string request) override
    {
        if (this->next_handler_)
        {
            return this->next_handler_->Handle(request);
        }

        return {};
    }
};
