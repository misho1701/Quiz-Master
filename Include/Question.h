#pragma once
#include "String.h"
#include "Vector.hpp"
#include <iostream>
#include <fstream>

class Question {
protected:
    String text;
    int points;

public:
	Question() = default;
    Question(const char* t) : text(t) {}
    Question(const String& text, int points);
    virtual ~Question() = default;

    virtual void display() const = 0;
    virtual bool checkAnswer(const String& answer) const = 0;
    virtual Question* clone() const = 0;
    virtual String getType() const = 0;

	virtual void readFromFile(std::ifstream& ifs) = 0;  
	virtual void writeToFile(std::ofstream& ofs) const = 0;

    int getPoints() const;
};
