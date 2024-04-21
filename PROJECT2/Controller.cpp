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
	// zero the controller state
	ZeroMemory(&controllerState, sizeof(XINPUT_STATE));

	// update the controller
	DWORD Result = XInputGetState(controllerNum, &controllerState);

	// update bool based on connection state
	connected = (Result != ERROR_DEVICE_NOT_CONNECTED);
}