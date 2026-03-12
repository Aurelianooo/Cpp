/*
fstream 类中常用的成员函数如下，
其中参数 c、str为 char 型，n 为 int 型：

函数/方法	                    描述
get(c)	                从文件中读取一个字符。
getline(str, n, '\n')	从文件中读取字符并存入字符串 str 中，直到读取第 n-1 个字符或遇到 '\n' 时结束。
peek()	                查找下一个字符，但不从文件中取出。
put(c)	                将一个字符写入文件。
putback(c)	            对输入流放回一个字符，但不保存。
eof	                    如果读取超过 eof，返回 true。
ignore(n)	            跳过 n 个字符，参数为空时，表示跳过下一个字符。

要实现在指定位置读写文件的功能，首先要了解文件指针是如何移动的。下面来认识下设置文件指针位置的 4 个函数：
seekg()：参数有两个，分别是位移字节数和相对位置，用于输入文件中指针的移动；
seekp()：参数有两个，分别是位移字节数和相对位置，用于输出文件中指针的移动；
tellg()：用于查找输入文件中的文件指针位置；
tellp()：用于查找输出文件中的文件指针位置。

位移字节数是移动指针的位移量，相对位置是参照位置，可取值如下：
ios::beg：文件头部；
ios::end：文件尾部；
ios::cur：文件指针的当前位置。
 */

#include <iostream>
#include <fstream>
using namespace std;

void write()
{
    fstream file("test.txt", ios::out);
    if (!file.fail())
    {
        cout << "start write" << endl;
        file << "abc test" << endl;
        file << "hello world!";
        file.put('-');
        file << " /c/ " << endl;
        cout << "write end" << endl;
    }
    else
    {
        cout << "can not open" << endl;
        file.close();
    }
}

void read()
{
    fstream file("test.txt", ios::in);
    if (!file.fail())
    {
        cout << "start read" << endl;
        while (!file.eof())
        {
            char buf[128];
            file.getline(buf, 128);
            if (file.tellg() > 0)
            {
                cout << buf << endl;
            }
        }
        cout << "read end" << endl;
    }
    else
        cout << "can not open" << endl;
    file.close();
}

void seek()
{
    ifstream ifile;
    ifile.open("test.txt");
    if (!ifile)
        cout << "can not open" << endl;
    ifile.seekg(0, ios::end);
    int maxpos = ifile.tellg();
    int pos;
    cout << "Max length:" << maxpos << endl
         << "Position:";
    cin >> pos;
    if (pos > maxpos)
        cout << "over file length" << endl;
    else
    {
        char ch;
        ifile.seekg(pos);
        ifile.get(ch);
        cout << ch << endl;
    }
    ifile.close();
}

int main()
{
    write();
    read();
    seek();

    return 0;
}
