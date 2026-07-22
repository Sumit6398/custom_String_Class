MyString — A Simple Custom String Class (STL::string Clone)

A hand-built C++ class that recreates the core behavior of std::string
using manual dynamic memory management (new[] / delete[]). Built to
understand how a string container works internally, not just how to
use one.

How the Files Work Together


MyString.h is the promise: it lists every method the class
has, without saying how they work. Any file that wants to use
MyString just needs #include "MyString.h".
MyString.cpp fulfills that promise — every method declared
in the header is defined here.
main.cpp only ever talks to the header. It doesn't need to know
how append() is implemented internally — only that it exists.


At compile time, main.cpp and MyString.cpp are compiled separately
into .o files, and the linker combines them into one program. This is
exactly what the Makefile automates.

How to Build & Run

Requires a C++17-capable compiler (g++ or clang++).

bashmake          # compiles main.cpp + MyString.cpp -> ./demo
make run      # builds (if needed) and runs the demo
make clean    # removes build artifacts

Or compile manually without make:

bashg++ -std=c++17 -Wall -Wextra -o demo main.cpp MyString.cpp
./demo

Design Overview

Internally, MyString stores just two things:

cppchar* data;   // pointer to a heap-allocated buffer, always ending in '\0'
int   len;    // number of characters (not counting the '\0')

The one repeating pattern behind almost every method:
Allocate a new buffer big enough → copy the necessary characters into
it → free the old buffer → point data at the new one. Once you
understand this pattern in append(), you understand push_back(),
operator+, and substr() too — they're all the same idea.

Why this design teaches the important C++ concepts


RAII — the constructor allocates, the destructor frees. The user
of the class never manually manages memory.
The Rule of Three — since the class owns a raw resource (heap
memory), it correctly implements all three special member functions:

Destructor (~MyString())
Copy constructor (deep copy — so two objects never share/double-free
the same buffer)
Copy assignment operator (deep copy, with a self-assignment guard)



Operator overloading — +, [], ==, << are overloaded so
MyString behaves like a built-in type.
Exception safety — operator[] and substr() throw
std::out_of_range on invalid access, matching real std::string
behavior.
Implicit conversion — because the constructor MyString(const char* str) isn't marked explicit, plain string literals like
"Hello" are automatically converted into a MyString wherever one
is expected (e.g. s1 == "Hello", s1 + " " + s2).


Public API Reference

Constructors / Destructor

cppMyString();                        // "" (empty string)
MyString(const char* str);         // from a C-string, e.g. MyString("Hello")
MyString(const MyString& other);   // copy constructor (deep copy)
~MyString();

Assignment

cppMyString& operator=(const MyString& other);   // deep-copy assignment

Access

cppchar&       operator[](int index);   // bounds-checked, throws std::out_of_range
char        front() const;           // first character
char        back() const;            // last character
const char* c_str() const;           // raw C-string view

Info

cppint  length() const;
bool empty() const;

Modify

cppvoid append(const char* str);        // add a C-string onto the end
void push_back(char c);              // add one character onto the end
void pop_back();                     // remove the last character
void clear();                        // reset to empty

Search / Slice

cppint      find(const char* str) const;         // index of first match, or -1
MyString substr(int pos, int count) const;     // extract part of the string

Operators

cppMyString operator+(const MyString& other) const;
MyString operator+(const char* str) const;
bool     operator==(const MyString& other) const;
bool     operator==(const char* str) const;

Printing

cppfriend std::ostream& operator<<(std::ostream& os, const MyString& s);

Example Usage

cpp#include "MyString.h"
#include <iostream>

int main() {
    MyString greeting("Hello");
    MyString name("World");

    MyString message = greeting + " " + name + "!";
    std::cout << message << std::endl;      // Hello World!

    std::cout << message.substr(0, 5) << std::endl;  // Hello
    std::cout << message.find("World") << std::endl; // 6
}

Sample Output

Running make run with the included main.cpp produces:

s1 = Hello
s2 = World
After + : Hello World
After append : Hello World!!!
After push_back : Hello World!!!?
After pop_back : Hello World!!!
Length = 14
First character : H
Last character  : !
Character at index 1 : e
Position of 'World' : 6
Substring : World
Comparison works!
After clear(), Empty = 1

Possible Extensions (good bonus-feature ideas)


insert(pos, str) / erase(pos, len) — insert or remove from the
middle of the string
to_upper() / to_lower()
operator+= for in-place concatenation
reserve(capacity) — pre-allocate space to reduce reallocations
Move constructor / move assignment (MyString(MyString&&)) for a
performance upgrade — steals the pointer instead of copying it
Iterators (begin() / end()) so range-based for loops work


Known Limitations (by design, to keep the code simple)


No move semantics — every copy is a deep copy, even from temporaries.
This is intentional for clarity; std::string avoids this for
performance using move constructors.
append() always reallocates exact-size memory rather than
over-allocating and growing geometrically, so repeated push_back()
calls are less efficient than in real std::string.
No insert()/erase() yet — see Extensions above if you want to add
them yourself.
