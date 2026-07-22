#include "MyString.h"
#include <iostream>

using namespace std;

int main()
{
    // Constructors
    MyString s1("Hello");
    MyString s2("World");

    cout << "s1 = " << s1 << endl;
    cout << "s2 = " << s2 << endl;

    // Concatenation
    MyString s3 = s1 + " " + s2;
    cout << "After + : " << s3 << endl;

    // Append
    s3.append("!!!");
    cout << "After append : " << s3 << endl;

    // Push and Pop
    s3.push_back('?');
    cout << "After push_back : " << s3 << endl;

    s3.pop_back();
    cout << "After pop_back : " << s3 << endl;

    // Length
    cout << "Length = " << s3.length() << endl;

    // Character Access
    cout << "First character : " << s3.front() << endl;
    cout << "Last character  : " << s3.back() << endl;
    cout << "Character at index 1 : " << s3[1] << endl;

    // Find
    cout << "Position of 'World' : " << s3.find("World") << endl;

    // Substring
    cout << "Substring : " << s3.substr(6, 5) << endl;

    // Comparison
    if (s1 == "Hello")
        cout << "Comparison works!" << endl;

    // Clear
    s3.clear();
    cout << "After clear(), Empty = " << s3.empty() << endl;

    return 0;
}
