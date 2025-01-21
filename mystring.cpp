#include "mystring.hpp"

StringValue::StringValue(const char* _value) : refCount(1) {
    int l = strlen(_value);
    value = new char[l + 1];
    strcpy(value, _value);
    value[l] = '\0';
    length = l;
}

StringValue::~StringValue() {
    delete[] value;
}

const char* StringValue::getValue() const {
    return value;
}

char& StringValue::getChar(int index) {
    if (index >= 0 && index < length) {
        return *(value + index);
    }
    else {
        throw std::runtime_error("Index out of bounds");;
    }
}

void StringValue::increaseRefCount() {
    refCount++;
}

void StringValue::decreaseRefCount() {
    refCount--;
}

void StringValue::setValue(const char* _value) {
    delete[] value;
    int l = strlen(_value);
    value = new char[l + 1];
    strcpy(value,  _value);
    value[l] = '\0';
    length = l;
}

bool StringValue::isNotUsed() const {
    return refCount == 0;
}

int StringValue::getLength() const {
    return length;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - //

MyString::MyString() : stringValue(nullptr) {}

MyString::MyString(const char* value) {
    stringValue = new StringValue(value);
}

MyString::MyString(const MyString& other) {
    if (other.stringValue != nullptr) {
        stringValue = other.stringValue;
        stringValue->increaseRefCount();
    }
    else {
        stringValue = nullptr;
    }
}

MyString::MyString(MyString&& other) noexcept {
    if (other.stringValue != nullptr) {
        stringValue = other.stringValue;
        other.stringValue = nullptr;
    }
    else {
        stringValue = nullptr;
    }
}

MyString::~MyString() {
    if (stringValue != nullptr) {
        stringValue->decreaseRefCount();
        if (stringValue->isNotUsed()) {
            delete stringValue;
        }
    }
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - //

const MyString& MyString::operator=(const char* value) {
    if (stringValue != nullptr) {
        stringValue->decreaseRefCount();
        if (stringValue->isNotUsed()) {
            delete stringValue;
        }
    }
    stringValue = new StringValue(value);

    return *this;
}

const MyString& MyString::operator=(const MyString& other) {
    if (stringValue != other.stringValue) {
        if (other.stringValue != nullptr) {
            if (stringValue != nullptr) {
                stringValue->decreaseRefCount();
                if (stringValue->isNotUsed()) {
                    delete stringValue;
                }
            }
            stringValue = other.stringValue;
            stringValue->increaseRefCount();
        }
    }
    return *this;
}

const MyString& MyString::operator=(MyString&& other) noexcept {
    if (stringValue != other.stringValue) {  
        if (other.stringValue != nullptr) {
            if (stringValue != nullptr) {
                stringValue->decreaseRefCount();
                if (stringValue->isNotUsed()) {
                    delete stringValue;
                }
            }
            stringValue = other.stringValue;
            other.stringValue = nullptr;
        }
    }
    return *this;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - //

MyString MyString::operator+(const MyString& other) {
    const char* thisValue = stringValue->getValue();
    const char* otherValue = other.stringValue->getValue();
    const int thisLength = getLength();
    const int otherLength = other.getLength();
    char* resultValue = new char[thisLength + otherLength + 1];

    for (int i = 0; i < thisLength; ++i) {
        *(resultValue + i) = *(thisValue + i);
    }
    for (int i = 0; i < otherLength; ++i) {
        *(resultValue + thisLength + i) = *(otherValue + i);
    }
    resultValue[thisLength + otherLength] = '\0';

    MyString myString;
    myString = (const char*)resultValue;
    delete[] resultValue;
    return myString;
}

void MyString::operator+=(const MyString& other) {
    if (other.stringValue == nullptr) {
        throw std::runtime_error("MyString::operator+= parameter is nullptr");
    }
    else {
        const char* thisValue;
        int thisLength;
        if (stringValue != nullptr) {
            thisValue = stringValue->getValue();
            thisLength = getLength();
        }
        else {
            thisValue = "";
            thisLength = 0;
        } 

        const char* otherValue = other.stringValue->getValue();
        int otherLength = other.getLength();

        char* resultValue = new char[thisLength + otherLength + 1];

        for (int i = 0; i < thisLength; ++i) {
            *(resultValue + i) = *(thisValue + i);
        }
        for (int i = 0; i < otherLength; ++i) {
            *(resultValue + thisLength + i) = *(otherValue + i);
        }
        resultValue[thisLength + otherLength] = '\0';

        *this = resultValue;
        delete[] resultValue;
    }  
}

MyString MyString::operator+(char c) {
    const char* thisValue = stringValue->getValue();
    const int thisLength = getLength();
    char* resultValue = new char[thisLength + 2];

    strcpy(resultValue, thisValue);
    resultValue[thisLength] = c;
    resultValue[thisLength + 1] = '\0';

    MyString myString;
    myString = resultValue;
    delete[] resultValue;
    return myString;
}

void MyString::operator+=(char c) {
    const char* thisValue = stringValue->getValue();
    const int thisLength = getLength();
    char* resultValue = new char[thisLength + 2];

    strcpy(resultValue, thisValue);
    resultValue[thisLength] = c;
    resultValue[thisLength + 1] = '\0';

    *this = resultValue;
    delete[] resultValue;
}

const char& MyString::operator[](int index) const {
    int length = getLength();
    if (index < 0 || index > length - 1) {
        throw std::out_of_range("Index out of bounds");;
    }
    else {
        const char* value = stringValue->getValue();
        return *(value + index);
    }
}

char& MyString::operator[](int index) {
    if (stringValue == nullptr) {
        throw std::runtime_error("StringValue is nullptr");
    }

    int length = stringValue->getLength();
    if (index < 0 || index > length - 1) {
        throw std::runtime_error("Index out of bounds");;
    }
    else {
        char* oldValue = new char[length + 1];
        strcpy(oldValue, stringValue->getValue());

        stringValue->decreaseRefCount();
        if (stringValue->isNotUsed()) {
            delete stringValue;
        }

        stringValue = new StringValue(oldValue);
        delete[] oldValue;
        return stringValue->getChar(index);
    }
}

int MyString::getLength() const {
    if (stringValue != nullptr) {
        return stringValue->getLength();
    }
    else {
        return 0;
    }
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - //

std::ostream& operator<<(std::ostream& o, const MyString& mystring) {
    auto stringValue = mystring.stringValue;
    if (stringValue == nullptr) {
        o << "MyString stringValue is nullptr!";
    }
    else {
        o << stringValue->getValue();
    }
    return o;
}

std::istream& operator>>(std::istream& i, MyString& mystring) {
    char buffer[1024];
    i >> buffer;
    if (mystring.stringValue == nullptr) {
        mystring.stringValue = new StringValue(buffer);
    }
    else {
        mystring.stringValue->setValue(buffer);
    }
    return i;
}
