#include "InputMgr.h"
#include <algorithm>

map<Axis, AxisInfo> InputMgr::mapAxis;
list<Keyboard::Key> InputMgr::downKeys;
list<Keyboard::Key> InputMgr::ingKeys;
list<Keyboard::Key> InputMgr::upKeys;


void InputMgr::Init()
{
	mapAxis.clear();

	AxisInfo info;
	// Hrizontal
	info.axis = Axis::Horizontal;
	info.positiveKeys.clear();
	info.positiveKeys.push_back(Keyboard::D);
	info.positiveKeys.push_back(Keyboard::Right);
	
	info.negativeKeys.clear();
	info.negativeKeys.push_back(Keyboard::A);
	info.negativeKeys.push_back(Keyboard::Left);
	mapAxis[info.axis] = info;

	//vertical
	info.axis = Axis::Vertical; 
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
}
//list<Keyboard::Key> downKeys;
//list<Keyboard::Key> ingKeys;
//list<Keyboard::Key> upKeys;

//static bool GetKeyDown(Keyboard::Key key);
//static bool GetKey(Keyboard::Key key);
//static bool GetKeyUp(Keyboard::Key key);

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
	default:
		break;
	}
}

int InputMgr::GetAxis(list<Keyboard::Key> positive, list<Keyboard::Key> negative)
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

int InputMgr::GetAxis(Axis axis)
{
	auto pair = mapAxis.find(axis);
	if (pair != mapAxis.end())
	{
		return GetAxis(pair->second.positiveKeys, pair->second.negativeKeys);
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
	return Mouse::getPosition();
}
