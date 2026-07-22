#ifndef MYSTRING_H
#define MYSTRING_H

#include <iostream>

/*
    MyString - a simple clone of std::string
    ------------------------------------------
    Internally it just holds:
        - a pointer to a block of characters on the heap (data)
        - how many characters are actually used (len)

    Every method either READS that block, or creates a NEW block
    (bigger or smaller) and copies the right characters into it.
    That's really the whole trick behind this project.
*/

class MyString {
private:
    char* data;   // pointer to heap-allocated characters (always ends with '\0')
    int len;      // number of characters, NOT counting the '\0'

public:
    // ---------- Constructors / Destructor ----------
    MyString();                       // empty string ""
    MyString(const char* str);        // build from a C-string, e.g. MyString("Hello")
    MyString(const MyString& other);  // copy constructor (deep copy)
    ~MyString();                      // destructor (frees memory)

    // ---------- Assignment ----------
    MyString& operator=(const MyString& other); // copy assignment (deep copy)

    // ---------- Access ----------
    char& operator[](int index);        // s[2] -> character at index 2
    char front() const;                 // first character
    char back() const;                  // last character
    const char* c_str() const;          // raw C-string (for printing / interop)

    // ---------- Info ----------
    int length() const;                 // how many characters
    bool empty() const;                 // true if length == 0

    // ---------- Modify ----------
    void append(const char* str);       // add characters onto the end
    void push_back(char c);             // add a single character onto the end
    void pop_back();                    // remove the last character
    void clear();                       // make it empty again

    // ---------- Search / Slice ----------
    int find(const char* str) const;    // index where str starts, or -1 if not found
    MyString substr(int pos, int count) const; // extract part of the string

    // ---------- Operators ----------
    MyString operator+(const MyString& other) const; // concatenation -> new string
    MyString operator+(const char* str) const;        // concatenation with a C-string
    bool operator==(const MyString& other) const;     // equality check
    bool operator==(const char* str) const;            // equality check vs C-string

    // ---------- Printing ----------
    friend std::ostream& operator<<(std::ostream& os, const MyString& s);
};

#endif
