#include "QuestionContainer.h"

QuestionContainer::QuestionContainer()
{
    size = 0;
    capacity = MIN_CAPACITY;
    arr = new Question * [capacity];
}
QuestionContainer::QuestionContainer(const QuestionContainer& other)
{
    copyFrom(other);
}
QuestionContainer& QuestionContainer::operator=(const QuestionContainer& other)
{
    if (this != &other)
    {
        free();
        copyFrom(other);
    }
    return *this;
}
QuestionContainer::~QuestionContainer()
{
    free();
}

void QuestionContainer::copyFrom(const QuestionContainer& other)
{
    size = other.size;
    capacity = other.capacity;
    arr = new Question * [capacity];
    for (int i = 0; i < size; i++)
    {
        arr[i] = other.arr[i]->clone();
    }
}
void QuestionContainer::free()
{
    for (int i = 0; i < size; i++)
    {
        delete arr[i];
    }
    delete[] arr;
}

void QuestionContainer::resize(int newCapacity)
{
    capacity = newCapacity;
    Question** temp = new Question * [capacity];
    for (int i = 0; i < size; i++)
    {
        temp[i] = arr[i];
    }
    delete[] arr;
    arr = temp;
}
unsigned QuestionContainer::calculateCapacity(unsigned size, unsigned minCapacity)
{
    if (size == 0)
    {
        return minCapacity;
    }
    while (size < minCapacity)
    {
        size *= RESIZE_COEFF;
    }
    return size;
}

void QuestionContainer::shuffle()
{
    if (size <= 1)
    {
        return;
    }
    std::srand(std::time(nullptr));
    for (int i = size - 1; i > 0; i--)
    {
        int j = std::rand() % (i + 1);
        std::swap(arr[i], arr[j]);
    }
}
void QuestionContainer::addQuestion(const Question* newQuestion)
{
    if (size == capacity)
    {
        resize(capacity * RESIZE_COEFF);
    }
    arr[size++] = newQuestion->clone();
}
void QuestionContainer::writeToBinaryFile(std::ofstream& ofs) const
{
    ofs.write((const char*)&size, sizeof(size));
    for (int i = 0; i < size; i++)
    {
        bool hasQuestion = (arr[i] != nullptr);
        ofs.write((const char*)&hasQuestion, sizeof(hasQuestion));
        if (hasQuestion)
        {
            arr[i]->writeToFile(ofs);
        }
    }
}
void QuestionContainer::readFromBinaryFile(std::ifstream& ifs)
{
    free();
    ifs.read((char*)&size, sizeof(size));
    capacity = calculateCapacity(size, MIN_CAPACITY);
    arr = new Question * [capacity];
    for (int i = 0; i < size; i++)
    {
        bool hasQuestion = false;
        ifs.read((char*)&hasQuestion, sizeof(hasQuestion));
        if (hasQuestion)
        {
            QuestionType type;
            ifs.read((char*)&type, sizeof(type));
            arr[i] = QuestionFactory::create(type);
            arr[i]->readFromFile(ifs);
        }
        else
        {
            arr[i] = nullptr;
        }
    }
}

bool QuestionContainer::is_empty() const
{
    return this->size == 0;
}

int QuestionContainer::getSize() const
{
    return size;
}

Question* QuestionContainer::getQuestion(int index) const
{
	if (index < 0 || index >= size)
	{
		throw std::out_of_range("Index out of range");
	}
    return arr[index];
}
