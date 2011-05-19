#include "EventHandler.h"

bool EventHandler::KeyPressed(int key)
{
	if(m_pressed & key)
	{
		return true;
	}

	return false;
}

bool EventHandler::KeyHeld(int key)
{
	if(m_held & key)
	{
		return true;
	}

	return false;
}

bool EventHandler::StylusDown()
{
	if(m_held & KEY_TOUCH)
	{
		return true;
	}

	return false;
}

float EventHandler::GetStylusX()
{
	return m_touchPos.px;
}

float EventHandler::GetStylusY()
{
	return m_touchPos.py;
}

void EventHandler::Update()
{
	scanKeys();

	touchRead(&m_touchPos);

	m_held = keysHeld();
	m_pressed = keysDown();
}

