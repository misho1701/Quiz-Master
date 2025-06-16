#pragma once
#include <iostream>
#include <fstream>
#include "Utils.h"
#include "MyString.h"
#include "Vector.hpp"
#include "Users.h"
#include "UsersFactory.h"

class UserContainer
{
public:
	UserContainer();
	UserContainer(const UserContainer& other);
	UserContainer& operator=(const UserContainer& other);
	~UserContainer();

	Users* getUserPointer(const String& username);
	void addUser(const Users& newUser);
	bool doesUsernameExist(const String& username) const;
	void banUser(const String& username);
	void addDefaultAdministrators();
	void findUserByUsername(const String& username, Users*& result) const;
	bool removeAt(size_t index);
	Users* operator[](unsigned index) const;

	void witeToTextFile(std::ofstream& ofs) const;
	void readFromTextFile(std::ifstream& ifs);

	unsigned getSize() const;

private:
	void copyFrom(const UserContainer& other);
	void free();

	void resize(int newCapacity);
	static unsigned calculateCapacity(unsigned size, unsigned minCapacity);
	static constexpr unsigned MIN_CAPACITY = 16;
	static constexpr unsigned RESIZE_COEFF = 2;

	

	Users** arr;
	unsigned size;
	unsigned capacity;
};
