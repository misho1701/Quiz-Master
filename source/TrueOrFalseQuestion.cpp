#include "TrueOrFalseQuestion.h"
#include <iostream>
#include "QuestionType.h"

TrueOrFalseQuestion::TrueOrFalseQuestion(const String& text, int points, bool correct)
    : Question(text, points), correctAnswer(correct) {}

void TrueOrFalseQuestion::display() const {
    std::cout << "[True/False] " << text.c_str() << " (" << points << " pts)\n";
    std::cout << "1. True\n2. False\n";
}

bool TrueOrFalseQuestion::checkAnswer(const String& answer) const {
    String ans = answer;
    ans.toLower();
    return (ans == "true" && correctAnswer) || (ans == "false" && !correctAnswer);
}

Question* TrueOrFalseQuestion::clone() const {
    return new TrueOrFalseQuestion(*this);
}

String TrueOrFalseQuestion::getType() const {
    return "TrueOrFalse";
}

void TrueOrFalseQuestion::readFromFile(std::ifstream& ifs)
{
	ifs >> points;
	ifs.ignore();

	std::string tempText;
	std::getline(ifs, tempText);
	text = String(tempText.c_str());  

	std::string answer;
	std::getline(ifs, answer);
	correctAnswer = (answer == "true");
}


void TrueOrFalseQuestion::writeToFile(std::ofstream& ofs) const
{
	int type = (int)QuestionType::TrueOrFalse;
	ofs << type << "\n";

	ofs << points << '\n';
	ofs << text.c_str() << '\n';
	ofs << (correctAnswer ? "true" : "false") << '\n';
}

