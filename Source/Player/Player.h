#pragma once
#include <SFML/Graphics.hpp>
#include "../Bullet/Bullet.h"
#include <list>
using namespace sf;

class PickUp;

class Player
{
private:

	const float START_SPEED = 1000;
	const float START_ACCEL = 1500;
	const float START_HEALTH = 100;
	const float START_IMMUNE_MS = 200;

	Vector2f position;
	std::string textureFileName;
	Sprite sprite;
	Texture texture;

	Vector2f tempPos;

	Vector2i resolustion; //해상도
	//플레이어 회전을 시키기 위해서 마우스 포인터가 어느 포인터에 있는지...
	IntRect arena;//충돌체크, 플레이어는 사각 테두리를 벗어나면 안됨.

	int tileSize;

	Vector2f direction; //어느방향으로 가야하는가... 방향*시간*속도'
	Vector2f lastDir;
	float speed;

	
	int health; //현재 hp 게이지 구하기.
	int maxHealth; //현재상태 최대 hP
	float immuneMs;
	bool immune;

	Time lastHit; // 누적시간, 좀비한테 맞고나서의 몇초동안s의 무적시간을 주기위해서..

	const float BULLET_CACHE_SIZE = 200;
	std::list<Bullet*> unuseBullets;
	std::list<Bullet*> useBullets;
	float distanceToMuzzle;

public:
	Player();
	~Player();

	void Shoot(Vector2f dir);

	void Spawn(IntRect arena, Vector2i res, int tileSize);
	bool OnHitted(Time lastHit); //피격시

	Time GetLastTime() const;
	FloatRect GetGlobalBound() const;
	Vector2f GetPosition() const;
	float GetRotation() const;
	Sprite GetSprite() const;
	int Gethealth() const;

	void SetDirection(Vector2f dir);
	void update(float dt); // 마우스 포지션 들고오기

	bool UpdateCollition(const std::list<PickUp*>& items);
	bool UpdateCollision(const std::vector<Zombie*>& zombies);

	void Draw(RenderWindow& window);

	void GetHealthItem(int amount);
	void UpgradeSpeed();
	void UpgradeMaxHealth();



};

