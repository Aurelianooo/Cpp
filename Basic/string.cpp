/*
方法	                        作用
length()	                返回字符串的长度
empty()	                    判断字符串是否为空
substr(pos, len)	        返回从 pos 开始、长度为 len 的子串（若省略 len，则表示截取到末尾）
erase(pos, len)	            删除从 pos 开始、长度为 len 的子串
operator + char/str	        将字符或字符串拼接到当前字符串后面
operator<，<=，>，>=，==	  按字典顺序比较字符串
find(str)	                返回指定字符串或字符在当前字符串中第一次出现的位置
 */

#include <string>
#include <iostream>
using namespace std;

int main()
{
    string str = "Hello World";
    cout << str << endl;

    string str1 = "Hello";
    string str2 = str1;
    cout << str2 << endl;

    char arr[] = "Hello";
    string str3(arr);
    cout << str3 << endl;

    string str4(5, 'A');
    cout << str4 << endl;

    return 0;
}
