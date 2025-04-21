#include "Header.hpp"
#include <cstring>
#include <fstream>
#include <algorithm> 

String::String() {
    Data = new char[1]; 
    Data[0] = '\0';     
}

String::String(const String &rhs) {
    Data = new char[rhs.Size()+1];
    for (int i = 0; i < rhs.Size(); i++)
        Data[i] = rhs.Data[i];
    Data[rhs.Size()] = '\0';
}

String::String(const char* data){
    Data = new char[strlen(data) + 1];
    for (int i = 0; i < strlen(data); i++)
        Data[i] = data[i];
    Data[strlen(data)] = '\0';
}

String::~String(){
    delete[] Data;
}

size_t String::Size() const{
    size_t length{};
    for(int i{}; Data[i]!='\0'; ++i){
        ++length;
    }
    return length;
}

String& String::operator=(const String& rhs){
    if (this == &rhs) {
        return *this;  // ничего не делаем
    }

    delete[] Data;
    Data = new char[rhs.Size()+1];
    for(int i{}; rhs.Data[i]!='\0'; ++i){
        Data[i] = rhs.Data[i];
    }
    Data[rhs.Size()] = '\0';
    return *this;
}

String& String::operator+=(const String& rhs){
    size_t length = this->Size();
    size_t length_all = length + rhs.Size();
    char* Data1  = new char[length_all + 1];

    for (int i{};i < length;++i)
        Data1[i] = Data[i];
    for (int i{}; i < length_all - length;++i)
        Data1[length + i] = rhs.Data[i];

    Data1[length_all] = '\0';
    delete[] Data;
    Data = Data1;

    return *this;
}

String& String::operator*=(unsigned int m){
    size_t length = this->Size();
    char* Data1  = new char[length * m + 1];

    for (int j{}; j < m; ++j){
        for (int i{};i<length;++i){
            Data1[length*j + i] = Data[i];
        }
    }
    Data1[length*m] = '\0';
    delete[] Data;
    Data = Data1;

    return *this;
}

bool String::operator==(const String& rhs) const{
    size_t length = this->Size();
    if (length != rhs.Size()){
        return 0;
    }
    else {
        for(int i{}; i < length; ++i){
            if (rhs.Data[i] != this->Data[i]){
                return 0;
            }
        }
    }
    return 1;
}

bool String::operator<(const String& rhs) const{
    size_t minl = std::min(rhs.Size(), this->Size());
    for(int i{}; i < minl; ++i){
        if(this->Data[i] > rhs.Data[i]){
            return 0;
        }
    }
    return 1;
}

int String::Find(const String& substr) const {
    size_t thisLength = this->Size();
    size_t subLength = substr.Size();

    if (subLength > thisLength) {
        return -1;
    }

    for (int i = 0; i <= thisLength - subLength; ++i) {
        bool match = true;
        for (size_t j = 0; j < subLength; ++j) {
            if (Data[i + j] != substr.Data[j]) {
                match = false;
                break;
            }
        }
        if (match) {
            return i;
        }
    }

    return -1; 
}

bool String::Empty() const{
    if(this->Size() == 0){
        return 1;
    }
    return 0;
}

void String::Replace(char oldSymbol, char newSymbol){
    size_t length = Size();
    for(int i{}; i < length; ++i){
        if(Data[i] == oldSymbol){
            Data[i] = newSymbol;
        }
    }
}

String operator+(const String& a, const String& b){
    String c =a;
    c+=b;
    return c;
}

String operator*(const String& a, unsigned int b){
    String c = a;
    c *= b;
    return c;
}

bool operator!=(const String& a, const String& b){
    if (a==b){
        return 0;
    }
    else{
        return 1;
    }
}

bool operator>(const String& a, const String& b){
    if (a<b){
        return 0;
    }
    if(a==b){
        return 0;
    }
    return 1;
}

std::ostream& operator<<(std::ostream& out, const String& str) {
    out << str.Data;
    return out;
}