/*
里氏替换原则是 SOLID 设计原则中的第三个原则。
该原则指出，如果程序中使用了某个基类的对象，那么在不改变程序正确性的情况下，应能够用其派生类的对象来替换这个基类对象。
这个原则强调了继承机制的正确使用，确保派生类能够完全代替其基类。
 */

#include <iostream>
#include <string>

/*
初始设计：考虑一个图形界面组件的类层次结构，其中包含一个基类 Widget 和两个派生类 Button 和 TextBox。
基类 Widget 有一个 draw() 方法，用于绘制组件。
假设 TextBox 的 draw() 方法实现引入了额外的条件——只在文本框非空时绘制。
这违反了 LSP，因为它改变了基类 Widget 的基本行为，使得 TextBox 在某些条件下不执行任何绘制操作。
 */
class Widget
{
public:
    virtual void draw()
    {
        std::cout << "Drawing Widget" << std::endl;
    }
};

class Button : public Widget
{
public:
    void draw() override
    {
        std::cout << "Drawing Button" << std::endl;
    }
};

class TextBox1 : public Widget
{
private:
    std::string text;

public:
    TextBox1(const std::string &txt) : text(txt) {}
    void draw() override
    {
        if (!text.empty())
        {
            std::cout << "Drawing TextBox: " << text << std::endl;
        }
        else
        {
            // 不绘制任何东西，违反了Widget的预期行为
        }
    }
};

void renderScreen(Widget *widget)
{
    widget->draw();
}

void func1()
{
    Widget *w = new Widget();
    Widget *b = new Button();
    Widget *t = new TextBox1("Hello");
    renderScreen(w);
    renderScreen(b);
    renderScreen(t);
    delete w;
    delete b;
    delete t;
}

/*
为了保持 TextBox 类的行为与 Widget 基类一致，需要修改 TextBox 的 draw() 方法以确保它在所有情况下都执行一些形式的绘制操作。
即使在没有文本时也应至少调用基类的绘制方法，这样可以确保 TextBox 类可以无缝替换 Widget 类，而不会导致程序行为的任何变化。
 */
class TextBox2 : public Widget
{
private:
    std::string text;

public:
    TextBox2(const std::string &txt) : text(txt) {}
    void draw() override
    {
        if (!text.empty())
        {
            std::cout << "Drawing TextBox: " << text << std::endl;
        }
        else
        { // 为了保持与 Widget 类的行为一致，即使没有文本也进行绘制
            std::cout << "Drawing TextBox" << std::endl;
        }
    }
};

void func2()
{
    Widget *w = new Widget();
    Widget *b = new Button();
    Widget *t = new TextBox2("");
    renderScreen(w);
    renderScreen(b);
    renderScreen(t);
    delete w;
    delete b;
    delete t;
}

int main()
{
    // func1();
    func2();

    return 0;
}
