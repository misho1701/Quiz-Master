#include "Question.h"

Question::Question(const String& txt, int pts) : text(txt), points(pts) {}

int Question::getPoints() const {
    return points;
}
void Question::readFromFile(std::ifstream& ifs) {
	ifs >> points;
	ifs.ignore();

	std::string tempText;
	std::getline(ifs, tempText);
	text = String(tempText.c_str());
}

void Question::writeToFile(std::ofstream& ofs) const {
	ofs << points << '\n';
	ofs << text.c_str() << '\n';
}

String Question::getText() const {
	return text;
}