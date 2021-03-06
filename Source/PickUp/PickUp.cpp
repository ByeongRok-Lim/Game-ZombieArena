#include "PickUp.h"
#include "../Utils/TextureHolder.h"
#include "../Utils/Utils.h"
#include <iostream>

PickUp::PickUp(PickUpTypes type)
	: type(type)
{
	std::string textureID;
	switch (this->type)
	{
	case PickUpTypes::Ammo:
		textureID = "graphics/ammo_pickup.png";
		value = AMMO_START_VKLUE;
		break;
	case PickUpTypes::Health:
		textureID = "graphics/health_pickup.png";
		value = HEALTH_START_VALUE;
		break;
	}

	sprite.setTexture(TextureHolder::GetTexture(textureID));
	Utils::SetOrigin(sprite, Pivots::CC);

	Spawn(false);
}

void PickUp::Update(float dt)
{
	timer -= dt;
	if (timer < 0)
	{
		Spawn(!spawned);
	}
}

void PickUp::Spawn(bool spawn)
{
	spawned = spawn;
	if (spawned)
	{
		timer = START_SECONDS_FOR_LIVE;

		int x = Utils::RandomRange(arena.left, arena.left + arena.width);
		int y = Utils::RandomRange(arena.top, arena.top + arena.height);


		sprite.setPosition(Vector2f(x, y));

	}
	else
	{
		timer = START_WAIT_TIME;
	}

}

int PickUp::GotIt()
{
	switch (type)
	{
	case PickUpTypes::Ammo:
		std::cout << "Ammo" << std::endl;
		break;
	case PickUpTypes::Health:
		std::cout << "Health" << std::endl;
		break;
	default:
		break;
	}
	return 0;

}

void PickUp::SetArena(IntRect rect)
{
	arena = rect;
}

bool PickUp::IsSpawned()
{
	return spawned;
}

Sprite PickUp::GetSprite()
{
	return sprite;
}

FloatRect PickUp::GetGlobalBounds()
{
	return sprite.getGlobalBounds();
}

PickUpTypes PickUp::GetType()
{
	return type;
}
