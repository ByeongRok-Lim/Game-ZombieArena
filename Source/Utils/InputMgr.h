#pragma once
#include "SFML/Graphics.hpp"
#include <list>
#include <map>

using namespace sf;
using namespace std;

enum class Axis //축
{
	Horizontal,
	Vertical,
};

struct AxisInfo	
{
	Axis axis;
	list<Keyboard::Key> positiveKeys;
	list<Keyboard::Key> negativeKeys;
};

class InputMgr
{
private:
	static map<Axis, AxisInfo> mapAxis;

	static list<Keyboard::Key> downKeys;
	static list<Keyboard::Key> ingKeys;
	static list<Keyboard::Key> upKeys;


public:
	static void Init();
	
	static void ProcessInput(const Event& event);
	static void ClearInput();

	static int GetAxis(list<Keyboard::Key> positive, list<Keyboard::Key> negative);

	static int GetAxis(Axis axis);

	static bool GetKeyDown(Keyboard::Key key);			//눌린 순간
	static bool GetKey(Keyboard::Key key);				//꾹 눌렀을때?
	static bool GetKeyUp(Keyboard::Key key);			//떨어지는 순간


	static Vector2i GetMousePosition();
};

