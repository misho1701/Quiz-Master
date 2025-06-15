#include "Admin.h"

Admin::Admin(const String& fName, const String& lName, const String& uname, const String& pwd)
    : Users(fName, lName, uname, pwd) {}

Users::Role Admin::getRole() const
{
	return Users::Role::ADMIN;
}

bool Admin::isAdmin() const {
    return true;
}

bool Admin::isPlayer() const
{
	return false;
}

void Admin::approveQuiz(Quiz& quiz) {
	quiz.approve();
	quiz.incrementPlayCount();
}

void Admin::rejectQuiz(Quiz& quiz, const String& reason) {
	String message("Quiz ID: ");
	message.concat(quiz.getId()).concat(" rejected: ").concat(reason);
	receiveMessage(message);
}

void Admin::removeQuiz(Quiz& quiz, const String& reason) {
	String message("Quiz ID: ");
	message.concat(quiz.getId()).concat(" removed: ").concat(reason);
	receiveMessage(message);
}

void Admin::readFromFile(std::ifstream& ifs)
{
	Users::readFromFile(ifs);
}

void Admin::writeToFile(std::ofstream& ofs) const
{
	Users::writeToFile(ofs);
}