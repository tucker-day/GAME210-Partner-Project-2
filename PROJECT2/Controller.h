#pragma once

#include "windows.h"
#include "xinput.h"

class Controller
{
public:
	Controller();
	~Controller();

	void Update();

	bool IsConnected() { return connected; };

	// button states
	bool IsAPressed() { return (controllerState.Gamepad.wButtons & XINPUT_GAMEPAD_A); }
	bool IsBPressed() { return (controllerState.Gamepad.wButtons & XINPUT_GAMEPAD_B); }
	bool IsXPressed() { return (controllerState.Gamepad.wButtons & XINPUT_GAMEPAD_X); }
	bool IsYPressed() { return (controllerState.Gamepad.wButtons & XINPUT_GAMEPAD_Y); }
	bool IsRBPressed() { return (controllerState.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER); }
	bool IsLBPressed() { return (controllerState.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER); }
	bool IsStartPressed() { return (controllerState.Gamepad.wButtons & XINPUT_GAMEPAD_START); }
	bool IsBackPressed() { return (controllerState.Gamepad.wButtons & XINPUT_GAMEPAD_BACK); }
	bool IsLThumbPressed() { return (controllerState.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_THUMB); }
	bool IsRThumbPressed() { return (controllerState.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_THUMB); }
	bool IsDPUpPressed() { return (controllerState.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP); }
	bool IsDPDownPressed() { return (controllerState.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN); }
	bool IsDPLeftPressed() { return (controllerState.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT); }
	bool IsDPRightPressed() { return (controllerState.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT); }

	// trigger states
	float GetRightTriggerValue() { return controllerState.Gamepad.bRightTrigger / MAX_TRIGGER_VALUE; }
	float GetLeftTriggerValue() { return controllerState.Gamepad.bLeftTrigger / MAX_TRIGGER_VALUE; }

	// stick states
	float GetStickRXValue() { return controllerState.Gamepad.sThumbRX / MAX_STICK_VALUE; }
	float GetStickRYValue() { return controllerState.Gamepad.sThumbRY / MAX_STICK_VALUE; }
	float GetStickLXValue() { return controllerState.Gamepad.sThumbLX / MAX_STICK_VALUE; }
	float GetStickLYValue() { return controllerState.Gamepad.sThumbLY / MAX_STICK_VALUE; }

private:
	short controllerNum;
	bool connected = false;
	
	XINPUT_STATE controllerState;
	
	// input adjust values
	const float MAX_TRIGGER_VALUE = 255.0f;
	const float MAX_STICK_VALUE = 32768.0f;
	const float MAX_RUMBLE_VALUE = 65535.0f;
};

