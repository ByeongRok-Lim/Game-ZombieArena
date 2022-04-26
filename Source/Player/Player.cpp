#include "Player.h"
#include "../Utils/Utils.h"
#include "../Utils/InputMgr.h"
#include <cmath>
#include "../Utils/TextureHolder.h"

Player::Player()
	:speed(START_SPEED), health(START_HEALTH), maxHealth(START_HEALTH), immuneMs(START_IMMUNE_MS), resolustion(), tileSize(0.f),
	textureFileName("graphics/player.png"), tempPos()
{
	
	sprite.setTexture(TextureHolder::GetTexture(textureFileName));

	Utils::SetOrigin(sprite, Pivots::CC);
}

Player::~Player()
{
}

void Player::Spawn(IntRect arena, Vector2i res, int tileSize)
{
	this->arena = arena;
	resolustion = res;
	this->tileSize = tileSize;

	position.x = arena.width * 0.5f;
	position.y = arena.height * 0.5f;
}

bool Player::OnHitted(Time timeHit)	//�ǰ� ����
{
	if (timeHit.asMicroseconds() - timeHit.asMicroseconds() > 200)
	{
		lastHit = timeHit;
		health -= 10;
		return true;

	}
	return false;
}

Time Player::GetLastTime() const
{
	return lastHit;
}

FloatRect Player::GetGobalBound() const
{
	return sprite.getGlobalBounds();
}

Vector2f Player::GetPosition() const
{
	return position;
}

float Player::GetRotation() const
{
	return sprite.getRotation();
}

Sprite Player::GetSprite() const
{
	return sprite;
}

int Player::Gethealth() const
{
	return health;
}

void Player::SetDirection(Vector2f dir)
{
	//���
}

void Player::update(float dt)
{
	//�̵��ϴ°� �ǳ��Ұ� �ڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡ�
	//����� �Է�
	float h = InputMgr::GetAxis(Axis::Horizontal); //���� ��
	float v = InputMgr::GetAxis(Axis::Vertical);	//���� ��
	Vector2f dir(h, v);

	float length = sqrt(dir.x * dir.x + dir.y * dir.y);
	if (length > 1)
	{
		dir /= length;
	}




	//�̵�
	
	position += dir * speed * dt;
	

	//�浹ó��
	if (position.x < arena.left + 50 || position.x > arena.width - 50)
	{
		position.x -= 2;
	}
	if (position.x < arena.left + 50)
	{
		position.x += 10;
	}
	if (position.y < arena.top + 50 || position.y > arena.height - 50)
	{
		position.y -= 2;
	}
	if (position.y < arena.top + 50)
	{
		position.y += 10;
	}
	
	sprite.setPosition(position);
	//ȸ�� resolution = �����ػ󵵸� int������ �����߾���.
	Vector2i mousePos = InputMgr::GetMousePosition();
	Vector2i mouseDir;

	mouseDir.x = mousePos.x - resolustion.x * 0.5f;
	mouseDir.y = mousePos.y - resolustion.y * 0.5f;
	//mouseDir.x = mousePos.x - position.x;
	//mouseDir.y = mousePos.y - position.y;

	float radian = atan2(mouseDir.y, mouseDir.x);
	float degree = radian * 180 / 3.141592f;

	sprite.setRotation(degree);
}

void Player::GetHealthItem(int amount)
{
	health += amount;
	if (health > maxHealth)
	{
		health = maxHealth;
	}
	if (health < 0)
	{
		health = 0;
	}
}

void Player::UpgradeSpeed()	//���ǵ� ��������.
{
	speed += START_SPEED * 0.2f;
}

void Player::UpgradeMaxHealth()	//MAX ü�� ��������.
{
	maxHealth += START_HEALTH * 0.2f;
}
