#include "MultipleChoiceQuestion.h"
#include <iostream>
#include <sstream>
#include "QuestionType.h"

MultipleChoiceQuestion::MultipleChoiceQuestion(const String& text, int points, const Vector<String>& opts, const Vector<int>& correct)
    : Question(text, points), options(opts), correctIndices(correct) {}

void MultipleChoiceQuestion::display() const {
    std::cout << "[Multiple Choice] " << text.c_str() << " (" << points << " pts)\n";
    std::cout << "Choose ALL that apply (e.g., 1,3):\n";
    for (size_t i = 0; i < options.size(); i++) {
        std::cout << "  " << i + 1 << ". "; options[i].print(); std::cout << "\n";
    }
    std::cout << "Enter your answers: ";
}


bool MultipleChoiceQuestion::checkAnswer(const String& answer) const {
    std::stringstream ss(answer.c_str());
    std::string token;
    Vector<int> userIndices;

    static const int npos = -1;

    while (std::getline(ss, token, ',')) {
        int index = toInt(token.c_str()) - 1;
        if (index >= 0 && index < (int)options.size()) {
            userIndices.push_back(index);
        }
    }

    if (userIndices.is_empty()) return false;
    if (correctIndices.is_empty()) return false;
    if (userIndices.size() < correctIndices.size()) return false;
    if (userIndices.size() > correctIndices.size() + 1) return false;

    int correctCount = 0;
    for (size_t i = 0; i < userIndices.size(); i++) {
        for (size_t j = 0; j < correctIndices.size(); j++) {
            if (userIndices[i] == correctIndices[j]) {
                correctCount++;
                break;
            }
        }
    }

    if (correctCount == correctIndices.size()) return true;
    if (correctCount >= (int)((correctIndices.size() + 1) / 2)) return false;
    return false;
}


Question* MultipleChoiceQuestion::clone() const {
    return new MultipleChoiceQuestion(*this);
}

String MultipleChoiceQuestion::getType() const {
    return "MultipleChoice";
}

void MultipleChoiceQuestion::readFromFile(std::ifstream& ifs)
{
	ifs >> text >> points;
	int optionsCount;
	ifs >> optionsCount;
	options.resize(optionsCount);
	for (int i = 0; i < optionsCount; i++) {
		ifs >> options[i];
	}

	int correctCount;
	ifs >> correctCount;
	correctIndices.resize(correctCount);
	for (int i = 0; i < correctCount; i++) {
		ifs >> correctIndices[i];
	}
}

void MultipleChoiceQuestion::writeToFile(std::ofstream& ofs) const
{
    int type = (int)QuestionType::MultipleChoice;
    ofs << type << "\n";
	ofs << text << " " << points << "\n";
	ofs << options.size() << "\n";
	for (const auto& option : options) {
		ofs << option << "\n";
	}
	ofs << correctIndices.size() << "\n";
	for (const auto& index : correctIndices) {
		ofs << index << " ";
	}
	ofs << "\n";
}

