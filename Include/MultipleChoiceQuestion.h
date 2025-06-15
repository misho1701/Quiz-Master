#pragma once
#include "Question.h"
#include "Vector.hpp"
#include "String.h"
#include <fstream>

class MultipleChoiceQuestion : public Question {
    Vector<String> options;
    Vector<int> correctIndices;

public:
	MultipleChoiceQuestion() = default;
    MultipleChoiceQuestion(const String& text, int points, const Vector<String>& opts, const Vector<int>& correct);
    void display() const override;
    bool checkAnswer(const String& answer) const override;
    Question* clone() const override;
    String getType() const override;

	virtual void readFromFile(std::ifstream& ifs) override;
	virtual void writeToFile(std::ofstream& ofs) const override;    
};
