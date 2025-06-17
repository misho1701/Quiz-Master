#pragma once
#include <iostream>
#include "Utils.h"
#include "Question.h"
#include "TrueOrFalseQuestion.h"
#include "SingleChoiceQuestion.h"
#include "MultipleChoiceQuestion.h"
#include "ShortAnswerQuestion.h"
#include "MatchingPairQuestion.h"
#include "QuestionType.h"


class QuestionFactory
{
public:
	static Question* create(QuestionType type);
};