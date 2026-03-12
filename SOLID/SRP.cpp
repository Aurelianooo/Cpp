/*
单一职责原则是 SOLID 设计原则中的第一个原则，核心思想是“一个类应该仅有一个引起它变化的原因”。
单一职责原则强调的是职责的单一性，意味着一个类应当只承担一种职责或功能。
若一个类承担过多的功能，它在软件系统中将扮演多个角色，这不仅会增加代码修改和维护的难度，还会影响到类的可复用性。
其中，职责可以理解为完成特定行为的义务或者必须履行的功能。在面向对象设计中，职责通常是指一个类中实现的功能。
识别职责是实现单一职责原则的第一步。通常，这涉及对系统的功能需求进行分析，确保每个类映射到单一的功能。
如果发现一个类支持多个不同的功能，应考虑将其拆分。
 */

#include <iostream>
#include <vector>
#include <string>

/*
如下类 ReportGenerator，它的职责包括生成报告数据、格式化输出以及打印报告。
这个类的设计违反了单一职责原则，因为它同时承担了数据处理、报告格式化和输出打印这 3 个不同的职责。
 */
class ReportGenerator
{
public:
    void gatherData()
    {
        // 模拟数据收集
        data.push_back("Data 1");
        data.push_back("Data 2");
        data.push_back("Data 3");
    }
    void formatReport()
    {
        for (const auto &d : data)
        {
            formattedData += d + "\n";
        }
    }
    void printReport() const
    {
        std::cout << formattedData;
    }

private:
    std::vector<std::string> data;
    std::string formattedData;
};

void func1()
{
    ReportGenerator report;
    report.gatherData();
    report.formatReport();
    report.printReport();
}

/*
为了遵守单一职责原则，可以将 ReportGenerator 拆分成 3 个类，每个类只负责一个功能：
DataCollector 类：负责收集报告所需的数据；
ReportFormatter 类：负责将数据格式化为报告格式；
ReportPrinter类：负责输出报告到控制台或其他媒介。
 */
class DataCollector
{
public:
    void gatherData()
    {
        data.push_back("Data 1");
        data.push_back("Data 2");
        data.push_back("Data 3");
    }
    const std::vector<std::string> &getData() const
    {
        return data;
    }

private:
    std::vector<std::string> data;
};

class ReportFormatter
{
public:
    void formatReport(const std::vector<std::string> &data)
    {
        for (const auto &d : data)
        {
            formattedData += d + "\n";
        }
    }
    const std::string &getFormattedData() const
    {
        return formattedData;
    }

private:
    std::string formattedData;
};

class ReportPrinter
{
public:
    void printReport(const std::string &report) const
    {
        std::cout << report;
    }
};

void func2()
{
    DataCollector collector;
    collector.gatherData();
    ReportFormatter formatter;
    formatter.formatReport(collector.getData());
    ReportPrinter printer;
    printer.printReport(formatter.getFormattedData());
}

int main()
{
    // func1();
    func2();

    return 0;
}
