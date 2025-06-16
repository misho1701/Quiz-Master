#pragma once
#include <iostream>
#include "Utils.h"
#include "Users.h"
#include "Admin.h"
#include "Player.h"


class UserFactory
{
public:
	static Users* create(Role type);
};

