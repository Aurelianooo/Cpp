#include "memento.hpp"

/**
 * The Concrete Memento contains the infrastructure for storing the Originator's
 * state.
 */
class ConcreteMemento : public Memento
{
private:
    std::string state_;
    std::string date_;

public:
    ConcreteMemento(std::string state) : state_(state)
    {
        this->state_ = state;
        std::time_t now = std::time(0);
        this->date_ = std::ctime(&now);
        if (!date_.empty() && date_.back() == '\n')
            date_.pop_back();
    }
    /**
     * The Originator uses this method when restoring its state.
     */
    std::string state() const override
    {
        return this->state_;
    }
    /**
     * The rest of the methods are used by the Caretaker to display metadata.
     */
    std::string GetName() const override
    {
        return this->date_ + " / (" + this->state_.substr(0, 9) + "...)";
    }
    std::string date() const override
    {
        return this->date_;
    }
};

/**
 * The Originator holds some important state that may change over time. It also
 * defines a method for saving the state inside a memento and another method for
 * restoring the state from it.
 */
class Originator
{
    /**
     * @var string For the sake of simplicity, the originator's state is stored
     * inside a single variable.
     */
private:
    std::string state_;

    std::string GenerateRandomString(int length = 10)
    {
        const char alphanum[] =
            "0123456789"
            "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
            "abcdefghijklmnopqrstuvwxyz";
        int stringLength = sizeof(alphanum) - 1;

        std::string random_string;
        for (int i = 0; i < length; i++)
        {
            random_string += alphanum[std::rand() % stringLength];
        }
        return random_string;
    }

public:
    Originator(std::string state) : state_(state)
    {
        std::cout << "Originator: My initial state is: " << this->state_ << "\n";
    }
    /**
     * The Originator's business logic may affect its internal state. Therefore,
     * the client should backup the state before launching methods of the business
     * logic via the save() method.
     */
    void DoSomething()
    {
        std::cout << "Originator: I'm doing something important.\n";
        this->state_ = this->GenerateRandomString(24);
        std::cout << "Originator: and my state has changed to: " << this->state_ << "\n";
    }

    /**
     * Saves the current state inside a memento.
     */
    Memento *Save()
    {
        return new ConcreteMemento(this->state_);
    }
    /**
     * Restores the Originator's state from a memento object.
     */
    void Restore(Memento *memento)
    {
        this->state_ = memento->state();
        std::cout << "Originator: My state has changed to: " << this->state_ << "\n";
        delete memento;
    }
};

/**
 * The Caretaker doesn't depend on the Concrete Memento class. Therefore, it
 * doesn't have access to the originator's state, stored inside the memento. It
 * works with all mementos via the base Memento interface.
 */
class Caretaker
{
    /**
     * @var Memento[]
     */
private:
    std::vector<Memento *> mementos_;

    /**
     * @var Originator
     */
    Originator *originator_;

public:
    Caretaker(Originator *originator) : originator_(originator)
    {
    }

    ~Caretaker()
    {
        for (auto m : mementos_)
            delete m;
    }

    void Backup()
    {
        std::cout << "Caretaker: Saving Originator's state...\n";
        this->mementos_.push_back(this->originator_->Save());
    }
    void Undo()
    {
        if (!this->mementos_.size())
        {
            return;
        }
        Memento *memento = this->mementos_.back();
        this->mementos_.pop_back();
        std::cout << "Caretaker: Restoring state to: " << memento->GetName() << "\n";
        try
        {
            this->originator_->Restore(memento);
        }
        catch (...)
        {
            this->Undo();
        }
    }
    void ShowHistory() const
    {
        std::cout << "Caretaker: Here's the list of mementos:\n";
        for (Memento *memento : this->mementos_)
        {
            std::cout << memento->GetName() << "\n";
        }
    }
};

void ClientCode()
{
    Originator *originator = new Originator("Super-duper-super-puper-super.");
    Caretaker *caretaker = new Caretaker(originator);
    caretaker->Backup();
    originator->DoSomething();
    caretaker->Backup();
    originator->DoSomething();
    caretaker->Backup();
    originator->DoSomething();
    caretaker->ShowHistory();
    std::cout << "Client: Now, let's rollback!\n";
    caretaker->Undo();
    std::cout << "Client: Once more!\n";
    caretaker->Undo();

    delete originator;
    delete caretaker;
}

int main()
{
    std::srand(static_cast<unsigned int>(std::time(NULL)));
    ClientCode();
    return 0;
}
