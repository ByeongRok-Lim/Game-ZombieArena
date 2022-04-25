#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

//
enum class Pivots
{
	//실습으로 프리셋 추가하기 ★
	
	LT, CT, RT,
	LC, CC, RC,
	LB, CB, RB,

};

class Utils
{
	//Player든 어디든 다른데서 다 사용하기 위한 함수를 적을 클래스 Utils.
public:
	static void SetOrigin(Text& text, Pivots preset);
	static void SetOrigin(Sprite& sprite, Pivots preset);
	static void SetOrigin(Shape& shape, Pivots preset);
	static void SetOrigin(Transformable& tr, FloatRect bounds,Pivots preset);

};

