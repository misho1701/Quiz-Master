#include "Users.h"
#include <iostream>

Users::Users(const String& fn, const String& ln, const String& un, const String& pw)
	: firstName(fn), lastName(ln), username(un), password(pw), isBanned(false) {}

Users::~Users() {}

String Users::getUsername() const { return username; }
bool Users::checkPassword(const String& pw) const { return password == pw; }
bool Users::getBanStatus() const { return isBanned; }
void Users::ban() { isBanned = true; }

void Users::viewProfile() const {
	std::cout << "User: " << username.c_str() << "\n";
	std::cout << "Name: " << firstName.c_str() << " " << lastName.c_str() << "\n";
	std::cout << "Messages:\n";
	for (size_t i = 0; i < messages.size(); ++i) {
		messages[i].display();
	}
	std::cout << "Favorite Quizzes:\n";
	for (size_t i = 0; i < favoriteQuizzes.size(); ++i) {
		std::cout << favoriteQuizzes[i].getTitle().c_str() << "\n";
	}
	std::cout << "Challenges:\n";
	for (size_t i = 0; i < challenges.size(); ++i) {
		challenges[i].display();
	}
	std::cout << "Banned: " << (isBanned ? "Yes" : "No") << "\n";
	std::cout << "Total Messages: " << messages.size() << "\n";
	std::cout << "Total Favorite Quizzes: " << favoriteQuizzes.size() << "\n";
	std::cout << "Total Challenges: " << challenges.size() << "\n";
	std::cout << "------------------------\n";
}

void Users::receiveMessage(const String& msg) {
	messages.push_back(Message(msg));
	std::cout << "Message received: " << msg.c_str() << "\n";
}

void Users::viewMessages() const {
	for (size_t i = 0; i < messages.size(); ++i) {
		messages[i].display();
	}
	if (messages.is_empty()) {
		std::cout << "No messages.\n";
	}
	std::cout << "Total Messages: " << messages.size() << "\n";
}

void Users::addToFavorites(Quiz* q) {
	favoriteQuizzes.push_back(*q);
	std::cout << "Quiz '" << q->getTitle().c_str() << "' added to favorites.\n";
	if (q == nullptr) {
		std::cout << "Warning: Attempted to add a null quiz to favorites.\n";
		return;
	}
	if (favoriteQuizzes.size() > 100) {
		std::cout << "Warning: Favorites list exceeds 100 quizzes. Consider removing some.\n";
	}
	else {
		std::cout << "Total Favorite Quizzes: " << favoriteQuizzes.size() << "\n";
	}
	if (q->getId() < 0) {
		std::cout << "Warning: Attempted to add a quiz with negative ID to favorites.\n";
		return;
	}
}

void Users::removeFromFavorites(int id) {
	for (size_t i = 0; i < favoriteQuizzes.size(); ++i) {
		if (favoriteQuizzes[i].getId() == id) {
			favoriteQuizzes.remove_at(i);
			break;
		}
	}
	if (favoriteQuizzes.is_empty()) {
		std::cout << "No favorite quizzes left.\n";
	}
	else {
		std::cout << "Favorite quizzes updated. Total: " << favoriteQuizzes.size() << "\n";
	}
	if (id < 0) {
		std::cout << "Warning: Attempted to remove a quiz with negative ID from favorites.\n";
		return;
	}
	std::cout << "Quiz with ID " << id << " removed from favorites.\n";
}

void Users::showFavorites() const {
	for (size_t i = 0; i < favoriteQuizzes.size(); ++i) {
		std::cout << favoriteQuizzes[i].getTitle().c_str() << "\n";
	}
	if (favoriteQuizzes.is_empty()) {
		std::cout << "No favorite quizzes.\n";
	}
	else {
		std::cout << "Total Favorite Quizzes: " << favoriteQuizzes.size() << "\n";
	}
	if (favoriteQuizzes.size() > 100) {
		std::cout << "Warning: Favorites list exceeds 100 quizzes. Consider removing some.\n";
	}
	std::cout << "------------------------\n";
}

void Users::printInfo() const {
    std::cout << "Name: " << firstName;
    std::cout << "Last name: " << lastName;
    std::cout << "Username: " << username;
    std::cout << std::endl;
}


void Users::writeToFile(std::ofstream& ofs) const
{
	ofs << firstName.c_str() << '\n';
	ofs << lastName.c_str() << '\n';
	ofs << username.c_str() << '\n';
	ofs << password.c_str() << '\n';
	ofs << isBanned << '\n';

	ofs << messages.size() << '\n';
	for (const auto& msg : messages) {
		ofs << msg.getContent().c_str() << '\n';
	}

	ofs << favoriteQuizzes.size() << '\n';
	for (const auto& quiz : favoriteQuizzes) {
		ofs << quiz.getTitle().c_str() << '\n'; 
	}

	ofs << challenges.size() << '\n';
	for (const auto& challenge : challenges) {
		challenge.writeToFile(ofs);
	}
}


void Users::readFromFile(std::ifstream& ifs)
{
	ifs.ignore();
	std::string tempFirstName, tempLastName, tempUsername, tempPassword;
	std::getline(ifs, tempFirstName);
	std::getline(ifs, tempLastName);
	std::getline(ifs, tempUsername);
	std::getline(ifs, tempPassword);

	firstName = String(tempFirstName.c_str());
	lastName = String(tempLastName.c_str());
	username = String(tempUsername.c_str());
	password = String(tempPassword.c_str());

	ifs >> isBanned;
	ifs.ignore(); 

	size_t msgCount;
	ifs >> msgCount;
	ifs.ignore(); 
	messages.resize(msgCount);
	for (size_t i = 0; i < msgCount; ++i) {
		messages[i].readFromFile(ifs);
	}

	size_t favQuizCount;
	ifs >> favQuizCount;
	ifs.ignore(); 
	favoriteQuizzes.resize(favQuizCount);

	size_t challengeCount;
	ifs >> challengeCount;
	ifs.ignore(); 
	challenges.resize(challengeCount);
	for (size_t i = 0; i < challengeCount; ++i) {
		challenges[i].readFromFile(ifs);
	}
}


