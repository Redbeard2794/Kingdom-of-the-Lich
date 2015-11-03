#ifndef GAMEPAD_H
#define GAMEPAD_H
#include <Xinput.h>
#pragma comment(lib, "XInput9_1_0.lib")   // Library. If your compiler doesn't support this type of lib include change to the corresponding one
class Gamepad
{
public:
	Gamepad();
	~Gamepad();

	/*Check whether the controller is connected*/
	bool CheckControllerConnection(bool showOutput);

	/*Cause the motors to rumble*/
	void Rumble(int leftMotorRumble, int rightMotorRumble);

	/*Call all checks for the different button presses*/
	void CheckAllButtons();

	/*methods to check button presses*/
	void CheckA();
	void CheckB();
	void CheckX();
	void CheckY();

	void CheckDpadUp();
	void CheckDpadDown();
	void CheckDpadRight();
	void CheckDpadLeft();

	void CheckRB();
	void CheckLB();

	void CheckStart();
	void CheckBack();

	/*retrieve the pressed state of each button*/
	bool A() { return aPressed; }
	bool B() { return bPressed; }
	bool X() { return xPressed; }
	bool Y() { return yPressed; }

	bool DpadUp() { return upPressed; }
	bool DpadDown() { return downPressed; }
	bool DpadRight() { return rightPressed; }
	bool DpadLeft() { return leftPressed; }

	bool RB() { return rbPressed; }
	bool LB() { return lbPressed; }

	bool Start() { return startPressed; }
	bool Back() { return backPressed; }

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
	//start and back/menu and view
	bool startPressed;
	bool backPressed;

};

#endif
