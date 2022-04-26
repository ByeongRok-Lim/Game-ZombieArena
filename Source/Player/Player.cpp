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

bool Player::OnHitted(Time timeHit)	//피격 판정
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
	//대기
}

void Player::update(float dt)
{
	//이동하는거 맨날할것 ★★★★★★★★★★★★★★★★★
	//사용자 입력
	float h = InputMgr::GetAxis(Axis::Horizontal); //빙판 좌
	float v = InputMgr::GetAxis(Axis::Vertical);	//빙판 우
	Vector2f dir(h, v);

	float length = sqrt(dir.x * dir.x + dir.y * dir.y);
	if (length > 1)
	{
		dir /= length;
	}




	//이동
	
	position += dir * speed * dt;
	

	//충돌처리
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
	//회전 resolution = 현재해상도를 int단위로 저장했었다.
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

void Player::UpgradeSpeed()	//스피드 빨라지게.
{
	speed += START_SPEED * 0.2f;
}

void Player::UpgradeMaxHealth()	//MAX 체력 높아지게.
{
	maxHealth += START_HEALTH * 0.2f;
}
