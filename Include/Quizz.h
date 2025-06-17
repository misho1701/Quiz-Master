#pragma once
#include "Question.h"
#include "Vector.hpp"
#include "String.h"
#include <ctime>
#include <algorithm>
#include <iostream> 
#include<fstream>
#include "QuestionContainer.h"

class Quiz {
    int id;
    String title;
    QuestionContainer questions;
    int playCount;
    bool isApproved;
    bool shuffleEnabled;

public:
    enum Mode { TEST, NORMAL };

	Quiz() = default;
    Quiz(int id, const String& title);

    void addQuestion(Question* q);
    void display(Mode mode);
    int execute(Mode mode);

    int getId() const;
    String getTitle() const;
    int getPlayCount() const;
    bool getApproval() const;
    int getQuestionCount() const;
    int getTotalPoints() const;
    void approve();
    void enableShuffle(bool val);
    void shuffleQuestions();
    void incrementPlayCount();
	void readFromFile(std::ifstream& ifs);
	void writeToFile(std::ofstream& ofs) const;
	
};
