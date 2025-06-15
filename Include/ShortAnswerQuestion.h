#pragma once
#include "Question.h"
#include "String.h"
#include <fstream>
#include "Vector.hpp"


class ShortAnswerQuestion : public Question {
    String correctAnswer;

public:
	ShortAnswerQuestion() = default;
    ShortAnswerQuestion(const String& text, int points, const String& answer);
    void display() const override;
    bool checkAnswer(const String& answer) const override;
    Question* clone() const override;
    String getType() const override;

	virtual void readFromFile(std::ifstream& ifs) override;
	virtual void writeToFile(std::ofstream& ofs) const override;
};
