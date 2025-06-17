#include <iostream>
#include <fstream>
#include <string>
#include <limits>
#include <ctime>

#include "Vector.hpp"
#include "MyString.h"
#include "Users.h"
#include "Player.h"
#include "Admin.h"
#include "Quizz.h"
#include "ChallengeProgress.h"
#include "Message.h"
#include "TrueOrFalseQuestion.h"
#include "SingleChoiceQuestion.h"
#include "MultipleChoiceQuestion.h"
#include "ShortAnswerQuestion.h"
#include "MatchingPairQuestion.h"
#include "Utils.h"
#include "UsersFactory.h"
#include "QuestionFactory.h"
#include "UsersContainer.h"
#pragma warning(disable:4996)


UserContainer users;
Vector<Quiz*> quizzes;
Vector<Quiz*> pendingQuizzes;
Users* currentUser = nullptr;

Users* findUserByUsername(const String& username) {
	for (size_t i = 0; i < users.getSize(); ++i) {
		if (users[i]->getUsername() == username)
			return users[i];
	}

	return nullptr;
}


Quiz* findQuizById(int id) {
	for (size_t i = 0; i < quizzes.size(); ++i) {
		if (quizzes[i]->getId() == id)
			return quizzes[i];
	}
	return nullptr;
}

void playQuiz() {
	int id;
	std::cout << "Enter quiz ID to play: ";
	std::cin >> id;
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	Quiz* quiz = findQuizById(id);
	if (!quiz) {
		std::cout << "Quiz not found.\n";
		return;
	}

	int modeInput;
	std::cout << "Select mode:\n1. NORMAL\n2. TEST\nChoice: ";
	std::cin >> modeInput;
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	Quiz::Mode mode = (modeInput == 2) ? Quiz::Mode::TEST : Quiz::Mode::NORMAL;

	std::cout << "Type 'shuffle' to shuffle questions, or press Enter to continue: ";
	std::string shuffleInput;
	std::getline(std::cin, shuffleInput);
	if (shuffleInput == "shuffle") {
		quiz->shuffleQuestions();  
		std::cout << "Questions shuffled.\n";
	}

	if (mode == Quiz::Mode::TEST || mode == Quiz::Mode::NORMAL)
		quiz->display(mode);

	int score = quiz->execute(mode);
	std::cout << "You scored " << score << " points.\n";

	if (currentUser && currentUser->getRole() == Role::PLAYER) {
		Player* player = static_cast<Player*>(currentUser);

		player->addPoints(score);
		player->onQuizSolved(mode == Quiz::Mode::NORMAL);
		player->progressChallenge("solve_quiz");

		char fav;
		std::cout << "Add this quiz to your favorites? (y/n): ";
		std::cin >> fav;
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

		if (fav == 'y' || fav == 'Y') {
			player->addFavorite(String(std::to_string(quiz->getId()).c_str()));
			std::cout << "Quiz added to your favorites.\n";
		}
	}
}



int main() {

	std::string command;
	std::cout << "Welcome to Quiz System. Type 'help' for a list of commands.\n";
	
	std::ifstream ofs("users.txt");
	users.readFromTextFile(ofs);
	ofs.close();

	std::ifstream quizFile("quizzes.txt");
	while (true)
	{
		Quiz* q = new Quiz();
		q->readFromFile(quizFile);
		quizzes.push_back(q);
		if (quizFile.eof()) {
			break;
		}
		
	}
    
	quizFile.close();
	
	users.addDefaultAdministrators();

	while (true)
	{
		std::cout << "\n> ";
		std::cin >> command;

		if (command == "signup")
		{
			String fn, ln, un, pw, pw2;
			int roleInput;
			std::cout << "First name: "; std::cin >> fn;
			std::cout << "Last name: "; std::cin >> ln;
			std::cout << "Username: "; std::cin >> un;
			std::cout << "Password: "; std::cin >> pw;
			std::cout << "Confirm password: "; std::cin >> pw2;

			if (pw != pw2) {
				std::cout << "Passwords do not match.\n";
			}
			else if (findUserByUsername(un) != nullptr) {
				std::cout << "Username already exists.\n";
			}
			else if (fn.is_empty() || ln.is_empty() || un.is_empty() || pw.is_empty()) {
				std::cout << "All fields are required.\n";
			}
			else {
				users.addDefaultAdministrators();
				std::cout << "Player account created successfully.\n";
			}

			Player* newPlayer = new Player(fn, ln, un, pw);
			users.addUser(*newPlayer);
			std::ofstream ofs("users.txt", std::ios::app);
			newPlayer->writeToFile(ofs);
		}

		else if (command == "help") {
			std::cout << "Available commands:\n";
			std::cout << "signup - Create a new user account\n";
			std::cout << "login - Log in to your account\n";
			std::cout << "logout - Log out of your account\n";
			std::cout << "create-quiz - Create a new quiz\n";
			std::cout << "add-question - Add a question to a quiz\n";
			std::cout << "play-quiz - Play a quiz\n";
			std::cout << "show-favorites - Show favorite quizzes (player only)\n";
			std::cout << "admin-panel - Access admin panel (admin only)\n";
			std::cout << "view-profile - View your profile\n";
			std::cout << "view-messages - View your messages\n";
			std::cout << "view-challenges - View your challenges (player only)\n";
			std::cout << "view-quizzes - View all quizzes\n";
			std::cout << "view-users - View all users (admin only)\n";
			std::cout << "approve-quiz - Approve a quiz (admin only)\n";
			std::cout << "Ban - Ban a user (admin only)\n";
			std::cout << "remove-quiz - Remove a quiz (admin only)\n";
			std::cout << "quiz-stats - View quiz statistics (admin only)\n";
			std::cout << "reset-progress - Reset a player's progress (admin only)\n";;
			std::cout << "progress-challenge - Progress a challenge (player only)\n";
			std::cout << "exit - Exit the application\n";
		}
		else if (command == "login") {
			std::string un, pw;
			std::cout << "Username: "; std::cin >> un;
			std::cout << "Password: "; std::cin >> pw;

			Users* u = findUserByUsername(un.c_str());

			if (!u) {
				std::cout << "User not found. Please sign up first.\n";
				continue;
			}
			else if (u && u->checkPassword(pw.c_str())) {
				currentUser = u;
				std::cout << "Logged in successfully.\n";
			}
			else {
				std::cout << "Invalid credentials.\n";
			}
		}
		else if (command == "logout") {
			currentUser = nullptr;
			std::cout << "Logged out.\n";
		}
		else if (command == "create-quiz") {
			if (!currentUser || currentUser->getRole() != Role::PLAYER) {
				std::cout << "Only players can create quizzes. Please login as a player.\n";
				continue;
			}

			std::string title;
			std::cin.ignore();
			std::cout << "Enter quiz title: ";
			std::getline(std::cin, title);

			Quiz* q = new Quiz(quizzes.size() + pendingQuizzes.size() + 1, title.c_str());
			pendingQuizzes.push_back(q);

			static_cast<Player*>(currentUser)->onQuizCreated();

			std::cout << "Quiz created with ID: " << q->getId() << ". Waiting for admin approval.\n";
		}
		else if (command == "add-question") {
			if (!currentUser || currentUser->getRole() != Role::PLAYER) {
				std::cout << "Only players can add questions.\n";
				continue;
			}

			int id;
			std::cout << "Enter quiz ID: ";
			std::cin >> id;

			Quiz* q = findQuizById(id);
			if (!q) {
				std::cout << "Quiz not found.\n";
				continue;
			}

			int type;
			std::cout << "Question type:\n1. True/False\n2. Single Choice\n3. Multiple Choice\n4. Short Answer\n5. Matching Pair\nEnter type (1-5): ";
			std::cin >> type;
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

			std::string questionText;
			std::cout << "Enter question text: ";
			std::getline(std::cin, questionText);

			int points;
			std::cout << "Enter number of points: ";
			std::cin >> points;
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

			if (type == 1) {
				std::string answer;
				std::cout << "Enter answer (true/false): ";
				std::getline(std::cin, answer);
				bool isTrue = (answer == "true" || answer == "1");
				q->addQuestion(new TrueOrFalseQuestion(questionText.c_str(), points, isTrue));
			}
			else if (type == 2) {
				Vector<String> options(4);
				for (int i = 0; i < 4; i++) {
					std::cout << "Option " << i + 1 << ": ";
					std::string temp;
					std::getline(std::cin, temp);
					options.push_back(temp.c_str());
				}

				int correct;
				std::cout << "Enter correct option number (1-4): ";
				std::cin >> correct;
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

				if (correct >= 1 && correct <= 4) {
					q->addQuestion(new SingleChoiceQuestion(questionText.c_str(), points, options, correct - 1));
				}
				else {
					std::cout << "Invalid correct option number. Must be between 1 and 4.\n";
				}
			}
			else if (type == 3) {
				int numOptions;
				std::cout << "Enter number of options: ";
				std::cin >> numOptions;
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

				Vector<String> options(numOptions);
				for (int i = 0; i < numOptions; ++i) {
					std::cout << "Option " << i + 1 << ": ";
					std::string temp;
					std::getline(std::cin, temp);
					options.push_back(temp.c_str());
				}

				std::string correctInput;
				std::cout << "Enter correct answer indices separated by commas (e.g., 1,3): ";
				std::getline(std::cin, correctInput);

				std::stringstream ss(correctInput);
				std::string token;
				Vector<int> correctIndices;

				while (std::getline(ss, token, ',')) {
					int index = toInt(token.c_str()) - 1;
					if (index >= 0 && index < numOptions) {
						correctIndices.push_back(index);
					}
				}

				q->addQuestion(new MultipleChoiceQuestion(questionText.c_str(), points, options, correctIndices));
			}
			else if (type == 4) {
				std::string correct;
				std::cout << "Enter correct answer: ";
				std::getline(std::cin, correct);

				if (correct.empty()) {
					std::cout << "Error: Correct answer cannot be empty.\n";
				}
				else {
					q->addQuestion(new ShortAnswerQuestion(questionText.c_str(), points, correct.c_str()));
				}
			}
			else if (type == 5) {
				int numPairs;
				std::cout << "Enter number of pairs: ";
				std::cin >> numPairs;
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

				Vector<String> leftItems(numPairs);
				Vector<String> rightItems(numPairs);
				Vector<int> matches(numPairs);

				std::cout << "Enter items for the left column:\n";
				for (int i = 0; i < numPairs; ++i) {
					std::cout << "Left item " << i + 1 << ": ";
					std::string temp;
					std::getline(std::cin, temp);
					leftItems.push_back( temp.c_str());
				}

				std::cout << "Enter items for the right column:\n";
				for (int i = 0; i < numPairs; ++i) {
					std::cout << "Right item " << static_cast<char>('A' + i) << ": ";
					std::string temp;
					std::getline(std::cin, temp);
					rightItems.push_back(temp.c_str());
				}

				std::cout << "Enter matching letters (e.g., A, B, C) for each left item.\n";
				for (int i = 0; i < numPairs; ++i) {
					char matchLetter;
					std::cout << "Match for left item " << i + 1 << ": ";
					std::cin >> matchLetter;
					matchLetter = toupper(matchLetter);

					int matchIndex = matchLetter - 'A';
					if (matchIndex >= 0 && matchIndex < numPairs) {
						matches.push_back(matchIndex);
					}
					else {
						std::cout << "Invalid input. Defaulting to A.\n";
						matches[i] = 0;
					}
				}
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

				q->addQuestion(new MatchingPairsQuestion(questionText.c_str(), points, leftItems, rightItems, matches));
			}
		}
		else if (command == "play-quiz") {
			if (!currentUser || currentUser->getRole() != Role::PLAYER) {
				std::cout << "Only players can play quizzes.\n";
				continue;
			}
			playQuiz();
		}
		else if (command == "show-favorites") {
			if (!currentUser || currentUser->getRole() != Role::PLAYER) {
				std::cout << "Only players can view favorites.\n";
				continue;
			}
			static_cast<Player*>(currentUser)->listFavorites();
		}
		else if (command == "remove-favorite") {
			if (!currentUser || currentUser->getRole() != Role::PLAYER) {
				std::cout << "Only players can remove favorites.\n";
				continue;
			}
			int id;
			std::cout << "Enter quiz ID to remove from favorites: ";
			std::cin >> id;
			static_cast<Player*>(currentUser)->removeFavorite(std::to_string(id).c_str());
			std::cout << "Quiz removed from favorites.\n";
		}
		else if (command == "view-challenges") {
			if (!currentUser || currentUser->getRole() != Role::PLAYER) {
				std::cout << "This command is for players only.\n";
				continue;
			}
			static_cast<Player*>(currentUser)->viewChallenges();
		}
		else if (command == "view-profile") {
			if (!currentUser) {
				std::cout << "Please login first.\n";
				continue;
			}
			currentUser->viewProfile();
		}
		else if (command == "view-messages") {
			if (!currentUser) {
				std::cout << "Please login first.\n";
				continue;
			}
			currentUser->viewMessages();
		}
		else if (command == "view-quizzes") {
			for (size_t i = 0; i < quizzes.size(); ++i) {
				quizzes[i]->display(Quiz::Mode::NORMAL);
			}
		}
		else if (command == "progress-challenge") {
			if (!currentUser || currentUser->getRole() != Role::PLAYER) {
				std::cout << "This command is for players only.\n";
				continue;
			}
			static_cast<Player*>(currentUser)->progressChallenge("solve_quiz");
			std::cout << "Challenge progressed.\n";
		}
		else if (command == "admin-panel") {
			if (!currentUser || currentUser->getRole() != Role::ADMIN) {
				std::cout << "Admin access only.\n";
				continue;
			}

			std::string subcommand;
			std::cout << "\n--- Admin Panel ---\n";
			std::cout << "Commands: view-users, approve-quiz, Ban, view-quizzes, remove-quiz, quiz-stats, reset-progress, back\n";

			while (true) {
				std::cout << "\n[admin-panel] > ";
				std::cin >> subcommand;

				if (subcommand == "view-users") {
					String username;
					for (size_t i = 0; i < users.getSize(); ++i) {
						if (users[i]->getUsername() == username) {
							users.removeAt(i);
							std::cout << "User removed.\n";
							break;
						}
					}
				}

				else if (subcommand == "Ban") {
					String username;
					std::cout << "Enter username to ban: ";
					std::cin >> username;

					bool found = false;
					for (size_t i = 0; i < users.getSize(); ++i) {
						if (users[i]->getUsername() == username) {
							users.removeAt(i);
							std::cout << "User banned.\n";
							found = true;
							break;
						}
					}
					if (!found) std::cout << "User not found.\n";
				}

				else if (subcommand == "view-quizzes") {
					for (size_t i = 0; i < quizzes.size(); ++i) {
						std::cout << "Quiz ID: " << quizzes[i]->getId()
							<< ", Title: " << quizzes[i]->getTitle().c_str() << "\n";
					}
				}
				else if (subcommand == "approve-quiz") {
					if (!currentUser || currentUser->getRole() != Role::ADMIN) {
						std::cout << "Only admins can approve quizzes.\n";
						continue;
					}

					if (pendingQuizzes.is_empty()) {
						std::cout << "No pending quizzes for approval.\n";
						continue;
					}

					std::cout << "Pending quizzes:\n";
					for (size_t i = 0; i < pendingQuizzes.size(); ++i) {
						std::cout << "[" << i + 1 << "] ";
						pendingQuizzes[i]->display(Quiz::Mode::NORMAL);
					}

					int choice;
					std::cout << "Enter quiz number to approve: ";
					std::cin >> choice;

					if (choice >= 1 && static_cast<size_t>(choice) <= pendingQuizzes.size()) {
						Quiz* approved = pendingQuizzes[choice - 1];
						quizzes.push_back(approved);

						Vector<Quiz*> updatedPending;
						for (size_t i = 0; i < pendingQuizzes.size(); ++i) {
							if (i != static_cast<size_t>(choice - 1)) {
								updatedPending.push_back(pendingQuizzes[i]);
							}
						}

						pendingQuizzes = updatedPending;

						std::cout << "Quiz approved and published.\n";
					}
					else {
						std::cout << "Invalid selection.\n";
					}
				}
				else if (subcommand == "remove-quiz") {
					int id;
					std::cout << "Enter quiz ID to remove: ";
					std::cin >> id;
					std::cin.ignore();

					std::string reason;
					std::cout << "Enter reason for removing the quiz: ";
					std::getline(std::cin, reason);

					bool found = false;
					for (size_t i = 0; i < quizzes.size(); ++i) {
						if (quizzes[i]->getId() == id) {
							delete quizzes[i];

							for (size_t j = i; j < quizzes.size() - 1; ++j) {
								quizzes[j] = quizzes[j + 1];
							}
							quizzes.pop_back();

							std::cout << "Quiz removed. Reason: " << reason << "\n";
							found = true;
							break;
						}
					}

					if (!found)
						std::cout << "Quiz not found.\n";
				}

				else if (subcommand == "quiz-stats") {
					int id;
					std::cout << "Enter quiz ID: ";
					std::cin >> id;
					Quiz* q = findQuizById(id);
					if (!q) {
						std::cout << "Quiz not found.\n";
					}
					else {
						std::cout << "Quiz Title: " << q->getTitle().c_str() << "\n";
						std::cout << "Number of Questions: " << q->getQuestionCount() << "\n";
						std::cout << "Total Points: " << q->getTotalPoints() << "\n";
					}
				}
				else if (subcommand == "reset-progress") {
					String username;
					std::cout << "Enter username to reset progress: ";
					std::cin >> username;
					Users* user = findUserByUsername(username);
					if (user && user->getRole() == Role::PLAYER) {
						static_cast<Player*>(user)->resetProgress();
						std::cout << "Progress reset.\n";
					}
					else {
						std::cout << "Player not found or not a valid player.\n";
					}
				}
				else if (subcommand == "back") {
					break;
				}
				else {
					std::cout << "Unknown admin command.\n";
				}
			}
		}
		else if (command == "exit") {
			std::cout << "Exiting...\n";
			std::ofstream ofs1("quizzes.txt");
			for (size_t i = 0; i < quizzes.size(); ++i) {
				quizzes[i]->writeToFile(ofs1);
			}
			ofs1.close();

			std::ofstream ofs2("pending.txt");
			for (size_t i = 0; i < pendingQuizzes.size(); ++i) {
				pendingQuizzes[i]->writeToFile(ofs2);
			}

			ofs2.close();
			break;
		}
		else {
			std::cout << "Unknown command.\n";
		}
	}
	return 0;
}
