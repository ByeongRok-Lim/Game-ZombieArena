#include "Bullet.h"
#include "../Utils/Utils.h"
#include "../Player/Zombie.h"

Bullet::Bullet()
	: speed(DEFAULT_SPEED), isActive(false)
{
	shape.setSize(Vector2f(50, 10));
	shape.setFillColor(Color::Red);
	Utils::SetOrigin(shape, Pivots::CC);
	
}

void Bullet::SetActive(bool active)
{
	isActive = active;
}


bool Bullet::IsActive()
{
	return isActive;
}

void Bullet::Shoot(Vector2f pos, Vector2f dir)
{
	SetActive(true);

	distance = 0.f;
	position = pos;
	shape.setPosition(position);
	direction = Utils::Normalize(dir);		//Á¤±ÔÈ­ Normalize

	float dgree = Utils::GetAngle(position, position + direction);
	shape.setRotation(dgree);
}

void Bullet::Stop()
{
	SetActive(false);
}

void Bullet::Update(float dt)
{
	position += direction * speed * dt;
	shape.setPosition(position);

	distance += speed * dt;
	if (distance > DEFAULT_DISTANCE)
	{
		Stop();
	}
}

bool Bullet::UpdateCollision(const std::vector<Zombie*>& zombies)
{
	FloatRect bounds = shape.getGlobalBounds();
	for (auto zombie : zombies)
	{
		if (zombie->IsAlive())
		{
			if (bounds.intersects(zombie->GetGlobalBound()))
			{
				zombie->OnHitted();
				Stop();

				return true;
			}
		}
	}

	return false;
}

RectangleShape Bullet::GetShape()
{
	return shape;
}