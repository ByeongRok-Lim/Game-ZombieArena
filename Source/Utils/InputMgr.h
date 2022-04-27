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

	float sensi;	//크면 빨리도달 작으면 늦게 도달
	float limit;
	float value; //-1.0 ~ 1.1
};

class InputMgr
{
private:
	static map<Axis, AxisInfo> mapAxis;

	static list<Keyboard::Key> downKeys;
	static list<Keyboard::Key> ingKeys;
	static list<Keyboard::Key> upKeys;

	static list<Mouse::Button> buttonDown;
	static list<Mouse::Button> ingbutton;
	static list<Mouse::Button> buttonUp;
	static bool setPress;

	static Vector2i mousePosition;
	static Vector2f mousePositionWorld;

public:
	static void Init();
	
	static void ProcessInput(const Event& event);
	static void ClearInput();

	static float GetAxis(Axis axis);			//-1.0~ 1.0

	static int GetAxisRaw(list<Keyboard::Key> positive, list<Keyboard::Key> negative);
	static void Update(float dt, RenderWindow& window, View& worldView);
	static int GetAxisRaw(Axis axis);				//-1, 0, 1

	static bool GetKeyDown(Keyboard::Key key);			//눌린 순간
	static bool GetKey(Keyboard::Key key);				//꾹 눌렀을때?
	static bool GetKeyUp(Keyboard::Key key);			//떨어지는 순간

	static Vector2i GetMousePosition();
	static Vector2f GetMouseWorldPosition();
	
	static bool GetMouseButtonDown(Mouse::Button button);
	static bool GetMouseButton(Mouse::Button button);
	static bool GetMouseButtonUp(Mouse::Button button);
};

//InputMgr::GetMouseButtonDown, GetMouseButton, GetMouseButtonUp(Mouse::Button) 추가하기.!