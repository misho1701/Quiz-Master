﻿#include "Quizz.h"
#include <iostream>
#include <algorithm>
#include <cstdlib>
#include<string>

Quiz::Quiz(int id, const String& title)
	: id(id), title(title), playCount(0), isApproved(false), shuffleEnabled(false) {}


void Quiz::addQuestion(Question* q)
{
	questions.addQuestion(q);
	std::cout << "Question added to quiz '" << title.c_str() << "'. Total questions: " << questions.getSize() << "\n";
	if (q == nullptr) {
		std::cout << "Warning: Attempted to add a null question to the quiz.\n";
		return;
	}
}

void Quiz::display(Mode mode) {
	std::cout << "Quiz: " << title.c_str() << " [ID: " << id << "]\n";
	for (size_t i = 0; i < questions.getSize(); ++i) {
		std::cout << "Question " << i + 1 << ": ";
		questions.getQuestion(i)->display();
	}
	if (mode == TEST) {
		std::cout << "Mode: TEST\n";
	}
	else {
		std::cout << "Mode: NORMAL\n";
	}
	std::cout << "Total Questions: " << questions.getSize() << "\n";
	std::cout << "Play Count: " << playCount << "\n";
	std::cout << "Approved: " << (isApproved ? "Yes" : "No") << "\n";
	std::cout << "Shuffle Enabled: " << (shuffleEnabled ? "Yes" : "No") << "\n";
	std::cout << "------------------------\n";
}

int Quiz::execute(Mode mode)
{
	if (questions.is_empty()) {
		std::cout << "No questions available in this quiz.\n";
		return 0;
	}

	QuestionContainer execQuestions = questions;

	if (shuffleEnabled) {
		execQuestions.shuffle();
	}

	std::cout << "Starting quiz in " << (mode == TEST ? "TEST" : "NORMAL") << " mode. "
		<< "Type 'exit' to quit, 'skip' to skip a question, or 'help' for commands.\n";
	std::cout << "Total Questions: " << execQuestions.getSize() << "\n";

	int score = 0;

	for (size_t i = 0; i < execQuestions.getSize(); ++i) {
		execQuestions.getQuestion(i)->display();

		std::string inputBuffer;
		std::getline(std::cin, inputBuffer);
		String userInput = inputBuffer.c_str();

		userInput = userInput.trim();

		if (userInput.is_empty()) {
			std::cout << "No input provided. Please try again.\n";
			--i;
			continue;
		}
		if (userInput == "exit") {
			std::cout << "Exiting quiz.\n";
			return score;
		}
		if (userInput == "skip") {
			std::cout << "Question skipped.\n";
			continue;
		}
		if (userInput == "help") {
			std::cout << "Available commands: exit, skip, help\n";
			--i;
			continue;
		}
		if (userInput.length() > 1024) {
			std::cout << "Input too long. Please try again.\n";
			--i;
			continue;
		}
		if (userInput.length() < 1) {
			std::cout << "Input too short. Please try again.\n";
			--i;
			continue;
		}

		bool correct = execQuestions.getQuestion(i)->checkAnswer(userInput);

		if (mode == NORMAL && correct) {
			score += execQuestions.getQuestion(i)->getPoints();
			std::cout << (correct ? "Correct!\n" : "Wrong!\n");
		}

		if (mode == TEST) {
			std::cout << (correct ? "Correct!\n" : "Wrong!\n");
		}

		std::cout << "---\n";
	}

	if (mode == NORMAL) {
		std::cout << "Total Score: " << score << "\n";
		incrementPlayCount();
	}

	return score;
}



int Quiz::getId() const { return id; }
String Quiz::getTitle() const { return title; }
int Quiz::getPlayCount() const { return playCount; }
bool Quiz::getApproval() const { return isApproved; }
int Quiz::getQuestionCount() const
{
	return questions.getSize();
}
int Quiz::getTotalPoints() const
{
	int totalPoints = 0;
	for (size_t i = 0; i < questions.getSize(); ++i) {
		totalPoints += questions.getQuestion(i)->getPoints();
	}
	return totalPoints;
}
void Quiz::approve() { isApproved = true; }
void Quiz::enableShuffle(bool val) { shuffleEnabled = val; }
void Quiz::shuffleQuestions()
{
	if (shuffleEnabled) {
		questions.shuffle();
		std::cout << "Questions shuffled.\n";
	}
	else {
		std::cout << "Shuffle is disabled. Cannot shuffle questions.\n";
	}
}
void Quiz::incrementPlayCount() { playCount++; }

void Quiz::readFromFile(std::ifstream& ifs){
	ifs >> id;
	ifs.ignore();
	std::string tempTitle;
	std::getline(ifs, tempTitle);
	title = String(tempTitle.c_str());
	ifs >> playCount;
	ifs >> isApproved;

	while (true) {

		int type;
		ifs >> type;

		Question* question = QuestionFactory::create((QuestionType)type);

		question->readFromFile(ifs);
			
		
		if (question->getText().is_empty() || ifs.eof()) {
			return;
		}
		this->addQuestion(question);
	}
}

void Quiz::writeToFile(std::ofstream& ofs) const
{
	ofs << id << "\n";
	ofs << title.c_str() << "\n";
	ofs << playCount << "\n";
	ofs << isApproved << "\n";

	for (size_t i = 0; i < questions.getSize(); ++i) {
		questions.getQuestion(i)->writeToFile(ofs);
	}
}






