#include "UsersContainer.h"

UserContainer::UserContainer()
{
	size = 0;
	capacity = MIN_CAPACITY;
	arr = new Users * [capacity];
//addDefaultAdministrators();
}

UserContainer::UserContainer(const UserContainer& other)
{
	copyFrom(other);
}
UserContainer& UserContainer::operator=(const UserContainer& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}
UserContainer::~UserContainer()
{
	free();
}

void UserContainer::copyFrom(const UserContainer& other)
{
	size = other.size;
	capacity = other.capacity;
	arr = new Users * [capacity];
	for (int i = 0; i < size; i++)
	{
		arr[i] = other.arr[i]->clone();
	}
}
void UserContainer::free()
{
	for (int i = 0; i < this->size; i++)
	{
		delete arr[i];
	}

	delete[] arr;
}

void UserContainer::resize(int newCapacity)
{
	capacity = newCapacity;
	Users** temp = new Users * [capacity];
	for (int i = 0; i < size; i++)
	{
		temp[i] = arr[i];
	}
	delete[] arr;
	arr = temp;
}

unsigned UserContainer::calculateCapacity(unsigned size, unsigned minCapacity)
{
	unsigned capacity = minCapacity;
	while (capacity < size)
	{
		capacity *= RESIZE_COEFF;
	}
	return capacity;
}

Users* UserContainer::getUserPointer(const String& username)
{
	Users* result = nullptr;
	for (int i = 0; i < size; i++)
	{
		if (arr[i] == nullptr)
		{
			continue;
		}
		if (username == arr[i]->getUsername())
		{
			result = arr[i];
			break;
		}
	}
	return result;
}
void UserContainer::addUser(const Users& newUser)
{
	if (size == capacity)
	{
		resize(capacity * 2);
	}
	arr[size++] = newUser.clone();
}
void UserContainer::addDefaultAdministrators()
{
	Users* admin1 = new Admin("Admin", "One", "admin1", "0000");
	Users* admin2 = new Admin("Admin", "Two", "admin2", "0000");
	Users* admin3 = new Admin("Admin", "Three", "admin3", "0000");
	Users* admin4 = new Admin("Admin", "Four", "admin4", "0000");
	Users* admin5 = new Admin("Admin", "Five", "admin5", "0000");

	addUser(*admin1);
	addUser(*admin2);
	addUser(*admin3);
	addUser(*admin4);
	addUser(*admin5);
}
void UserContainer::findUserByUsername(const String& username, Users*& result) const
{
	result = nullptr;
	for (int i = 0; i < size; i++)
	{
		if (arr[i] == nullptr)
		{
			continue;
		}
		if (arr[i]->getUsername() == username)
		{
			result = arr[i];
			break;
		}
	}
}
bool UserContainer::removeAt(size_t index)
{
	if (index >= size)
	{
		return false; 
	}
	delete arr[index];
	arr[index] = nullptr; 
	for (size_t i = index; i < size - 1; i++)
	{
		arr[i] = arr[i + 1];
	}
	arr[size - 1] = nullptr; 
	size--;
	return true;
}
bool UserContainer::doesUsernameExist(const String& username) const
{
	for (int i = 0; i < size; i++)
	{
		if (arr[i] == nullptr)
		{
			continue;
		}
		if (arr[i]->getUsername() == username)
		{
			return true;
		}
	}
	return false;
}
void UserContainer::banUser(const String& username)
{
	for (int i = 0; i < size; i++)
	{
		if (arr[i]->getUsername() == username)
		{
			arr[i]->ban();
			break;
		}
	}
}

Users* UserContainer::operator[](unsigned index) const
{
	if (index >= size)
	{
		throw std::out_of_range("Index out of range");
	}
	return arr[index];
}

void UserContainer::witeToTextFile(std::ofstream& ofs) const
{
	ofs << size << std::endl;
	for (int i = 0; i < size; i++)
	{
		if (arr[i] != nullptr)
		{
			arr[i]->writeToFile(ofs);
		}
		else
		{
			//ofs << "null" << std::endl;
			return;
		}
	}
}


void UserContainer::readFromTextFile(std::ifstream& ifs)
{
	free();
	this->arr = new Users * [capacity];
	while(true)
	{
		String type;
		ifs >> type;
		Users* user = nullptr;
		if (type == "Admin")
		{
			user = UserFactory::create(Role::PLAYER);
		}
		else if (type == "Player")
		{
			user = UserFactory::create(Role::PLAYER);
		}
		else
		{
			return;
		}
		user->readFromFile(ifs);
		this->addUser(*user);
		
	}
}



unsigned UserContainer::getSize() const
{
	return size;
}