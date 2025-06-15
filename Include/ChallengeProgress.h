#pragma once
#include <iostream> 
#include <ctime>
#include "MyString.h"
#include <fstream>
#include "Vector.hpp"

class ChallengeProgress {
public:
    ChallengeProgress() = default;
    enum Type { TEST_SOLVE, NORMAL_SOLVE, QUIZ_CREATE };
    Type type;
    int target;
    int current;
    bool completed;
    std::time_t completedAt;

    ChallengeProgress(Type type, int target);
    void updateProgress(int value);
    void display() const;

	virtual void readFromFile(std::ifstream& ifs);
    virtual void writeToFile(std::ofstream& ofs) const;
};