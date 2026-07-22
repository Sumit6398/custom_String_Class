#include "MyString.h"
#include <cstring>      // strlen, strcpy, strcat, strstr
#include <stdexcept>    // std::out_of_range

// ============================================================
//  Constructors / Destructor
// ============================================================

// Empty string: just a buffer holding '\0'
MyString::MyString() {
    len = 0;
    data = new char[1];
    data[0] = '\0';
}

// Build from a C-string like "Hello"
MyString::MyString(const char* str) {
    len = strlen(str);          // how many characters (not counting '\0')
    data = new char[len + 1];   // +1 so there's room for '\0'
    strcpy(data, str);          // copy the characters + the '\0' in
}

// Copy constructor: called when you do  MyString b = a;
// We must allocate OUR OWN memory and copy the contents,
// otherwise 'a' and 'b' would point to the SAME memory and
// both destructors would try to delete it -> crash.
MyString::MyString(const MyString& other) {
    len = other.len;
    data = new char[len + 1];
    strcpy(data, other.data);
}

// Destructor: give the heap memory back when the object dies
MyString::~MyString() {
    delete[] data;
}

// ============================================================
//  Assignment
// ============================================================

// Called when you do  b = a;  (b already exists)
MyString& MyString::operator=(const MyString& other) {
    if (this == &other) return *this;  // guard against  a = a;

    delete[] data;               // free our old memory first
    len = other.len;
    data = new char[len + 1];
    strcpy(data, other.data);

    return *this;
}

// ============================================================
//  Access
// ============================================================

char& MyString::operator[](int index) {
    if (index < 0 || index >= len)
        throw std::out_of_range("MyString::operator[] - index out of range");
    return data[index];
}

char MyString::front() const {
    return data[0];
}

char MyString::back() const {
    return data[len - 1];
}

const char* MyString::c_str() const {
    return data;
}

// ============================================================
//  Info
// ============================================================

int MyString::length() const {
    return len;
}

bool MyString::empty() const {
    return len == 0;
}

// ============================================================
//  Modify
// ============================================================

// Add a C-string onto the end. Strategy: allocate a NEW bigger
// buffer, copy the old characters in, then copy the new ones in.
void MyString::append(const char* str) {
    int addLen = strlen(str);
    int newLen = len + addLen;

    char* newData = new char[newLen + 1];
    strcpy(newData, data);        // copy old characters in
    strcat(newData, str);         // add the new characters on the end

    delete[] data;                // free the old buffer
    data = newData;
    len = newLen;
}

// Add one character. Same idea as append(), just for a single char.
void MyString::push_back(char c) {
    char* newData = new char[len + 2]; // +1 for new char, +1 for '\0'
    strcpy(newData, data);
    newData[len] = c;
    newData[len + 1] = '\0';

    delete[] data;
    data = newData;
    len = len + 1;
}

// Remove the last character
void MyString::pop_back() {
    if (len == 0) return; // nothing to remove
    len = len - 1;
    data[len] = '\0';     // just shrink the "used" part and re-terminate
}

// Reset to empty
void MyString::clear() {
    delete[] data;
    len = 0;
    data = new char[1];
    data[0] = '\0';
}

// ============================================================
//  Search / Slice
// ============================================================

// Find where 'str' first appears. Returns -1 if not found.
int MyString::find(const char* str) const {
    const char* result = strstr(data, str); // C library search
    if (result == nullptr) return -1;
    return static_cast<int>(result - data);  // pointer distance = index
}

// Extract 'count' characters starting at index 'pos'
MyString MyString::substr(int pos, int count) const {
    if (pos < 0 || pos > len)
        throw std::out_of_range("MyString::substr - position out of range");

    // don't read past the end of the string
    if (pos + count > len) count = len - pos;

    char* temp = new char[count + 1];
    strncpy(temp, data + pos, count);
    temp[count] = '\0';

    MyString result(temp);  // build a MyString from the temp C-string
    delete[] temp;
    return result;
}

// ============================================================
//  Operators
// ============================================================

MyString MyString::operator+(const MyString& other) const {
    MyString result(data);   // start as a copy of *this
    result.append(other.data);
    return result;
}

MyString MyString::operator+(const char* str) const {
    MyString result(data);
    result.append(str);
    return result;
}

bool MyString::operator==(const MyString& other) const {
    return strcmp(data, other.data) == 0;
}

bool MyString::operator==(const char* str) const {
    return strcmp(data, str) == 0;
}

// ============================================================
//  Printing
// ============================================================

std::ostream& operator<<(std::ostream& os, const MyString& s) {
    os << s.data;
    return os;
}
