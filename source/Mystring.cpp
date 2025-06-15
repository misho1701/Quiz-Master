#include "MyString.h"
#include "Vector.hpp"
#pragma warning(disable : 4996)


void String::copyFrom(const char* src) {
    len = strlen(src);
    data = new char[len + 1];
    strcpy(data, src);
}

void String::free() {
    delete[] data;
}

String::String() : data(new char[1]), len(0) {
    data[0] = '\0';
}

String::String(const char* s) {
    copyFrom(s);
}

String::String(const String& other) {
    copyFrom(other.data);
}

String& String::operator=(const String& other) {
    if (this != &other) {
        free();
        copyFrom(other.data);
    }
    return *this;
}

String::~String() {
    free();
}

const char* String::c_str() const {
    return data;
}

size_t String::length() const {
    return len;
}

bool String::operator==(const String& other) const {
    return strcmp(data, other.data) == 0;
}

bool String::operator!=(const String& other) const {
    return !(*this == other);
}

String& String::operator+=(const String& other)
{
    if (other.len == 0) {
        return *this;
    }
    char* newData = new char[len + other.len + 1];
    strcpy(newData, data);
    strcat(newData, other.data);
    delete[] data;
    data = newData;
    len += other.len;
    return *this;
}



char& String::operator[](size_t index)
{
    return data[index];
}

const char& String::operator[](size_t index) const
{
    return data[index];
}



String String::toLower() const {
    String result(data);
    for (size_t i = 0; i < result.len; i++)
        result.data[i] = std::tolower(result.data[i]);
    return result;
}

void String::print() const {
    std::cout << data;
}

bool String::is_empty() const
{
    return this->len == 0;
}

int String::find(char ch) const
{
    static const int npos = -1;
    for (int i = 0; i < length(); ++i) {
        if (data[i] == ch) return i;
    }
    return npos;
}

String String::trim() const
{
	size_t start = 0;
	while (start < len && std::isspace(data[start])) {
		start++;
	}

	size_t end = len;
	while (end > start && std::isspace(data[end - 1])) {
		end--;
	}

	if (start >= end) {
		return String(); 
	}
	char* temp = new char[end - start + 1];
	copy(temp, end - start, start);
	String result(temp);
	delete[] temp;

	return result;
}

String String::substr(size_t pos, size_t count) const {
    count = std::min(this->len - pos, count);

    if (pos + count > this->len) {
        throw std::out_of_range("Index out of range");
    }



    char* temp = new char[count + 1];
    copy(temp, count, pos);
    String result(temp);
    delete[] temp;

    return result;
}

String& String::concat(int value) {
    std::stringstream ss;
    ss << value;
    *this += String(ss.str().c_str());
    return *this;
}

String& String::concat(char ch) {
    std::stringstream ss; 
    ss << ch;
    *this += String(ss.str().c_str());
    return *this;
}

String& String::concat(double value) {
    std::stringstream ss;
    ss << value;
    *this += String(ss.str().c_str());
    return *this;
}

String& String::concat(const char* value) 
{
    *this += String(value);
    return *this;
}

String& String::concat(const String& value)
{
    *this += value;
    return *this;
}

void String::readFromFile(std::ifstream& ifs)
{
	std::string temp;
	std::getline(ifs, temp);
	if (temp.empty()) {
		data = new char[1];
		data[0] = '\0';
		len = 0;
	}
	else {
		copyFrom(temp.c_str());
	}

}

void String::writeToFile(std::ofstream& ofs) const
{
	if (ofs.is_open()) {
		ofs << data << '\n';
	}
	else {
		std::cerr << "Error writing String to file.\n";
	}
}

void String::copy(char*& dest, size_t count, size_t pos) const {
    if (pos > this->length()) {
        throw std::out_of_range("Index out of range");
    }

    count = std::min(this->length() - pos, count);


    for (size_t i = 0; i < count; i++) {
        dest[i] = this->data[pos + i];
    }
    dest[count] = '\0';
}

std::istream& operator>>(std::istream& in, String& str) {
    char buffer[1024];
    in >> buffer;
    str = String(buffer);
    return in;
}

std::ostream& operator<<(std::ostream& out, const String& str) {
    out << str.data;
    return out;
}

String operator+(const String& lhs, const String& rhs)
{
    String result(lhs);
    result += rhs;
    return result;
}

