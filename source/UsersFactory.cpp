#include "UsersFactory.h"

Users* UserFactory::create(Role type)
{
    switch (type)
    {
    case Role::ADMIN:
        return new Admin();

    case Role::PLAYER:
        return new Player();

    default:
        return nullptr;
    }
}