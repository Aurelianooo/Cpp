/*
纯虚函数（pure virtual function）是指被不负责具体实现的虚成员函数，它不具备函数的功能。
通常情况下，在基类中定义纯虚函数，在派生类中给出具体实现。
纯虚函数不能被直接调用，其作用是提供一个与派生类一致的[接口]。

包含纯虚函数的类称为[抽象类]，抽象类不能在程序中被实例化（即不能定义抽象类的对象），但可以定义指向抽象类的指针。
当基类是抽象类时，派生类中必须给出基类中纯虚函数的实现，或再次声明其为纯虚函数。
当派生类给出基类中纯虚函数的具体实现时，该派生类就不再是抽象类。
从抽象类派生的子类如果不是抽象类，则派生类必须实现基类中的[所有]纯虚函数。
软件架构师可以通过纯虚函数建立接口和抽象类，由具体程序员填写代码实现接口。

C++虚函数实现[动态绑定]：[多态]主要体现在虚函数上，只要存在虚函数，对象类型就在程序运行时动态绑定。
具体的实现方法是定义一个指向基类对象的指针变量，并使它指向同一类中需要调用该函数的对象，通过该指针变量调用此虚函数。
*/

#include <iostream>
using namespace std;

const double PI = 3.14;
// 定义图形类 CFigure，因含纯虚函数，为抽象类
class CFigure
{
public:
    // 声明纯虚函数，不提供实现
    virtual double getArea() = 0;
};

class CCircle : public CFigure
{
private:
    double m_dRadius;

public:
    CCircle(double dR)
    {
        m_dRadius = dR;
    }
    double getArea() override
    {
        return m_dRadius * m_dRadius * PI;
    }
};

class CRectangle : public CFigure
{
protected:
    double m_dHeight, m_dWidth;

public:
    CRectangle(double dHeight, double dWidth)
    {
        m_dHeight = dHeight;
        m_dWidth = dWidth;
    }
    double getArea() override
    {
        return m_dHeight * m_dWidth;
    }
};

void func1()
{
    CFigure *ptr;
    ptr = new CRectangle(4.0, 5.0);
    cout << ptr->getArea() << endl;
    delete ptr;
    ptr = NULL;

    ptr = new CCircle(4.0);
    cout << ptr->getArea() << endl;
    delete ptr;
}

/*
CBird 类和 CFish 类都继承自同一个 CAnimal 基类，
从 CBird 类和 CFish 类派生子类 CWaterBird 时，
CWaterBird 类中将存在两个 CAnimal 类的拷贝。

若想使其只存在一个 CAnimal 基类，需要使用[虚继承]机制。
 */

class CAnimal
{
public:
    CAnimal()
    {
        cout << "animal constructed" << endl;
    }

    void Move()
    {
        cout << "animal move" << endl;
    }
};

class CBird : virtual public CAnimal
{
public:
    CBird()
    {
        cout << "bird constructed" << endl;
    }

    void FlyInSky()
    {
        cout << "bird fly" << endl;
    }

    void Breath()
    {
        cout << "bird breath" << endl;
    }
};

class CFish : virtual public CAnimal
{
public:
    CFish()
    {
        cout << "fish constructed" << endl;
    }

    void SwimInWater()
    {
        cout << "fish swim" << endl;
    }

    void Breath()
    {
        cout << "fish breath" << endl;
    }
};

class CWaterBird : public CBird, public CFish
{
public:
    CWaterBird()
    {
        cout << "water bird constructed" << endl;
    }

    void Action()
    {
        cout << "water bird fly and swim" << endl;
    }
};

void func2()
{
    CWaterBird waterbird;
}

int main()
{
    // func1();
    func2();

    return 0;
}
