#include "Zombie.h"
#include "../Utils/TextureHolder.h"
#include "../Utils/Utils.h"
#include "../Utils/InputMgr.h"
std::vector<ZombieInfo> Zombie::zombieInfo;
bool Zombie::isiInitInfo = false;
Zombie::Zombie()
{
	if (!isiInitInfo)
	{
		zombieInfo.resize((int)ZombieTypes::COUNT);
		{
			auto& info = zombieInfo[(int)ZombieTypes::BLOATER];
			info.type = ZombieTypes::BLOATER;
			info.textureFileName = "graphics/bloater.png";
			info.speed = 40.f;
			info.health = 5;
		}
		{
			auto& info = zombieInfo[(int)ZombieTypes::CHASER];
			info.type = ZombieTypes::CHASER;
			info.textureFileName = "graphics/chaser.png";
			info.speed = 70.f;
			info.health = 1;
		}
		
		{
			auto& info = zombieInfo[(int)ZombieTypes::CRAWLER];
			info.type = ZombieTypes::CRAWLER;
			info.textureFileName = "graphics/crawler.png";
			info.speed = 20.f;
			info.health = 3;
		}
		isiInitInfo = true;
	}
}

bool Zombie::OnHitted()
{
	return false;
}

bool Zombie::IsAlive()
{
	return alive;
}

void Zombie::Spawn(float x, float y, ZombieTypes type)
{
	auto& info = zombieInfo[(int)type];
	sprite.setTexture(TextureHolder::GetTexture(info.textureFileName));
	speed = info.speed;
	health = info.health;

	position.x = x;
	position.y = y;

	Utils::SetOrigin(sprite, Pivots::CC);
	sprite.setPosition(position);
}

void Zombie::Update(float dt, Vector2f playerPosition)
{
	//����................�Ф�
	//�÷��̾������ǿ��� �������������� ���ش�
	Vector2f zombieDir;
	float x = playerPosition.x - position.x;
	zombieDir.x = x;
	float y = playerPosition.y - position.y;
	zombieDir.y = y;
	Vector2f dir(x, y);

	//����ȭ
	Utils::Normalize(dir);
	//�̵�
	position += dir * speed * dt;
	sprite.setPosition(position);
	//ȸ��
	float radian = atan2(dir.y, dir.x);
	float degree = radian * 180.f / 3.141592f;
	sprite.setRotation(degree);
	//�̵����� ������ ���ǵ�, ��ŸŸ���� ������
	//�̵��ϰ� �÷��̾ �ٶ󺸰� ȸ��
}

FloatRect Zombie::GetGlobalBound()
{
	return sprite.getGlobalBounds();
}

Sprite Zombie::GetSprite()
{
	return sprite;
}
