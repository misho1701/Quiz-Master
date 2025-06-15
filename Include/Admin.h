#pragma once
#include "Users.h"
#include "MyString.h"
#include "Quizz.h"
#include "Utils.h"
#include <fstream>

class Admin : public Users {
public:
    enum class Role {
        ADMIN,
        PLAYER
    };
    Admin(const String& fName, const String& lName, const String& uname, const String& pwd);
    Users::Role getRole() const override;
    bool isAdmin() const override;
    bool isPlayer() const override;
    void approveQuiz(Quiz& quiz);
    void rejectQuiz(Quiz& quiz, const String& reason);
    void removeQuiz(Quiz& quiz, const String& reason);
    void readFromFile(std::ifstream& ifs) override;
	void writeToFile(std::ofstream& ofs) const override;
};