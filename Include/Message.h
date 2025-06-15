#pragma once
#include <iostream>
#include <ctime>
#include "MyString.h"
#include <fstream>
#include "Vector.hpp"
#pragma warning(disable:4996)

class Message {
public:
    Message() = default;
    String content;
    std::time_t timestamp;
    Message(const String& content);
    void display() const;
    String getContent() const;
    void readFromFile(std::ifstream& ifs);
    void writeToFile(std::ofstream& ofs) const;
};