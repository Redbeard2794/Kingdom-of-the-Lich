#ifndef GAMEPAD_H
#define GAMEPAD_H
#include <Xinput.h>
#pragma comment(lib, "XInput9_1_0.lib")   // Library. If your compiler doesn't support this type of lib include change to the corresponding one
class Gamepad
{
public:
	Gamepad();
	~Gamepad();

	bool CheckControllerConnection();
	void Rumble(int leftMotorRumble, int rightMotorRumble);
	void CheckAllButtons();

	void CheckA();
	void CheckB();
	void CheckX();
	void CheckY();

	bool A() { return aPressed; }
	bool B() { return bPressed; }
	bool X() { return xPressed; }
	bool Y() { return yPressed; }

	void CheckDpadUp();
	void CheckDpadDown();
	void CheckDpadRight();
	void CheckDpadLeft();

	bool DpadUp() { return upPressed; }
	bool DpadDown() { return downPressed; }
	bool DpadRight() { return rightPressed; }
	bool DpadLeft() { return leftPressed; }

	void CheckRB();

	bool RB() { return rbPressed; }

private:
	XINPUT_STATE state;
	XINPUT_VIBRATION motor;

	//a,b,x,y
	bool aPressed;
	bool bPressed;
	bool xPressed;
	bool yPressed;
	//d-pad
	bool upPressed;
	bool downPressed;
	bool rightPressed;
	bool leftPressed;
	//shoulder buttons
	bool lbPressed;
	bool rbPressed;

};

#endif
