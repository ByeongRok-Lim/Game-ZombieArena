#pragma once
#include <SFML/Graphics.hpp>
#include <string>
using namespace sf;

class Player;

enum class ZombieTypes
{
	BLOATER,
	CHASER,
	CRAWLER,
	COUNT,
};

//이정보를 누군가 들고 있는 것이 좋다..
struct ZombieInfo
{
	ZombieTypes type;
	std::string textureFileName;
	float speed;
	int health;
};



class Zombie
{
private:
	ZombieTypes zombieTypes;
	Vector2f position;
	Sprite sprite;

	float speed;	//기본속도
	int health;	//체력

	bool alive; //살았는지 죽었는지
	
	static std::vector<ZombieInfo> zombieInfo;
	static bool isiInitInfo;
public:
	Zombie();
	bool OnHitted();
	bool IsAlive();

	void Spawn(float x, float y, ZombieTypes type); //초기화함수
	void Update(float dt, Vector2f playerPosition);

	bool UpdateCollision(Time time, Player& player);

	FloatRect GetGlobalBound();
	Sprite GetSprite();

	
};

