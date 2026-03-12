/*
依赖倒置原则是 SOLID 设计原则中的第五个原则。
该原则强调“高层模块不应依赖于低层模块，两者都应依赖于抽象；抽象不应依赖于细节，细节应依赖于抽象”。
DIP 主张在软件组件之间建立稳定的抽象，使得高层（策略性和复杂的决策逻辑）和低层（具体的操作细节）的模块都依赖于这些抽象。
 */

#include <iostream>
#include <fstream>
#include <string>

/*
如下是一个应用程序，它需要记录信息。
最初的设计直接依赖于一个具体的日志记录类，这意味着高层模块（如业务逻辑类）直接依赖于低层模块（如文件日志记录器）。
 */
class FileLogger1
{ // 低层模块
public:
    void logMessage(const std::string &message)
    {
        std::ofstream logFile("log.txt", std::ios::app);
        logFile << message << std::endl;
        logFile.close();
    }
};

class Application1
{ // 高层模块
private:
    FileLogger1 logger;

public:
    void process()
    {
        // 业务逻辑
        logger.logMessage("Process started.");
        // 更多业务逻辑...
        logger.logMessage("Process finished.");
    }
};

/* 
为了遵循依赖倒置原则，首先定义一个抽象的日志接口，然后让高层模块依赖于这个接口，而不是具体的日志记录实现。
这样，不同的日志记录方式（如文件记录、数据库记录或网络日志记录）可以通过不同的实现类提供服务，而无须修改高层模块。
 */
class ILogger
{ // 抽象接口
public:
    virtual ~ILogger() {}
    virtual void logMessage(const std::string &message) = 0;
};

class FileLogger2 : public ILogger
{ // 具体实现：文件日志记录
public:
    void logMessage(const std::string &message) override
    {
        std::ofstream logFile("log.txt", std::ios::app);
        logFile << message << std::endl;
        logFile.close();
    }
};

class Application2
{ // 高层模块
private:
    ILogger &logger;

public:
    Application2(ILogger &logger) : logger(logger) {}
    void process()
    {
        logger.logMessage("Process started.");
        // 更多业务逻辑...
        logger.logMessage("Process finished.");
    }
};

int main()
{
    FileLogger2 fileLogger;
    Application2 app(fileLogger);
    app.process();
    return 0;
}
