#include "../../include/keyboard/keyboard.h"
#include <iostream>

using namespace std;
using namespace NotKeyBoard;

bool KeyBoardControl::initialized = false;
KeyBoardControl* KeyBoardControl::instance = nullptr;

bool NotKeyBoard::KeyBoardControl::OnMessage(ExMessage& msg)
{
	if (msg.message == WM_KEYDOWN)
	{
		if (48 <= msg.vkcode && msg.vkcode <= 57)
		{
			isNumberKeyDown[msg.vkcode - 48] = true;
			isNumberKeyUp[msg.vkcode - 48] = false;
		}
			
		else if (65 <= msg.vkcode && msg.vkcode <= 90)
		{
			isLetterKeyDown[msg.vkcode - 65] = true;
			isLetterKeyUp[msg.vkcode - 48] = false;
		}
	}
	else if (msg.message == WM_KEYUP)
	{
		if (48 <= msg.vkcode && msg.vkcode <= 57)
		{
			isNumberKeyDown[msg.vkcode - 48] = false;
			isNumberKeyUp[msg.vkcode - 48] = true;
		}
			
		else if (65 <= msg.vkcode && msg.vkcode <= 90)
		{
			isLetterKeyDown[msg.vkcode - 65] = false;
			isLetterKeyUp[msg.vkcode - 65] = true;
		}
	}
	else
		return false;

	return true;
}

bool NotKeyBoard::KeyBoardControl::isDown(NotVK vkcode)
{
	if (vkcode >= 65)
	{
		return isLetterKeyDown[vkcode - 65];
	}
	if (vkcode >= 48)
	{
		return isNumberKeyDown[vkcode - 48];
	}
	
	return false;
}

bool NotKeyBoard::KeyBoardControl::isUp(NotVK vkcode)
{
	if (vkcode >= 65)
	{
		return isLetterKeyUp[vkcode - 65];
	}
	if (vkcode >= 48)
	{
		return isNumberKeyUp[vkcode - 48];
	}
	return false;
}

KeyBoardControl* NotKeyBoard::KeyBoardControl::manager()
{
	if (!initialized)
	{
		instance = new KeyBoardControl();
	}
	return instance;
}

void NotKeyBoard::KeyBoardControl::quit()
{
	if (initialized)
		delete instance;
}

NotKeyBoard::KeyBoardControl::KeyBoardControl()
{
	initialized = true;
}

NotKeyBoard::KeyBoardControl::~KeyBoardControl()
{
	initialized = false;
}
