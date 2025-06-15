#pragma once
#include <iostream>
#include <cstring>
#include <cctype>
#include <sstream>
#include "Utils.h"
#include <fstream>

class String {
    char* data;
    size_t len;

    void copyFrom(const char* src);
    void free();

public:
    String();
    String(const char* s);
    String(const String& other);
    String& operator=(const String& other);
    ~String();

    const char* c_str() const;
    size_t length() const;

    bool operator==(const String& other) const;
    bool operator!=(const String& other) const;
    String& operator+=(const String& other);
    char& operator[](size_t index);
    const char& operator[](size_t index) const;
    void copy(char*& dest, size_t count, size_t pos = 0) const;
    String toLower() const;
    void print() const;
    bool is_empty() const;
    int find(char ch) const;
    String trim() const;
    String substr(size_t pos, size_t count) const;

    String& concat(int value);
    String& concat(char value);
    String& concat(double value);
    String& concat(const char* value);
    String& concat(const String& value);

    friend std::istream& operator>>(std::istream& in, String& str);
    friend std::ostream& operator<<(std::ostream& out, const String& str);

    void readFromFile(std::ifstream& ifs);
    void writeToFile(std::ofstream& ofs) const;
};

String operator+(const String& lhs, const String& rhs);