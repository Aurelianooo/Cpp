#include "iterator.hpp"

class Data
{
public:
    Data(int a = 0) : m_data_(a) {}

    void set_data(int a)
    {
        m_data_ = a;
    }

    int data()
    {
        return m_data_;
    }

private:
    int m_data_;
};

/**
 * The client code may or may not know about the Concrete Iterator or Collection
 * classes, for this implementation the container is generic so you can used
 * with an int or with a custom class.
 */
void ClientCode()
{
    std::cout << "-------Iterator with int-------" << std::endl;
    Container<int> cont;

    for (int i = 0; i < 10; i++)
    {
        cont.Add(i);
    }

    Iterator<int, Container<int>> *it = cont.CreateIterator();
    for (it->First(); !it->IsDone(); it->Next())
    {
        std::cout << *it->Current() << std::endl;
    }

    Container<Data> cont2;
    Data a(100), b(1000), c(10000);
    cont2.Add(a);
    cont2.Add(b);
    cont2.Add(c);

    std::cout << "-------Iterator with custom Class-------" << std::endl;
    Iterator<Data, Container<Data>> *it2 = cont2.CreateIterator();
    for (it2->First(); !it2->IsDone(); it2->Next())
    {
        std::cout << it2->Current()->data() << std::endl;
    }
    delete it;
    delete it2;
}

int main()
{
    ClientCode();
    return 0;
}
