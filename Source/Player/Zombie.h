#pragma once
#include <SFML/Graphics.hpp>
#include <string>
using namespace sf;

enum class ZombieTypes
{
	BLOATER,
	CHASER,
	CRAWLER,
	COUNT,
};

//�������� ������ ��� �ִ� ���� ����..
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

	float speed;	//�⺻�ӵ�
	int health;	//ü��

	bool alive; //��Ҵ��� �׾�����
	
	static std::vector<ZombieInfo> zombieInfo;
	static bool isiInitInfo;
public:
	Zombie();
	bool OnHitted();
	bool IsAlive();

	void Spawn(float x, float y, ZombieTypes type); //�ʱ�ȭ�Լ�
	void Update(float dt, Vector2f playerPosition);
	FloatRect GetGlobalBound();
	Sprite GetSprite();

	
};

