#include "Utils.h"
#include <stdexcept>
#include <cctype>

void setString(char*& dest, const char* src) {
    if (dest) {
        delete[] dest;
        dest = nullptr;
    }
    size_t len = strlen(src);
    dest = new char[len + 1];
    strcpy(dest, src);
}

size_t roundToPowerOfTwo(size_t v)
{
    if (v == 0) return 1;

    v--;
#if SIZE_MAX > UINT32_MAX
    v |= v >> 1;
    v |= v >> 2;
    v |= v >> 4;
    v |= v >> 8;
    v |= v >> 16;
    v |= v >> 32;
#else
    v |= v >> 1;
    v |= v >> 2;
    v |= v >> 4;
    v |= v >> 8;
    v |= v >> 16;
#endif
    v++;
    return v;
}

bool stringCmp(const char* str1, const char* str2, size_t size) {
    if (!str1 || !str2) return false;
    for (size_t i = 0; i < size; i++) {
        if (str1[i] != str2[i]) {
            return false;
        }
    }
    return true;
}

int toInt(const String& str) {
    int result = 0;
    size_t len = str.length();
    if (len == 0) throw std::invalid_argument("Empty string");

    size_t i = 0;
    bool negative = false;

    if (str[0] == '-') {
        negative = true;
        i = 1;
        if (len == 1) throw std::invalid_argument("Invalid number");
    }

    for (; i < len; i++) {
        if (!isdigit(str[i])) {
            throw std::invalid_argument("Invalid character in integer string");
        }
        result = result * 10 + (str[i] - '0');
    }

    return negative ? -result : result;
}

double toDouble(const String& str) {
    double result = 0.0;
    double factor = 1.0;
    bool isFractionalPart = false;

    size_t len = str.length();
    if (len == 0) throw std::invalid_argument("Empty string");

    size_t i = 0;
    bool negative = false;

    if (str[0] == '-') {
        negative = true;
        i = 1;
        if (len == 1) throw std::invalid_argument("Invalid number");
    }

    int dotCount = 0;

    for (; i < len; i++) {
        char ch = str[i];

        if (ch == '.') {
            dotCount++;
            if (dotCount > 1) {
                throw std::invalid_argument("Multiple decimal points");
            }
            isFractionalPart = true;
            continue;
        }

        if (!isdigit(ch)) {
            throw std::invalid_argument("Invalid character in double string");
        }

        if (isFractionalPart) {
            factor /= 10.0;
            result += (ch - '0') * factor;
        }
        else {
            result = result * 10.0 + (ch - '0');
        }
    }

    return negative ? -result : result;
}
