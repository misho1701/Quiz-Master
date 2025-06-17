#pragma once
#include "Users.h"
#include "MyString.h"
#include "Vector.hpp"
#include <ctime>
#include "Utils.h"
#pragma warning(disable:4996)

struct Challenge {
    String type;
    int target;
    int progress;
    int rewardPoints;
    bool completed;
    time_t completionTime;
};

class Player : public Users {
    int points;
    int level;
    int quizzesSolvedTest;
    int quizzesSolvedNormal;
    int quizzesCreated;
    Vector<Challenge> activeChallenges;
    Vector<Challenge> completedChallenges;
    Vector<String> favoriteQuizzesPlayer;

    void updateLevel();

public:
    
	Player() = default;
    Player(const String& fn, const String& ln, const String& un, const String& pw);

    void addPoints(int p);
    void addFavorite(const String& quizId);
    void removeFavorite(const String& quizId);
    void listFavorites() const;
    void onQuizSolved(bool isNormal);
    void onQuizCreated();

    void addChallenge(const Challenge& c);
    void progressChallenge(const String& type);
    void printChallenges() const;
    void printCompletedChallenges() const;
	void viewChallenges() const;

    int getPoints() const;
    Role getRole() const override;
	void resetProgress();
	bool isPlayer() const override;
    bool isAdmin() const override;
    void printInfo() const override;
	Users* clone() const override;

	void readFromFile(std::ifstream& ifs) override;
	void writeToFile(std::ofstream& ofs) const override;
};
