#include "stdafx.h"
#include "Gamepad.h"

Gamepad::Gamepad()
{
	memset(&state, 0, sizeof(XINPUT_STATE));
	memset(&motor, 0, sizeof(XINPUT_VIBRATION));

	aPressed = false;
	bPressed = false;
	xPressed = false;
	yPressed = false;
}

Gamepad::~Gamepad()
{

}

bool Gamepad::CheckControllerConnection()
{
	std::cout << "Gamepad is Checking for Xbox controller." << std::endl;
	if (XInputGetState(0, &state) == ERROR_SUCCESS)
	{
		std::cout << "	* Xbox controller connected successfully." << std::endl;
		return true;
	}
	else
	{
		std::cout << "	* No Xbox controller detected. You will need to use your keyboard and mouse to play." << std::endl;
		return false;
	}
}

void Gamepad::Rumble(int leftMotorRumble, int rightMotorRumble)
{
	motor.wLeftMotorSpeed = leftMotorRumble;
	motor.wRightMotorSpeed = rightMotorRumble;
	XInputSetState(0, &motor);
}

void Gamepad::CheckAllButtons()
{
	CheckA();
	CheckB();
	CheckX();
	CheckY();
	CheckDpadUp();
	CheckDpadDown();
	CheckDpadRight();
	CheckDpadLeft();
	CheckRB();
	CheckLB();
	CheckStart();
}

void Gamepad::CheckA()
{
	if (XInputGetState(0, &state) == ERROR_SUCCESS)
	{
		if (state.Gamepad.wButtons & XINPUT_GAMEPAD_A)
		{
			if (aPressed == false)
			{
				aPressed = true;
				std::cout << "A" << std::endl;
			}
		}
		else aPressed = false;
	}
}

void Gamepad::CheckB()
{
	if (XInputGetState(0, &state) == ERROR_SUCCESS)
	{
		if (state.Gamepad.wButtons & XINPUT_GAMEPAD_B)
		{
			if (bPressed == false)
			{
				bPressed = true;
				std::cout << "B" << std::endl;
			}
		}
		else bPressed = false;
	}
}

void Gamepad::CheckX()
{
	if (XInputGetState(0, &state) == ERROR_SUCCESS)
	{
		if (state.Gamepad.wButtons & XINPUT_GAMEPAD_X)
		{
			if (xPressed == false)
			{
				xPressed = true;
				std::cout << "X" << std::endl;
			}
		}
		else xPressed = false;
	}
}

void Gamepad::CheckY()
{
	if (XInputGetState(0, &state) == ERROR_SUCCESS)
	{
		if (state.Gamepad.wButtons & XINPUT_GAMEPAD_Y)
		{
			if (yPressed == false)
			{
				yPressed = true;
				std::cout << "Y" << std::endl;
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
				std::cout << "Dpad up" << std::endl;
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
				std::cout << "Dpad down" << std::endl;
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
				std::cout << "Dpad right" << std::endl;
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
				std::cout << "Dpad left" << std::endl;
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
				std::cout << "RB" << std::endl;
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
				std::cout << "LB" << std::endl;
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
				std::cout << "Start" << std::endl;
			}
		}
		else startPressed = false;
	}
}

