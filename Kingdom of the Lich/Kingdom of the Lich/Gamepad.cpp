#include "stdafx.h"
#include "Gamepad.h"

//constructor
Gamepad::Gamepad()
{
	memset(&state, 0, sizeof(XINPUT_STATE));
	memset(&motor, 0, sizeof(XINPUT_VIBRATION));

	aPressed = false;
	bPressed = false;
	xPressed = false;
	yPressed = false;
}

//destructor
Gamepad::~Gamepad()
{

}

/*Check whether the controller is connected*/
bool Gamepad::CheckControllerConnection(bool showOutput)
{
	if(showOutput == true)
		std::cout << "Gamepad is Checking for Xbox controller." << std::endl;
	if (XInputGetState(0, &state) == ERROR_SUCCESS)
	{
		if (showOutput == true)
			std::cout << "	* Xbox controller connected successfully." << std::endl;
		return true;
	}
	else
	{
		if (showOutput == true)
			std::cout << "	* No Xbox controller detected. You will need to use your keyboard and mouse to play." << std::endl;
		return false;
	}
}

/*Cause the motors to rumble*/
void Gamepad::Rumble(int leftMotorRumble, int rightMotorRumble)
{
	motor.wLeftMotorSpeed = leftMotorRumble;
	motor.wRightMotorSpeed = rightMotorRumble;
	XInputSetState(0, &motor);
}

/*Call all checks for the different button presses*/
void Gamepad::CheckAllButtons()
{
	CheckADown();
	CheckBDown();
	CheckXDown();
	CheckYDown();
	CheckDpadUp();
	CheckDpadDown();
	CheckDpadRight();
	CheckDpadLeft();
	CheckRB();
	CheckLB();
	CheckStart();
	CheckBack();
	CheckRT();
	CheckLT();
}

void Gamepad::CheckADown()
{
	if (XInputGetState(0, &state) == ERROR_SUCCESS)
	{
		if (state.Gamepad.wButtons & XINPUT_GAMEPAD_A)
		{
			if (aPressed == false)
			{
				aPressed = true;
				std::cout << "A down" << std::endl;
			}
		}
		else aPressed = false;
	}
}

void Gamepad::CheckBDown()
{
	if (XInputGetState(0, &state) == ERROR_SUCCESS)
	{
		if (state.Gamepad.wButtons & XINPUT_GAMEPAD_B)
		{
			if (bPressed == false)
			{
				bPressed = true;
				std::cout << "B down" << std::endl;
			}
		}
		else bPressed = false;
	}
}

void Gamepad::CheckXDown()
{
	if (XInputGetState(0, &state) == ERROR_SUCCESS)
	{
		if (state.Gamepad.wButtons & XINPUT_GAMEPAD_X)
		{
			if (xPressed == false)
			{
				xPressed = true;
				std::cout << "X down" << std::endl;
			}
		}
		else xPressed = false;
	}
}

void Gamepad::CheckYDown()
{
	if (XInputGetState(0, &state) == ERROR_SUCCESS)
	{
		if (state.Gamepad.wButtons & XINPUT_GAMEPAD_Y)
		{
			if (yPressed == false)
			{
				yPressed = true;
				std::cout << "Y down" << std::endl;
			}
		}
		else yPressed = false;
	}
}

void Gamepad::CheckDpadUp()
{
	if (XInputGetState(0, &state) == ERROR_SUCCESS)
	{
		if (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP)
		{
			if (upPressed == false)
			{
				upPressed = true;
				std::cout << "Dpad up pressed" << std::endl;
			}
		}
		else upPressed = false;
	}
}

void Gamepad::CheckDpadDown()
{
	if (XInputGetState(0, &state) == ERROR_SUCCESS)
	{
		if (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN)
		{
			if (downPressed == false)
			{
				downPressed = true;
				std::cout << "Dpad down pressed" << std::endl;
			}
		}
		else downPressed = false;
	}
}

void Gamepad::CheckDpadRight()
{
	if (XInputGetState(0, &state) == ERROR_SUCCESS)
	{
		if (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT)
		{
			if (rightPressed == false)
			{
				rightPressed = true;
				std::cout << "Dpad right pressed" << std::endl;
			}
		}
		else rightPressed = false;
	}
}

void Gamepad::CheckDpadLeft()
{
	if (XInputGetState(0, &state) == ERROR_SUCCESS)
	{
		if (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT)
		{
			if (leftPressed == false)
			{
				leftPressed = true;
				std::cout << "Dpad left pressed" << std::endl;
			}
		}
		else leftPressed = false;
	}
}

void Gamepad::CheckRB()
{
	if (XInputGetState(0, &state) == ERROR_SUCCESS)
	{
		if (state.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER)
		{
			if (rbPressed == false)
			{
				rbPressed = true;
				std::cout << "RB down" << std::endl;
			}
		}
		else rbPressed = false;
	}
}

void Gamepad::CheckLB()
{
	if (XInputGetState(0, &state) == ERROR_SUCCESS)
	{
		if (state.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER)
		{
			if (lbPressed == false)
			{
				lbPressed = true;
				std::cout << "LB down" << std::endl;
			}
		}
		else lbPressed = false;
	}
}

void Gamepad::CheckStart()
{
	if (XInputGetState(0, &state) == ERROR_SUCCESS)
	{
		if (state.Gamepad.wButtons & XINPUT_GAMEPAD_START)
		{
			if (startPressed == false)
			{
				startPressed = true;
				std::cout << "Start down" << std::endl;
			}
		}
		else startPressed = false;
	}
}

void Gamepad::CheckBack()
{
	if (XInputGetState(0, &state) == ERROR_SUCCESS)
	{
		if (state.Gamepad.wButtons & XINPUT_GAMEPAD_BACK)
		{
			if (backPressed == false)
			{
				backPressed = true;
				std::cout << "Back down" << std::endl;
			}
		}
		else backPressed = false;
	}
}

void Gamepad::CheckRT()
{
	if (XInputGetState(0, &state) == ERROR_SUCCESS)
	{
		if (state.Gamepad.bRightTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD)
		{
			if (rtPressed == false) 
			{
				rtPressed = true;
				std::cout << "RT pressed" << std::endl;
			}
		}
		else rtPressed = false;
	}
}

void Gamepad::CheckLT()
{
	if (XInputGetState(0, &state) == ERROR_SUCCESS)
	{
		if (state.Gamepad.bLeftTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD)
		{
			if (ltPressed == false)
			{
				ltPressed = true;
				std::cout << "LT pressed" << std::endl;
			}
		}
		else ltPressed = false;
	}
}
