#pragma once

#include <iostream>
#include <cstring>

class StringValue {
private:
    char* value;
    int length;
    int refCount;

public:
    StringValue(const char* _value);
    ~StringValue();

    const char* getValue() const;
    char& getChar(int index);
    bool isNotUsed() const;
    int getLength() const;

    void increaseRefCount();
    void decreaseRefCount();
    void setValue(const char* _value);
};

class MyString {
private:
    StringValue* stringValue;

public:
    MyString();
    MyString(const char* value);
    MyString(const MyString& other);
    MyString(MyString&& other) noexcept;
    ~MyString();

    const MyString& operator=(const char* value);
    const MyString& operator=(const MyString& other);
    const MyString& operator=(MyString&& other) noexcept;

    MyString operator+(const MyString& other);
    void operator+=(const MyString& other);
    MyString operator+(char c);
    void operator+=(char c);

    const char& operator[](int index) const;
    char& operator[](int index);

    int getLength() const;

    friend std::ostream& operator<<(std::ostream& o, const MyString& mystring);
    friend std::istream& operator>>(std::istream& i, MyString& mystring);
};