#include "SingleChoiceQuestion.h"
#include <iostream>
#include "QuestionType.h"

SingleChoiceQuestion::SingleChoiceQuestion(const String& text, int points, const Vector<String>& opts, int correct)
    : Question(text, points), options(opts), correctIndex(correct) {}

void SingleChoiceQuestion::display() const {
    std::cout << "[Single Choice] " << text.c_str() << " (" << points << " pts)\n";
    std::cout << "Choose ONE of the following:\n";
    for (size_t i = 0; i < options.size(); i++) {
        std::cout << "  " << i + 1 << ". "; options[i].print(); std::cout << "\n";
    }
    std::cout << "Your answer: ";
}

bool SingleChoiceQuestion::checkAnswer(const String& answer) const {
    int choice = toInt(answer.c_str()) - 1;
    return choice == correctIndex;
}

Question* SingleChoiceQuestion::clone() const {
    return new SingleChoiceQuestion(*this);
}

String SingleChoiceQuestion::getType() const {
    return "SingleChoice";
}

void SingleChoiceQuestion::readFromFile(std::ifstream& ifs)
{
    ifs >> points;
    ifs.ignore();

    std::string tempText;
    std::getline(ifs, tempText);
    text = String(tempText.c_str()); 

    int correct;
    ifs >> correct;
    correctIndex = correct;

    int optionsCount;
    ifs >> optionsCount;
    ifs.ignore();

    options.resize(optionsCount);
    for (int i = 0; i < optionsCount; ++i) {
        std::string tempOption;
        std::getline(ifs, tempOption);
        options[i] = String(tempOption.c_str());
    }
}

void SingleChoiceQuestion::writeToFile(std::ofstream& ofs) const
{
    int type = (int)QuestionType::SingleChoice;
    ofs << type << "\n";
	ofs << points << '\n';
	ofs << text.c_str() << '\n';
	ofs << correctIndex << '\n';

	ofs << options.size() << '\n';
	for (const auto& option : options) {
		ofs << option.c_str() << '\n';
	}
}
