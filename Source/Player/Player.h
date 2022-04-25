#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Player
{
private:
	const float START_SPEED = 200;
	const float START_HEALTH = 100;
	const float START_IMMUNE_MS = 100;

	Vector2f position;

	Sprite sprite;
	Texture texture;

	Vector2i resolustion; //해상도
	//플레이어 회전을 시키기 위해서 마우스 포인터가 어느 포인터에 있는지...
	IntRect arena;//충돌체크, 플레이어는 사각 테두리를 벗어나면 안됨.

	int tileSize;

	Vector2f direction; //어느방향으로 가야하는가... 방향*시간*속도'
	float speed;

	float aspeed;
	
	int health; //현재 hp 게이지 구하기.
	int maxHealth; //현재상태 최대 hP
	float immuneMs;

	Time lastHit; // 누적시간, 좀비한테 맞고나서의 몇초동안s의 무적시간을 주기위해서..
public:
	Player();
	~Player();

	void Spawn(IntRect arena, Vector2i res, int tileSize);
	bool OnHitted(Time lastHit); //피격시

	Time GetLastTime() const;
	FloatRect GetGobalBound() const;
	Vector2f GetPosition() const;
	float GetRotation() const;
	Sprite GetSprite() const;
	int Gethealth() const;

	void SetDirection(Vector2f dir);
	void update(float dt); // 마우스 포지션 들고오기
	void GetHealthItem(int amount);
	void UpgradeSpeed();
	void UpgradeMaxHealth();



};

