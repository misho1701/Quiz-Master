#pragma once
#include "Question.h"
#include "Vector.hpp"
#include "String.h"
#include <fstream>

class MatchingPairsQuestion : public Question {
    Vector<String> leftColumn;
    Vector<String> rightColumn;
    Vector<int> correctMatches;

public:
    MatchingPairsQuestion() = default;
    MatchingPairsQuestion(const String& text, int points, const Vector<String>& left, const Vector<String>& right, const Vector<int>& matches);
    void display() const override;
    bool checkAnswer(const String& answer) const override;
    Question* clone() const override;
    String getType() const override;

	virtual void readFromFile(std::ifstream& ifs) override;
	virtual void writeToFile(std::ofstream& ofs) const override;
};
