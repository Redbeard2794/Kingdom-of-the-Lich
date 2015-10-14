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
	// Create the main window 
	sf::RenderWindow window(sf::VideoMode(800, 600, 32), "Kingdom of the Lich");
	sf::RenderWindow *pWindow = &window;

	//create sf::View
	sf::View player_view(sf::FloatRect(0, 0, window.getSize().x, window.getSize().y));
	//Set it to be size of window
	player_view.setViewport(sf::FloatRect(0, 0, 1, 1));

	//minimap
	unsigned int size = 100;
	sf::View minimap(sf::FloatRect(player_view.getCenter().x, player_view.getCenter().y, size, window.getSize().y*size / window.getSize().x));
	minimap.setViewport(sf::FloatRect(1.f - (1.f*minimap.getSize().x) / window.getSize().x - 0.02f, 1.f - (1.f*minimap.getSize().y) / window.getSize().y - 0.02f, (1.f*minimap.getSize().x) / window.getSize().x, (1.f*minimap.getSize().y) / window.getSize().y));
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
	}

	enum GameState
	{
		SPLASH,
		MAINMENU,
		CHOOSERACEGENDER,
		CHOOSECLASS,
		GAME,
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
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))//up
			{
				gState = GAME;
				std::cout << "Current game state: " << gState << std::endl;
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
				if (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP)
				{
					p->Move(sf::Vector2f(0, -1));
				}
				if (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN)
				{
					p->Move(sf::Vector2f(0, 1));
				}
				if (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT)
				{
					p->Move(sf::Vector2f(-1, 0));
				}
				if (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT)
				{
					p->Move(sf::Vector2f(1, 0));
				}
			}
			else//use keyboard
			{
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))//up
				{
					p->Move(sf::Vector2f(0, -1));
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))//down
				{
					p->Move(sf::Vector2f(0, 1));
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))//left
				{
					p->Move(sf::Vector2f(-1, 0));
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))//right
				{
					p->Move(sf::Vector2f(1, 0));
				}
			}

			window.draw(tempBground);
			p->draw(*pWindow);

			//drawing the minimap
			window.setView(minimap);
			minimap.setCenter(p->getPosition());
			window.draw(tempBground2);
			p->draw(*pWindow);
			break;

		case CREDITS:

			break;
		}


	

		

		 // Finally, display rendered frame on screen 
		window.display();
	} //loop back for next frame

	return EXIT_SUCCESS;
}