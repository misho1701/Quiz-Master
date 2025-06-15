#pragma once
#include "Question.h"
#include "String.h"
#include <fstream>
#include "Vector.hpp"   

class TrueOrFalseQuestion : public Question {
    bool correctAnswer;

public:
	TrueOrFalseQuestion() = default;
    TrueOrFalseQuestion(const String& text, int points, bool correct);
    void display() const override;
    bool checkAnswer(const String& answer) const override;
    Question* clone() const override;
    String getType() const override;

	virtual void readFromFile(std::ifstream& ifs) override;
	virtual void writeToFile(std::ofstream& ofs) const override;    
};