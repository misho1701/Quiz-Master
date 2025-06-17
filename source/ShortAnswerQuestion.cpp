#include "ShortAnswerQuestion.h"
#include <iostream>
#include "QuestionType.h"

ShortAnswerQuestion::ShortAnswerQuestion(const String& text, int points, const String& answer)
    : Question(text, points), correctAnswer(answer) {}

void ShortAnswerQuestion::display() const {
    std::cout << "[Short Answer] " << text.c_str() << " (" << points << " pts)\n";
    std::cout << "Your answer: ";
}

bool ShortAnswerQuestion::checkAnswer(const String& answer) const {
    String ans = answer, correct = correctAnswer;
    ans.toLower();
    correct.toLower();
    return ans == correct;
}

Question* ShortAnswerQuestion::clone() const {
    return new ShortAnswerQuestion(*this);
}

String ShortAnswerQuestion::getType() const {
    return "ShortAnswer";
}

void ShortAnswerQuestion::readFromFile(std::ifstream& ifs) {
    ifs >> points;
    ifs.ignore(); 

    std::string tempText;
    std::getline(ifs, tempText); 
    text = String(tempText.c_str());

    std::string tempAnswer;
    std::getline(ifs, tempAnswer);
    correctAnswer = String(tempAnswer.c_str());
}

    
void ShortAnswerQuestion::writeToFile(std::ofstream& ofs) const
{
    int type = (int)QuestionType::ShortAnswer;
    ofs << type << "\n";
	ofs << points << '\n';
	ofs << text.c_str() << '\n';
	ofs << correctAnswer.c_str() << '\n';
}

