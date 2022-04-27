#include "Utils.h"
#include "../Player/Player.h"


std::random_device Utils::rd;
std::mt19937 Utils::gen(rd());


void Utils::SetOrigin(Text& text, Pivots preset)
{
	SetOrigin(text, text.getLocalBounds(), preset);
}

void Utils::SetOrigin(Sprite& sprite, Pivots preset)
{
	SetOrigin(sprite, sprite.getLocalBounds(), preset);	//getLocalBounds()세팅되어있는 상태에서 다음으로 넘겨주는 함수.
}

void Utils::SetOrigin(Shape& shape, Pivots preset)
{
	SetOrigin(shape, shape.getLocalBounds(), preset);
}


//호출하게 할 코드, 계산
void Utils::SetOrigin(Transformable& tr, FloatRect bounds, Pivots preset)
{
	float wc = bounds.width * 0.5f;
	float hc = bounds.height * 0.5f;

	float w = bounds.width;
	float h = bounds.height;

	switch (preset)
	{
	case Pivots::LT:
		tr.setOrigin(0.0f, 0.0f);
		break;
	case Pivots::CT:
		tr.setOrigin(wc, 0.0f);
		break;
	case Pivots::RT:
		tr.setOrigin(w, 0.0f);
		break;

	case Pivots::LC:
		tr.setOrigin(0.f, hc);
		break;
	case Pivots::CC:
		tr.setOrigin(wc, hc);
		break;
	case Pivots::RC:
		tr.setOrigin(w, hc);
		break;
	case Pivots::LB:
		tr.setOrigin(0.0f, h);
		break;
	case Pivots::CB:
		tr.setOrigin(wc, h);
		break;
	case Pivots::RB:
		tr.setOrigin(w, h);
		break;

	}
}

int Utils::RandomRange(int min, int max)
{
	int range = max - min;
	return min + gen() % range;
}

float Utils::GetLength(const Vector2f& vector)
{
	return sqrt(vector.x * vector.x + vector.y * vector.y);
}

Vector2f Utils::Normalize(Vector2f & vector)
{

	float length = GetLength(vector);
	if (length > 0)
	{
		vector /= length;
	}
	return vector;

	
}

float Utils::GetAngle(const Vector2f& from, const Vector2f& to)
{
	Vector2f dir = to - from;
	float radian = atan2(dir.y, dir.x);
	float degree = radian * 180 / 3.141592f;
	return degree;
}


