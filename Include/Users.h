#pragma once
#include <string>
#include "MyString.h"
#include "Message.h"
#include "Vector.hpp"
#include "Quizz.h"
#include "ChallengeProgress.h"
#pragma warning(disable:4996)


class Users {
protected:
    String firstName, lastName, username, password;
    Vector<Message> messages;
    Vector<Quiz*> favoriteQuizzes;
    Vector<ChallengeProgress> challenges;
    bool isBanned;

public:

    enum class Role {
        ADMIN,
        PLAYER
    };
    Users(const String& fn, const String& ln, const String& un, const String& pw);
    virtual ~Users();

    String getUsername() const;
    bool checkPassword(const String& pw) const;
    bool getBanStatus() const;
    void ban();

    virtual void viewProfile() const;
    void receiveMessage(const String& msg);
    void viewMessages() const;
    void addToFavorites(Quiz* q);
    void removeFromFavorites(int id);
    void showFavorites() const;
    virtual Role getRole() const = 0;
    virtual bool isAdmin() const = 0;
	virtual bool isPlayer() const = 0;
    virtual void printInfo() const;

    virtual void readFromFile(std::ifstream& ifs);
    virtual void writeToFile(std::ofstream& ofs) const;
};