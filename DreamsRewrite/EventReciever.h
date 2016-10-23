#pragma once
#include <irrlicht.h>


class EventReceiver : public irr::IEventReceiver
{
public:
	// This is the one method that we have to implement
	virtual bool OnEvent(const irr::SEvent& event)
	{
		// Remember whether each key is down or up
		if (event.EventType == irr::EET_KEY_INPUT_EVENT)
			KeyIsDown[event.KeyInput.Key] = event.KeyInput.PressedDown;
				
		return false;
	}

	// This is used to check whether a key is being held down
	virtual bool IsKeyDown(irr::EKEY_CODE keyCode) const
	{
		return KeyIsDown[keyCode];
	}

	void MyEventReceiver()
	{
		for (irr::u32 i = 0; i< irr::KEY_KEY_CODES_COUNT; ++i)
			KeyIsDown[i] = false;
	}

	void forceKeyUp(irr::EKEY_CODE keyCode) {
		KeyIsDown[keyCode] = false;
	}

	int numKeys() {
		return irr::KEY_KEY_CODES_COUNT;
	}

private:
	// We use this array to store the current state of each key
	bool KeyIsDown[irr::KEY_KEY_CODES_COUNT];
};