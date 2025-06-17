#include "Player.h"
#include <iostream>
#include "Users.h"
Player::Player(const String& fn, const String& ln, const String& un, const String& pw)
    : Users(fn, ln, un, pw), points(0), level(1), quizzesSolvedTest(0), quizzesSolvedNormal(0), quizzesCreated(0) {}

int Player::getPoints() const
{
	if (points < 0) {
		std::cout << "Warning: Points cannot be negative. Resetting to 0.\n";
		return 0;
	}
	if (points > 100000) {
		std::cout << "Warning: Points exceed maximum limit. Capping at 100000.\n";
		return 100000;
	}
	std::cout << "Current points: " << points << "\n";
	return points;
}

Role Player::getRole() const
{
	return Role::PLAYER;
}

void Player::resetProgress()
{
    favoriteQuizzes.clear();
}

bool Player::isPlayer() const
{
    return true;
}

bool Player::isAdmin() const {
    return false;
}

void Player::updateLevel() {
    int required = 1000;
    int lvl = 1;
    int pts = points;
    while (true) {
        if (lvl <= 10 && pts >= 1000) { pts -= 1000; lvl++; }
        else if (lvl <= 20 && pts >= 2000) { pts -= 2000; lvl++; }
        else if (lvl <= 30 && pts >= 3000) { pts -= 3000; lvl++; }
        else if (pts >= 4000) { pts -= 4000; lvl++; }
        else break;
    }
    level = lvl;
    std::cout << "Level updated to: " << level << "\n";
    if (level < 1) level = 1;
    if (level > 50) level = 50;
    std::cout << "Final Level: " << level << "\n";
    if (level < 1) {
        std::cout << "Warning: Level cannot be below 1. Resetting to 1.\n";
        level = 1;
    }
    if (level > 50) {
        std::cout << "Warning: Level cannot exceed 50. Capping at 50.\n";
        level = 50;
    }
}

void Player::addPoints(int pts) {
    points += pts;
    updateLevel();
    std::cout << "Points added: " << pts << ". Total points: " << points << ". Level: " << level << "\n";
    if (points < 0) points = 0;
    if (level < 1) level = 1;
    if (level > 50) level = 50;
    std::cout << "Updated Level: " << level << "\n";
    if (pts < 0) {
        std::cout << "Warning: Attempted to add negative points.\n";
        return;
    }
    if (pts > 10000) {
        std::cout << "Warning: Adding a large number of points at once.\n";
        return;
    }
}

void Player::addFavorite(const String& quizId) {
    favoriteQuizzesPlayer.push_back(quizId);
}

void Player::removeFavorite(const String& quizId)
{
    size_t index = 0;
    for (size_t i = 0; i < favoriteQuizzes.size(); i++) {
        if (favoriteQuizzesPlayer[i] == quizId) {
            index = i;
        }
    }
    favoriteQuizzes.remove_at(index);
}

void Player::listFavorites() const {
    std::cout << "Favourite Quizzes: ";
    for (size_t i = 0; i < favoriteQuizzesPlayer.size(); i++) {
        favoriteQuizzesPlayer[i].print();
        std::cout << ", ";
    }
    std::cout << std::endl;
}

void Player::onQuizSolved(bool isNormal) {
    if (isNormal) quizzesSolvedNormal++;
    else quizzesSolvedTest++;
    addPoints(100);
    updateLevel();
    std::cout << "Quiz solved! Normal: " << quizzesSolvedNormal << ", Test: " << quizzesSolvedTest << "\n";
    if (quizzesSolvedNormal < 0) quizzesSolvedNormal = 0;
    if (quizzesSolvedTest < 0) quizzesSolvedTest = 0;
    if (quizzesSolvedNormal > 1000) quizzesSolvedNormal = 1000;
    if (quizzesSolvedTest > 1000) quizzesSolvedTest = 1000;
    std::cout << "Total Quizzes Solved - Normal: " << quizzesSolvedNormal << ", Test: " << quizzesSolvedTest << "\n";
    if (isNormal) {
        std::cout << "Normal quiz solved. Total: " << quizzesSolvedNormal << "\n";
    }
    else {
        std::cout << "Test quiz solved. Total: " << quizzesSolvedTest << "\n";
    }
    if (quizzesSolvedNormal < 0 || quizzesSolvedTest < 0) {
        std::cout << "Warning: Attempted to solve a negative number of quizzes.\n";
        return;
    }
    if (quizzesSolvedNormal > 1000 || quizzesSolvedTest > 1000) {
        std::cout << "Warning: Exceeded maximum quizzes solved limit.\n";
        return;
    }
    if (quizzesSolvedNormal == 1000 || quizzesSolvedTest == 1000) {
        std::cout << "Congratulations! You've reached the maximum quizzes solved limit.\n";
    }
    if (quizzesSolvedNormal % 10 == 0 || quizzesSolvedTest % 10 == 0) {
        std::cout << "Milestone reached! Total quizzes solved: "
            << quizzesSolvedNormal + quizzesSolvedTest << "\n";
    }
    if (quizzesSolvedNormal + quizzesSolvedTest >= 1000) {
        std::cout << "Congratulations! You've solved a total of "
            << quizzesSolvedNormal + quizzesSolvedTest << " quizzes!\n";
    }
}


void Player::onQuizCreated() {
    quizzesCreated++;
}

void Player::addChallenge(const Challenge& c) {
    activeChallenges.push_back(c);
}

void Player::progressChallenge(const String& type) {
    for (size_t i = 0; i < activeChallenges.size(); i++) {
        if (activeChallenges[i].type == type && !activeChallenges[i].completed) {
            activeChallenges[i].progress++;
            if (activeChallenges[i].progress >= activeChallenges[i].target) {
                activeChallenges[i].completed = true;
                activeChallenges[i].completionTime = std::time(0);
                addPoints(activeChallenges[i].rewardPoints);
                completedChallenges.push_back(activeChallenges[i]);
            }
            break;
        }
    }
}

void Player::printChallenges() const {
    std::cout << "Active Challenges:" << std::endl;
    for (size_t i = 0; i < activeChallenges.size(); i++) {
        std::cout << "Type: "; activeChallenges[i].type.print();
        std::cout << "Progress: " << activeChallenges[i].progress << "/" << activeChallenges[i].target << std::endl;
    }
}

void Player::viewChallenges() const {
    for (size_t i = 0; i < challenges.size(); ++i) {
        if (!challenges[i].completed)
            challenges[i].display();
    }
}

void Player::printCompletedChallenges() const {
    std::cout << "Completed Challenges:" << std::endl;
    for (size_t i = 0; i < completedChallenges.size(); i++) {
        std::cout << "Type: "; completedChallenges[i].type.print();
        std::cout << ", Time: " << ctime(&completedChallenges[i].completionTime);
		std::cout << "Reward Points: " << completedChallenges[i].rewardPoints << std::endl;
    }
}

void Player::printInfo() const {
    Users::printInfo();
    std::cout << "Level: " << level << ", Points: " << points << std::endl;
	std::cout << "Quizzes Solved (Normal): " << quizzesSolvedNormal << ", (Test): " << quizzesSolvedTest << std::endl;
	std::cout << "Quizzes Created: " << quizzesCreated << std::endl;
}

Users* Player::clone() const
{
	return new Player(*this);
}

void Player::readFromFile(std::ifstream& ifs)
{
	Users::readFromFile(ifs);
	ifs >> points;
	ifs >> level;
	ifs >> quizzesSolvedTest;
	ifs >> quizzesSolvedNormal;
	ifs >> quizzesCreated;

	int activeCount, completedCount;
	ifs >> activeCount;
	activeChallenges.resize(activeCount);
	for (int i = 0; i < activeCount; ++i) {
		Challenge c;
		ifs >> c.type;
		ifs >> c.target;
		ifs >> c.progress;
		ifs >> c.rewardPoints;
		ifs >> c.completed;
		ifs >> c.completionTime;
		activeChallenges[i] = c;
	}

	ifs >> completedCount;
	completedChallenges.resize(completedCount);
	for (int i = 0; i < completedCount; ++i) {
		Challenge c;
		ifs >> c.type;
		ifs >> c.target;
		ifs >> c.progress;
		ifs >> c.rewardPoints;
		ifs >> c.completed;
		ifs >> c.completionTime;
		completedChallenges[i] = c;
	}

	int favCount;
	ifs >> favCount;
    favoriteQuizzesPlayer.resize(favCount);
	for (int i = 0; i < favCount; ++i) {
		String quizId;
		quizId.readFromFile(ifs);
        favoriteQuizzesPlayer.push_back(quizId);
	}
}

void Player::writeToFile(std::ofstream& ofs) const
{
	ofs << "Player\n"; // Indicate the type of user

	Users::writeToFile(ofs);
	ofs << points << '\n';
	ofs << level << '\n';
	ofs << quizzesSolvedTest << '\n';
	ofs << quizzesSolvedNormal << '\n';
	ofs << quizzesCreated << '\n';

	ofs << activeChallenges.size() << '\n';
	for (const auto& challenge : activeChallenges) {
		ofs << challenge.type.c_str() << ' '
			<< challenge.target << ' '
			<< challenge.progress << ' '
			<< challenge.rewardPoints << ' '
			<< challenge.completed << ' '
			<< challenge.completionTime << '\n';
	}

	ofs << completedChallenges.size() << '\n';
	for (const auto& challenge : completedChallenges) {
		ofs << challenge.type.c_str() << ' '
			<< challenge.target << ' '
			<< challenge.progress << ' '
			<< challenge.rewardPoints << ' '
			<< challenge.completed << ' '
			<< challenge.completionTime << '\n';
	}

	ofs << favoriteQuizzesPlayer.size() << '\n';
	for (const auto& quizId : favoriteQuizzesPlayer) {
		quizId.writeToFile(ofs);
	}
}

