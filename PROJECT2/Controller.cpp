#include "Controller.h"

// reduce windows.h import
#define WIN32_LEAN_AND_MEAN

// basic libraries
#include <iostream>
#include <windows.h>
#include <string>

// controller libraries
#include <Xinput.h>

using namespace std;

Controller::Controller()
{
	controllerNum = 0;
}


Controller::~Controller()
{
}


void Controller::Update()
{
	ZeroMemory(&controllerState, sizeof(XINPUT_STATE));

	DWORD Result = XInputGetState(controllerNum, &controllerState);

	if (Result == ERROR_DEVICE_NOT_CONNECTED)
	{
		connected = false;
	}
	else
	{
		connected = true;
		Rumble(GetLeftTriggerValue(), GetRightTriggerValue());
	}
}

// parameters are % of max speed
void Controller::Rumble(float leftSpeed, float rightSpeed)
{
	XINPUT_VIBRATION Vibration;

	ZeroMemory(&Vibration, sizeof(XINPUT_VIBRATION));

	Vibration.wLeftMotorSpeed = leftSpeed * MAX_RUMBLE_VALUE;
	Vibration.wRightMotorSpeed = rightSpeed * MAX_RUMBLE_VALUE;

	XInputSetState(controllerNum, &Vibration);
}