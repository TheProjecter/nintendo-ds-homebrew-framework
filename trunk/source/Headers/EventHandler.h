#ifndef EVENT_HANDLER_H
#define EVENT_HANDLER_H

#include <nds.h>

class EventHandler
{
public:

	EventHandler() {}
	 virtual ~EventHandler() {}

	void Update();

	bool KeyPressed(int key);
	bool KeyHeld(int key);

	bool StylusDown();

	float GetStylusX();
	float GetStylusY();

private:

	float m_stylusX;
	float m_stylusY;
	int m_held;
	int m_pressed;
	touchPosition m_touchPos;
};

#endif