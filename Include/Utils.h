#pragma once
#include <iostream>
#include "MyString.h"
#pragma warning(disable:4996)

class String;

void setString(char*& dest, const char* src);
size_t roundToPowerOfTwo(size_t v);
bool stringCmp(const char* str1, const char* str2, size_t size);
int toInt(const String& str);
double toDouble(const String& str);
