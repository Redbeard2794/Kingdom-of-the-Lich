//////////////////////////////////////////////////////////// 
// Headers 
//////////////////////////////////////////////////////////// 
#include "stdafx.h" 
#ifdef _DEBUG 
#pragma comment(lib,"sfml-graphics-d.lib") 
#pragma comment(lib,"sfml-audio-d.lib") 
#pragma comment(lib,"sfml-system-d.lib") 
#pragma comment(lib,"sfml-window-d.lib") 
#pragma comment(lib,"sfml-network-d.lib") 
#else 
#pragma comment(lib,"sfml-graphics.lib") 
#pragma comment(lib,"sfml-audio.lib") 
#pragma comment(lib,"sfml-system.lib") 
#pragma comment(lib,"sfml-window.lib") 
#pragma comment(lib,"sfml-network.lib") 
#endif 
#pragma comment(lib,"opengl32.lib") 
#pragma comment(lib,"glu32.lib") 

#include "SFML/Graphics.hpp" 
#include "SFML/OpenGL.hpp" 
#include <iostream> 
#define _USE_MATH_DEFINES
#include <math.h>

#include <Xinput.h>
#pragma comment(lib, "XInput9_1_0.lib")   // Library. If your compiler doesn't support this type of lib include change to the corresponding one



#include <ctime>

////////////////////////////////////////////////////////////
///Entrypoint of application 
//////////////////////////////////////////////////////////// 


int main()
{
	//tmx::TileMap map("Assets/Areas/tutorialArea.tmx");

	// Create the main window 
	sf::RenderWindow window(sf::VideoMode(800, 600, 32), "Kingdom of the Lich");
	sf::RenderWindow *pWindow = &window;

	//create sf::View
	sf::View player_view(sf::FloatRect(0, 0, window.getSize().x, window.getSize().y));
	//Set it to be size of window
	player_view.setViewport(sf::FloatRect(0, 0, 1, 1));

	//minimap
	unsigned int size = 130;//100
	sf::View minimap(sf::FloatRect(player_view.getCenter().x, player_view.getCenter().y, size, window.getSize().y*size / window.getSize().x));
	//change the viewport to change the maps size
	minimap.setViewport(sf::FloatRect(0.6f - (1.f*minimap.getSize().x) / window.getSize().x - 0.10f, 1.f - (1.f*minimap.getSize().y) / window.getSize().y - 0.004f, (2.0f*minimap.getSize().x) / window.getSize().x, (1.f*minimap.getSize().y) / (window.getSize().y)));
	minimap.zoom(4.f);

	//load a font
	sf::Font font;
	font.loadFromFile("C:\\Windows\\Fonts\\GARA.TTF");

	//these will be chosen in the menus so the player will actually be created later 
	Player* p = new Player("Elf", "Male", "Archer");

	window.setFramerateLimit(60);

	//text by cooltext.com
	sf::Sprite startup;
	sf::Texture startupTexture;
	startupTexture.loadFromFile("Assets/startScreenIcon.png");
	startup.setTexture(startupTexture);
	startup.setScale(sf::Vector2f(.5f, .5f));
	startup.setPosition(85, 260);

	sf::Sprite tempBground;
	sf::Texture tempBgroundTexture;
	tempBgroundTexture.loadFromFile("Assets/testingBackground.png");
	tempBground.setTexture(tempBgroundTexture);
	tempBground.setPosition(sf::Vector2f(0, 0));

	sf::Sprite tempBground2;
	sf::Texture tempBgroundTexture2;
	tempBgroundTexture2.loadFromFile("Assets/minmap.png");
	tempBground2.setTexture(tempBgroundTexture2);
	tempBground2.setPosition(sf::Vector2f(0, 0));




	//potions by http://opengameart.org/users/clint-bellanger

	//use gems as currency?

	//icon by http://opengameart.org/users/cron
	sf::Image icon;
	icon.loadFromFile("Assets/Icons/goldskull.png");
	window.setIcon(32, 32, icon.getPixelsPtr());

	XINPUT_STATE state;
	memset(&state, 0, sizeof(XINPUT_STATE));
	XINPUT_VIBRATION motor;
	memset(&motor, 0, sizeof(XINPUT_VIBRATION));
	bool useController;
	float leftStickXaxis;
	float leftStickYaxis;

	sf::Image screenShot;

	std::cout << "Checking for controller." << std::endl;
	if (XInputGetState(0, &state) == ERROR_SUCCESS)
	{
		std::cout << "	* Xbox controller connected successfully." << std::endl;
		useController = true;
	}
	else
	{
		std::cout << "	* No controller detected. You will need to use your keyboard to play." << std::endl;
		useController = false;
		window.setMouseCursorVisible(true);
	}

	enum GameState
	{
		SPLASH,
		MAINMENU,
		CHOOSERACEGENDER,
		CHOOSECLASS,
		GAME,
		COMBAT,
		CONVERSATION,
		INVENTORY,
		CREDITS
	};
	int gState = SPLASH;
	std::cout << "Current game state: " << gState << std::endl;

	// Start game loop 
	while (window.isOpen())
	{
		// Process events 
		sf::Event Event;
		while (window.pollEvent(Event))
		{
			// Close window : exit 
			if (Event.type == sf::Event::Closed)
				window.close();

			// Escape key : exit 
			if ((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::Escape))
				window.close();

			if ((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::P))
			{
				screenShot = window.capture();
				//time_t t = time(0);   // get time now
				//struct tm * now = localtime(&t);
				//int year = now->tm_year;
				//int month = now->tm_mon;
				//int day = now->tm_mday;
				//int hour = now->tm_hour;
				//int minute = now->tm_min;
				//sf::String dateInfo = year + "-" + month+day+hour+minute;
				screenShot.saveToFile("Assets/ScreenShots/testImg.png");
			}

			
		}

		window.clear();
		switch (gState)
		{
		case SPLASH:
			window.draw(startup);

			if (useController == true)
			{
				if (XInputGetState(0, &state) == ERROR_SUCCESS)
				{
					if (state.Gamepad.wButtons & XINPUT_GAMEPAD_A)
					{
						motor.wLeftMotorSpeed = 1000;
						motor.wRightMotorSpeed = 1000;
						gState = GAME;
						std::cout << "Current game state: " << gState << std::endl;
						XInputSetState(0, &motor);
					}
				}
			}

			else
			{
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))//up
				{
					gState = GAME;
					std::cout << "Current game state: " << gState << std::endl;
				}
			}
			break;

		case MAINMENU:

			break;

		case CHOOSERACEGENDER:

			break;

		case CHOOSECLASS:

			break;

		case GAME:
			//update sf::View center position
			player_view.setCenter(p->getPosition());

			//set view of window to be player_view
			window.setView(player_view);

			if (useController == true)//use controller
			{
				if (XInputGetState(0, &state) == ERROR_SUCCESS)
				{
					//for thumbsticks
					leftStickXaxis = state.Gamepad.sThumbLX;
					leftStickYaxis = state.Gamepad.sThumbLY;
					//std::cout << leftStickXaxis << std::endl;
					//determine how far the controller is pushed
					float magnitude = sqrt(leftStickXaxis*leftStickXaxis + leftStickYaxis*leftStickYaxis);

					//determine the direction the controller is pushed
					float normalizedLX = leftStickXaxis / magnitude;
					float normalizedLY = leftStickYaxis / magnitude;


					float normalizedMagnitude = 0;

					//check if the controller is outside a circular dead zone
					if (magnitude > XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)
					{
						//clip the magnitude at its expected maximum value
						if (magnitude > 32767) magnitude = 32767;

						//adjust magnitude relative to the end of the dead zone
						magnitude -= XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE;

						//optionally normalize the magnitude with respect to its expected range
						//giving a magnitude value of 0.0 to 1.0
						normalizedMagnitude = magnitude / (32767 - XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE);

						//std::cout << normalizedLX << std::endl;
						//std::cout << normalizedLY << std::endl;

						if (normalizedLX > 0.9f)
						{
							p->Move(sf::Vector2f(1, 0));
						}
						else if (normalizedLX < -0.9f)
						{
							p->Move(sf::Vector2f(-1, 0));
						}
						if (normalizedLY > 0.9f)
						{
							p->Move(sf::Vector2f(0, -1));
						}
						else if (normalizedLY < -0.9f)
						{
							p->Move(sf::Vector2f(0, 1));
						}

						//std::cout << normalizedMagnitude << std::endl;
					}


					if (state.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER) 
						p->setIsRunning(true);
					else p->setIsRunning(false);

					if (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP)
					{
						if (p->getIsRunning() == false)
							p->Move(sf::Vector2f(0, -1));
						else if (p->getIsRunning() == true)
							p->Move(sf::Vector2f(0, -2.5f));
					}
					else if (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN)
					{
						if (p->getIsRunning() == false)
							p->Move(sf::Vector2f(0, 1));
						else if (p->getIsRunning() == true)
							p->Move(sf::Vector2f(0, 2.5f));
					}
					else if (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT)
					{
						if (p->getIsRunning() == false)
							p->Move(sf::Vector2f(1, 0));
						else if (p->getIsRunning() == true)
							p->Move(sf::Vector2f(2.5f, 0));
					}
					else if (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT)
					{
						if (p->getIsRunning() == false)
							p->Move(sf::Vector2f(-1, 0));
						else if (p->getIsRunning() == true)
							p->Move(sf::Vector2f(-2.5f, 0));
					}
				}
			}
			else//use keyboard
			{
				//check if running
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
				{
					p->setIsRunning(true);
				}
				else { p->setIsRunning(false); }

				if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))//up
				{
					if(p->getIsRunning() == false)
						p->Move(sf::Vector2f(0, -1));
					else if (p->getIsRunning() ==true)
						p->Move(sf::Vector2f(0, -2.5f));
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))//down
				{
					if (p->getIsRunning() == false)
						p->Move(sf::Vector2f(0, 1));
					else if (p->getIsRunning() == true)
						p->Move(sf::Vector2f(0, 2.5f));
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))//left
				{
					if (p->getIsRunning() == false)
						p->Move(sf::Vector2f(-1, 0));
					else if (p->getIsRunning() == true)
						p->Move(sf::Vector2f(-2.5f, 0));
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))//right
				{
					if (p->getIsRunning() == false)
						p->Move(sf::Vector2f(1, 0));
					else if (p->getIsRunning() == true)
						p->Move(sf::Vector2f(2.5f, 0));
				}
			}

			window.draw(tempBground);
			p->Update();
			p->draw(*pWindow);

			//drawing the minimap
			window.setView(minimap);
			minimap.setCenter(p->getPosition());
			window.draw(tempBground2);
			p->draw(*pWindow);
			break;

		case COMBAT:

			break;

		case CONVERSATION:

			break;

		case INVENTORY:

			break;

		case CREDITS:

			break;
		}


	

		

		 // Finally, display rendered frame on screen 
		window.display();
	} //loop back for next frame

	return EXIT_SUCCESS;
}