#include "InputMgr.h"
#include <algorithm>
#include <cmath>

map<Axis, AxisInfo> InputMgr::mapAxis;
list<Keyboard::Key> InputMgr::downKeys;
list<Keyboard::Key> InputMgr::ingKeys;
list<Keyboard::Key> InputMgr::upKeys;
list<Mouse::Button> InputMgr::buttonDown;
list<Mouse::Button> InputMgr::ingbutton;
list<Mouse::Button> InputMgr::buttonUp;
bool InputMgr::setPress = false;

Vector2i InputMgr::mousePosition;
Vector2f InputMgr::mousePositionWorld;

void InputMgr::Init()
{
	mapAxis.clear();

	AxisInfo info;
	// Hrizontal
	info.axis = Axis::Horizontal;
	info.sensi = 2.0f;
	info.value = 0.f;
	info.limit = 0.05f;
	info.positiveKeys.clear();
	info.positiveKeys.push_back(Keyboard::D);
	info.positiveKeys.push_back(Keyboard::Right);
	
	info.negativeKeys.clear();
	info.negativeKeys.push_back(Keyboard::A);
	info.negativeKeys.push_back(Keyboard::Left);
	mapAxis[info.axis] = info;

	//vertical
	info.axis = Axis::Vertical; 
	info.sensi = 2.0f;
	info.value = 0.f;
	info.limit = 0.05f;
	info.positiveKeys.clear();
	info.positiveKeys.push_back(Keyboard::S);
	info.positiveKeys.push_back(Keyboard::Down);

	info.negativeKeys.clear();
	info.negativeKeys.push_back(Keyboard::W);
	info.negativeKeys.push_back(Keyboard::Up);
	mapAxis[info.axis] = info;

	//info.positiveKeys = list<Keyboard::Key>(Keyboard::S, Keyboard::Down);
	//info.negativeKeys = list<Keyboard::Key>(Keyboard::W, Keyboard::Up);

	mapAxis[info.axis] = info;
}
void InputMgr::ClearInput()
{
	downKeys.clear();
	upKeys.clear();
	buttonDown.clear();
	
}
float InputMgr::GetAxis(Axis axis)
{
	if (mapAxis.find(axis) != mapAxis.end())
	{
		return mapAxis[axis].value;
	}
	return 0.0f;
}


void InputMgr::ProcessInput(const Event& event)
{
	
	switch (event.type)
	{
	case Event::KeyPressed:
		if (!GetKey(event.key.code))
		{
			downKeys.push_back(event.key.code);	//동작이 진행되어야 한다.
			ingKeys.push_back(event.key.code);	//동작이 진행되어야 한다.
		}
		break;
	case Event::KeyReleased:
			ingKeys.remove(event.key.code);
			upKeys.push_back(event.key.code);	//동작이 멈추어야한다.
		break;
	case Event::MouseButtonPressed:
		if (!GetKey(event.key.code))
		{
			buttonDown.push_back(event.mouseButton.button);	
			ingbutton.push_back(event.mouseButton.button);	
		}
		setPress = true;
		break;
	case Event::MouseButtonReleased:
		ingbutton.remove(event.mouseButton.button);
		buttonUp.push_back(event.mouseButton.button);	//동작이 멈추어야한다.
		setPress = false;
		break;
	default:
		break;
	}

}

int InputMgr::GetAxisRaw(list<Keyboard::Key> positive, list<Keyboard::Key> negative)
{
	int axis = 0;
	bool isPositive = false;
	bool isNegative = false;

	for (auto it = positive.begin(); it != positive.end(); ++it)
	{
		Keyboard::Key key = (*it);
		if (Keyboard::isKeyPressed(key))
		{
			isPositive = true;
			break;
		}
	}
	for (auto it = negative.begin(); it != negative.end(); ++it)
	{
		Keyboard::Key key = (*it);
		if (Keyboard::isKeyPressed(key))
		{
			isNegative = true;
			break;
		}
	}

	if (isPositive && isNegative)
	{
		axis = 0;
	}
	else if (isNegative)
	{
		axis = -1;
	}
	else if (isPositive)
	{
		axis = 1;
	}


	return axis;
}

void InputMgr::Update(float dt, RenderWindow& window, View& worldView)
{
	for (auto it = mapAxis.begin(); it != mapAxis.end(); ++it)
	{	
		AxisInfo& ref = it->second;
		//Axis = 방향
		int axis = GetAxisRaw(ref.axis);
		if (axis == 0)
		{
			axis = ref.value > 0 ? -1 : 1;
			if (abs(ref.value) < ref.limit)
			{
				axis = 0;
				ref.value = 0;
			}
		}
				
		ref.value += axis * ref.sensi * dt;
		
		if (ref.value > 1.f)
		{
			ref.value = 1.f;
		}
		if (ref.value < -1.f)
		{
			ref.value = -1.f;
		}
	
	}
	mousePosition = Mouse::getPosition();
	mousePositionWorld = window.mapPixelToCoords(mousePosition, worldView);
}


int InputMgr::GetAxisRaw(Axis axis)
{
	auto pair = mapAxis.find(axis);
	if (pair != mapAxis.end())
	{
		return GetAxisRaw(pair->second.positiveKeys, pair->second.negativeKeys);
	}
	
	return 0;
}



//list<Keyboard::Key> downKeys;
//list<Keyboard::Key> ingKeys;
//list<Keyboard::Key> upKeys;
bool InputMgr::GetKeyDown(Keyboard::Key key)		//iterator
{
	auto it = find(downKeys.begin(), downKeys.end(), key);		//넘겨주면
	return it != downKeys.end();
}

bool InputMgr::GetKey(Keyboard::Key key)
{
	auto it = find(ingKeys.begin(), ingKeys.end(), key);		
	return it != ingKeys.end();
}

bool InputMgr::GetKeyUp(Keyboard::Key key)
{
	auto it = find(upKeys.begin(), upKeys.end(), key);		
	return it != upKeys.end();
	
}


Vector2i InputMgr::GetMousePosition()
{
	return mousePosition;
}

Vector2f InputMgr::GetMouseWorldPosition()
{
	return mousePositionWorld;
}

bool InputMgr::GetMouseButtonDown(Mouse::Button button)
{
	auto it = find(buttonDown.begin(), buttonDown.end(), button);
	return it != buttonDown.end();
}

bool InputMgr::GetMouseButton(Mouse::Button button)
{
	auto it = find(ingbutton.begin(), ingbutton.end(), button);
	return it != ingbutton.end();
}

bool InputMgr::GetMouseButtonUp(Mouse::Button button)
{
	auto it = find(buttonUp.begin(), buttonUp.end(), button);
	return it != buttonUp.end();
}
