#pragma once
#include <iostream>
#include <fstream>
#include <ctime>
#include <cstdlib>  
#include "MyString.h"
#include "Vector.hpp"
#include "Question.h"
#include "QuestionFactory.h"

class QuestionContainer
{
public:
	QuestionContainer();
	QuestionContainer(const QuestionContainer& other);
	QuestionContainer& operator=(const QuestionContainer& other);
	~QuestionContainer();

	void shuffle();
	void addQuestion(const Question* newQuestion);
	void writeToBinaryFile(std::ofstream& ofs) const;
	void readFromBinaryFile(std::ifstream& ifs);
	bool is_empty() const;
	int getSize() const;
	Question* getQuestion(int index) const;

private:
	void copyFrom(const QuestionContainer& other);
	void free();

	void resize(int newCapacity);
	static unsigned calculateCapacity(unsigned size, unsigned minCapacity);
	static constexpr unsigned MIN_CAPACITY = 16;
	static constexpr unsigned RESIZE_COEFF = 2;

	Question** arr;
	int size;
	int capacity;
};
