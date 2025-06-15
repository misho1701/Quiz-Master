#include "QuestionFactory.h"

Question* QuestionFactory::create(QuestionType type)
{
    switch (type)
    {
    case QuestionType::TrueOrFalse:
        return new TrueOrFalseQuestion();

    case QuestionType::SingleChoice:
        return new SingleChoiceQuestion();

    case QuestionType::MultipleChoice:
        return new MultipleChoiceQuestion();

    case QuestionType::ShortAnswer:
        return new ShortAnswerQuestion();

    case QuestionType::MatchingPairs:
        return new MatchingPairsQuestion();

    default:
        return nullptr;
    }
}