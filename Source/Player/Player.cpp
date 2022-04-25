#include "Player.h"
#include "../Utils/Utils.h"
#include "../Utils/InputMgr.h"
#include <cmath>

Player::Player()
	:speed(START_SPEED), health(START_HEALTH), maxHealth(START_HEALTH), immuneMs(START_IMMUNE_MS), resolustion(), tileSize(0.f), aspeed(100)
{
	texture.loadFromFile("graphics/player.png");
	sprite.setTexture(texture);

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
	direction.x = InputMgr::GetAxis(Axis::Horizontal);
	direction.y = InputMgr::GetAxis(Axis::Vertical);

	float length = sqrt(direction.x * direction.x + direction.y * direction.y);

	if (length != 0)
	{
		direction /= length;
	}
	//���ӵ�
	speed += aspeed * dt;
	//�̵�
	position += direction * speed * dt;


	//ȸ�� resolution = �����ػ󵵸� int������ �����߾���.
	Vector2i mousePos = InputMgr::GetMousePosition();

	Vector2i mouseDir;

	//mouseDir.x = mousePos.x - resolustion.x * 0.5f;
	//mouseDir.y = mousePos.y - resolustion.y * 0.5f;
	mouseDir.x = mousePos.x - position.x;
	mouseDir.y = mousePos.y - position.y;


	sprite.setPosition(position);

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
