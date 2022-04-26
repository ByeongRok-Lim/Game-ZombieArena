#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Player
{
private:

	const float START_SPEED = 1000;
	const float START_ACCEL = 5000;
	const float START_HEALTH = 100;
	const float START_IMMUNE_MS = 200;

	Vector2f position;
	std::string textureFileName;
	Sprite sprite;
	Texture texture;

	Vector2f tempPos;

	Vector2i resolustion; //�ػ�
	//�÷��̾� ȸ���� ��Ű�� ���ؼ� ���콺 �����Ͱ� ��� �����Ϳ� �ִ���...
	IntRect arena;//�浹üũ, �÷��̾�� �簢 �׵θ��� ����� �ȵ�.

	int tileSize;

	Vector2f direction; //����������� �����ϴ°�... ����*�ð�*�ӵ�'
	Vector2f lastDir;
	float speed;

	
	int health; //���� hp ������ ���ϱ�.
	int maxHealth; //������� �ִ� hP
	float immuneMs;

	Time lastHit; // �����ð�, �������� �°����� ���ʵ���s�� �����ð��� �ֱ����ؼ�..
public:
	Player();
	~Player();

	void Spawn(IntRect arena, Vector2i res, int tileSize);
	bool OnHitted(Time lastHit); //�ǰݽ�

	Time GetLastTime() const;
	FloatRect GetGobalBound() const;
	Vector2f GetPosition() const;
	float GetRotation() const;
	Sprite GetSprite() const;
	int Gethealth() const;

	void SetDirection(Vector2f dir);
	void update(float dt); // ���콺 ������ ������
	void GetHealthItem(int amount);
	void UpgradeSpeed();
	void UpgradeMaxHealth();



};

