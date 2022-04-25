#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

//
enum class Pivots
{
	//�ǽ����� ������ �߰��ϱ� ��
	
	LT, CT, RT,
	LC, CC, RC,
	LB, CB, RB,

};

class Utils
{
	//Player�� ���� �ٸ����� �� ����ϱ� ���� �Լ��� ���� Ŭ���� Utils.
public:
	static void SetOrigin(Text& text, Pivots preset);
	static void SetOrigin(Sprite& sprite, Pivots preset);
	static void SetOrigin(Shape& shape, Pivots preset);
	static void SetOrigin(Transformable& tr, FloatRect bounds,Pivots preset);

};

