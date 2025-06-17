#include "MatchingPairQuestion.h"
#include <iostream>
#include <sstream>
#include "QuestionType.h"

MatchingPairsQuestion::MatchingPairsQuestion(const String& text, int points, const Vector<String>& left, const Vector<String>& right, const Vector<int>& matches)
    : Question(text, points), leftColumn(left), rightColumn(right), correctMatches(matches) {}

void MatchingPairsQuestion::display() const {
    std::cout << "[Matching Pairs] " << text.c_str() << " (" << points << " pts)\n";
    std::cout << "Match the left side with the correct item from the right side.\n";
    std::cout << "Enter answers in format: 1:A, 2:B, 3:C ...\n\n";

    std::cout << "Left Side:\n";
    for (size_t i = 0; i < leftColumn.size(); ++i) {
        std::cout << "  " << i + 1 << ". ";
        leftColumn[i].print();
        std::cout << "\n";
    }

    std::cout << "\nRight Side:\n";
    for (size_t i = 0; i < rightColumn.size(); ++i) {
        std::cout << "  " << static_cast<char>('A' + i) << ". ";
        rightColumn[i].print();
        std::cout << "\n";
    }

    std::cout << "\nYour answer: ";
}


bool MatchingPairsQuestion::checkAnswer(const String& answer) const {
    std::stringstream ss(answer.c_str());
    std::string pair;

    Vector<int> userMatches(leftColumn.size(), -1); 

    while (std::getline(ss, pair, ',')) {
        size_t colonPos = pair.find(':');
        if (colonPos == std::string::npos) continue;

        String leftStr = pair.substr(0, colonPos).c_str();
        String rightStr = pair.substr(colonPos + 1).c_str();

        leftStr = leftStr.trim();
        rightStr = rightStr.trim();

        int leftIndex = toInt(leftStr.c_str()) - 1;
        int rightIndex = -1;

        if (rightStr.length() == 1 && std::isalpha(rightStr[0])) {
            rightIndex = std::toupper(rightStr[0]) - 'A';
        }

        if (leftIndex >= 0 && leftIndex < (int)leftColumn.size() &&
            rightIndex >= 0 && rightIndex < (int)rightColumn.size()) {
            userMatches[leftIndex] = rightIndex;
        }
    }

    for (size_t i = 0; i < userMatches.size(); ++i) {
        if (userMatches[i] != correctMatches[i])
            return false;
    }

    return true;
}

Question* MatchingPairsQuestion::clone() const {
    return new MatchingPairsQuestion(*this);
}

String MatchingPairsQuestion::getType() const {
    return "MatchingPairs";
}

void MatchingPairsQuestion::readFromFile(std::ifstream& ifs)
{
    ifs >> points;
    ifs.ignore();
	ifs >> text;

	int leftSize, rightSize, matchesSize;
	ifs >> leftSize >> rightSize >> matchesSize;

	leftColumn.resize(leftSize);
	rightColumn.resize(rightSize);
	correctMatches.resize(matchesSize);

    ifs.ignore();

	for (int i = 0; i < leftSize; ++i) {
        std::string tempAnswer;
        std::getline(ifs, tempAnswer);
		leftColumn[i] = String(tempAnswer.c_str());
	}

	for (int j = 0; j < rightSize; ++j) {
        std::string tempAnswer;
        std::getline(ifs, tempAnswer);
        rightColumn[j] = String(tempAnswer.c_str());
	}

	for (int k = 0; k < matchesSize; ++k) {
		int match;
		ifs >> match;
		correctMatches[k] = match - 1;
	}
}

void MatchingPairsQuestion::writeToFile(std::ofstream& ofs) const
{
	int type = (int)QuestionType::MatchingPairs;
	ofs << type << "\n";

	ofs << points << "\n";
	ofs << text << "\n";
	ofs << leftColumn.size() << " " << rightColumn.size() << " " << correctMatches.size() << "\n";

	for (const auto& item : leftColumn) {
		ofs << item.c_str() << "\n";
	}
	
	for (const auto& item : rightColumn) {
		ofs << item.c_str() << "\n";
	}
	
	for (const auto& match : correctMatches) {
		ofs << match + 1 << " "; 
	}
}

