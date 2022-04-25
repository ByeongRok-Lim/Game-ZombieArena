#include "Utils.h"
#include "../Player/Player.h"


void Utils::SetOrigin(Text& text, Pivots preset)
{
	SetOrigin(text, text.getLocalBounds(), preset);
}

void Utils::SetOrigin(Sprite& sprite, Pivots preset)
{
	SetOrigin(sprite, sprite.getLocalBounds(), preset);	//getLocalBounds()���õǾ��ִ� ���¿��� �������� �Ѱ��ִ� �Լ�.
}

void Utils::SetOrigin(Shape& shape, Pivots preset)
{
	SetOrigin(shape, shape.getLocalBounds(), preset);
}


//ȣ���ϰ� �� �ڵ�, ���
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
