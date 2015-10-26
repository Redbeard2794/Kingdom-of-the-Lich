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

//#include <Xinput.h>
//#pragma comment(lib, "XInput9_1_0.lib")   // Library. If your compiler doesn't support this type of lib include change to the corresponding one



#include <ctime>

////////////////////////////////////////////////////////////
///Entrypoint of application 
//////////////////////////////////////////////////////////// 


int main()
{
	//tmx::TileMap map("Assets/Areas/tutorialArea.tmx");

	// Create the main window 
	sf::RenderWindow window(sf::VideoMode(SCREENWIDTH, SCREENHEIGHT, 32), "Kingdom of the Lich");
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
	font.loadFromFile("Assets/Kelt Caps Freehand.TTF");

	//Player is created here(race,gender and maybe class will be set later)
	Player* p = new Player();

	window.setFramerateLimit(60);

	//text by cooltext.com
	sf::Sprite startup;
	sf::Texture startupTexture;
	startupTexture.loadFromFile("Assets/startScreenIcon.png");
	startup.setTexture(startupTexture);
	startup.setScale(sf::Vector2f(.5f, .5f));
	startup.setPosition(85, 260);

	//only here temporarily
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

	//curso
	sf::Sprite cursor;
	sf::Texture defaultCursor;
	defaultCursor.loadFromFile("Assets/Icons/Cursors/defaultCursor.png");
	cursor.setTexture(defaultCursor);


	//potions by http://opengameart.org/users/clint-bellanger

	//use gems as currency?

	//Icon for window corner
	//icon by http://opengameart.org/users/cron
	sf::Image icon;
	icon.loadFromFile("Assets/Icons/goldskull.png");
	window.setIcon(32, 32, icon.getPixelsPtr());

	bool useController = false;

	float leftStickXaxis;
	float leftStickYaxis;

	sf::Image screenShot;

	window.setMouseCursorVisible(false);
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

	Gamepad* gamepad = new Gamepad();
	useController = gamepad->CheckControllerConnection();

	Menu *mainMenu = new Menu(font, useController);
	ChooseRaceAndGenderMenu* raceAndGenderMenu = new ChooseRaceAndGenderMenu(font, useController);

	sf::Sprite splashHintSprite;
	sf::Texture splashHintTexture;
	sf::Text splashHintText1;
	splashHintText1.setFont(font);
	splashHintText1.setString("Press");
	//splashHintText1.setPosition(sf::Vector2f(SCREENWIDTH / 3, SCREENHEIGHT - 75));

	if (useController == true)
	{
		splashHintTexture.loadFromFile("Assets/ControllerHints/startButtonHint.png");
		splashHintText1.setPosition(sf::Vector2f(SCREENWIDTH / 2-100, SCREENHEIGHT - 75));
		ConfirmationDialogBox::GetInstance()->setShowControllerHints(true);
	}
	else if (useController == false)
	{
		splashHintTexture.loadFromFile("Assets/KeyboardAndMouseHints/spaceButtonHint.png");
		splashHintText1.setPosition(sf::Vector2f(SCREENWIDTH / 3, SCREENHEIGHT - 75));
		ConfirmationDialogBox::GetInstance()->setShowControllerHints(false);
	}

	ConfirmationDialogBox::GetInstance()->setHints();

	splashHintSprite.setTexture(splashHintTexture);
	splashHintSprite.setOrigin(sf::Vector2f(splashHintTexture.getSize().x / 2, splashHintTexture.getSize().y / 2));
	splashHintSprite.setPosition(sf::Vector2f(SCREENWIDTH / 2, SCREENHEIGHT - 50));

	bool spacePressed = false;
	bool enterPressed = false;

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
			window.draw(splashHintSprite);
			window.draw(splashHintText1);
			gamepad->CheckAllButtons();
			
			if (useController == true)
			{
				if (gamepad->Start() == true)
				{
					gState = MAINMENU;
					gamepad->Rumble(800, 0);
				}
			}

			else
			{
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))//up
				{
					gState = MAINMENU;
					std::cout << "Current game state: " << gState << std::endl;
				}
			}
			break;

		case MAINMENU:
			mainMenu->Draw(window);
			if (useController == false)
			{
				sf::Vector2i mousePos = sf::Mouse::getPosition(window);
				cursor.setPosition(sf::Vector2f(mousePos.x,mousePos.y));
				window.draw(cursor);
				mainMenu->CheckMouse(sf::Mouse::getPosition(window));
				if (mainMenu->getSelectedOption() == 0)//new game
					gState = CHOOSERACEGENDER;
				else if (mainMenu->getSelectedOption() == 1)//continue game
					std::cout << "Continue game not available yet" << std::endl;
				else if (mainMenu->getSelectedOption() == 2)//options
					std::cout << "Options not available yet" << std::endl;
				else if (mainMenu->getSelectedOption() == 3)//credits
					gState = CREDITS;
				else if (mainMenu->getSelectedOption() == 4)//quit
					window.close();
			}
			else if (useController == true)
			{
				gamepad->CheckAllButtons();

				if (gamepad->DpadUp() == true)
				{
					if (mainMenu->getCanMove() == true)
					{
						mainMenu->MoveUp();
						mainMenu->setCanMove(false);
					}
				}

				else if (gamepad->DpadDown() == true)
				{
					if (mainMenu->getCanMove() == true)
					{
						mainMenu->MoveDown();
						mainMenu->setCanMove(false);
					}
				}
				else mainMenu->setCanMove(true);

				if (gamepad->A() == true)
				{
					if (mainMenu->getSelectedOption() == 0)//new game
						gState = CHOOSERACEGENDER;
					else if (mainMenu->getSelectedOption() == 1)//continue game
						std::cout << "Continue game not available yet" << std::endl;
					else if (mainMenu->getSelectedOption() == 2)//options
						std::cout << "Options not available yet" << std::endl;
					else if (mainMenu->getSelectedOption() == 3)//credits
						gState = CREDITS;
					else if (mainMenu->getSelectedOption() == 4)//quit
						window.close();
				}
			}
			break;

		case CHOOSERACEGENDER:
			raceAndGenderMenu->Draw(window);

			if (useController == false)
			{
				sf::Vector2i mousePos = sf::Mouse::getPosition(window);
				if (ConfirmationDialogBox::GetInstance()->getVisible() == false)
				{
					raceAndGenderMenu->Update(sf::Mouse::getPosition(window));
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return)&& enterPressed==false)//up
					{
						if (raceAndGenderMenu->getCurrentState() == 0)
						{
							ConfirmationDialogBox::GetInstance()->setVisible(true);
							ConfirmationDialogBox::GetInstance()->setDialogText("Are you sure you want to be this race?", 20);
						}
						else if (raceAndGenderMenu->getCurrentState() == 1)
						{
							ConfirmationDialogBox::GetInstance()->setVisible(true);
							ConfirmationDialogBox::GetInstance()->setDialogText("Are you sure you want to be this gender?", 20);
						}
						enterPressed = true;
					}
				}
				else if (ConfirmationDialogBox::GetInstance()->getVisible() == true)
				{
					enterPressed = false;
					ConfirmationDialogBox::GetInstance()->CheckMouseToOptions(mousePos);

					if (ConfirmationDialogBox::GetInstance()->getOptionConfirmed() == true)
					{
						if (raceAndGenderMenu->getCurrentState() == 0)
						{
							if (ConfirmationDialogBox::GetInstance()->getCurrentOption() == 0)
							{
								p->setRace(raceAndGenderMenu->getCurrentlySelectedRace());
								raceAndGenderMenu->setCurrentState(1);
								ConfirmationDialogBox::GetInstance()->setVisible(false);
							}
							else if (ConfirmationDialogBox::GetInstance()->getCurrentOption() == 1)
							{
								raceAndGenderMenu->setCurrentState(0);
								ConfirmationDialogBox::GetInstance()->setVisible(false);
							}

						}
						else if (raceAndGenderMenu->getCurrentState() == 1)
						{
							if (ConfirmationDialogBox::GetInstance()->getCurrentOption() == 0)
							{
								p->setGender(raceAndGenderMenu->getCurrentlySelectedGender());
								//raceAndGenderMenu->setCurrentState(2);
								ConfirmationDialogBox::GetInstance()->setVisible(false);
								gState = GAME;
							}
							else if (ConfirmationDialogBox::GetInstance()->getCurrentOption() == 1)
							{
								raceAndGenderMenu->setCurrentState(1);
								ConfirmationDialogBox::GetInstance()->setVisible(false);
							}
						}
						ConfirmationDialogBox::GetInstance()->setOptionConfirmed(false);
					}
					
				}
				
				ConfirmationDialogBox::GetInstance()->Draw(window);


				cursor.setPosition(sf::Vector2f(mousePos.x, mousePos.y));
				window.draw(cursor);
				//if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return)&& spacePressed==false)//???
				//{
				//	
				//	if (raceAndGenderMenu->getCurrentState() == 0&&spacePressed==false)
				//	{
				//		raceAndGenderMenu->setCurrentState(1);
				//		spacePressed = true;
				//	}
				//	else if (raceAndGenderMenu->getCurrentState() == 1 && spacePressed == false)
				//	{
				//		raceAndGenderMenu->setCurrentState(2);
				//		spacePressed = true;
				//	}
				//	
				//}
				//else spacePressed = false;
				//if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
				//{
				//	p->setRace(raceAndGenderMenu->getCurrentlySelectedRace());
				//	p->setGender(raceAndGenderMenu->getCurrentlySelectedGender());
				//	p->setClass(raceAndGenderMenu->getCurrentlySelectedClass());
				//	std::cout << p->getRace() << ", " << p->getGender() << ", " << p->getClass() << std::endl;
				//	gState = GAME;
				//}
			}

			//if the player is using a controller
			else if (useController == true)
			{
				gamepad->CheckAllButtons();

				if (ConfirmationDialogBox::GetInstance()->getVisible() == false)
				{
					if (gamepad->DpadRight() == true)
					{
						if (raceAndGenderMenu->getCanMoveSelection() == true)
						{
							if (raceAndGenderMenu->getCurrentState() == 0)
								raceAndGenderMenu->moveRaceSelectionRight();
							else if (raceAndGenderMenu->getCurrentState() == 1)
								raceAndGenderMenu->moveGenderSelectionRight();
							else if (raceAndGenderMenu->getCurrentState() == 2)
								raceAndGenderMenu->moveClassSelectionRight();

							raceAndGenderMenu->setCanMoveSelection(false);
						}
					}

					else if (gamepad->DpadLeft() == true)
					{
						if (raceAndGenderMenu->getCanMoveSelection() == true)
						{
							if (raceAndGenderMenu->getCurrentState() == 0)
								raceAndGenderMenu->moveRaceSelectionLeft();
							else if (raceAndGenderMenu->getCurrentState() == 1)
								raceAndGenderMenu->moveGenderSelectionLeft();
							else if (raceAndGenderMenu->getCurrentState() == 2)
								raceAndGenderMenu->moveClassSelectionLeft();

							raceAndGenderMenu->setCanMoveSelection(false);
						}
					}
					else
					{
						raceAndGenderMenu->setCanMoveSelection(true);
						raceAndGenderMenu->setCanSelect(true);
					}


					//if (gamepad->A() == true)
					//{
					//	if (raceAndGenderMenu->getCurrentState() == 0 && raceAndGenderMenu->getCanSelect() == true)
					//		raceAndGenderMenu->setCanSelect(false);
					//	else if (raceAndGenderMenu->getCurrentState() == 1 && raceAndGenderMenu->getCanSelect() == true)
					//		raceAndGenderMenu->setCanSelect(false);
					//	else if (raceAndGenderMenu->getCurrentState() == 2 && raceAndGenderMenu->getCanSelect() == true)
					//		raceAndGenderMenu->setCanSelect(false);
					//}
					if (gamepad->RB())
					{
						if (raceAndGenderMenu->getCurrentState() == 0)
						{
							ConfirmationDialogBox::GetInstance()->setVisible(true);
							ConfirmationDialogBox::GetInstance()->setDialogText("Are you sure you want to be this race?", 20);
						}
						else if (raceAndGenderMenu->getCurrentState() == 1)
						{
							ConfirmationDialogBox::GetInstance()->setVisible(true);
							ConfirmationDialogBox::GetInstance()->setDialogText("Are you sure you want to be this gender?", 20);
						}
						else if (raceAndGenderMenu->getCurrentState() == 2)
						{
							ConfirmationDialogBox::GetInstance()->setVisible(true);
							ConfirmationDialogBox::GetInstance()->setDialogText("Are you sure you want to be this class?", 20);
						}

					}
				
				}
				else if (ConfirmationDialogBox::GetInstance()->getVisible() == true)
				{
					if (gamepad->DpadUp() == true)
					{
						if (ConfirmationDialogBox::GetInstance()->getCanMoveSelection() == true)
						{
							std::cout << "Moving up" << std::endl;
							ConfirmationDialogBox::GetInstance()->MoveUp();
							ConfirmationDialogBox::GetInstance()->setCanMoveSelection(false);
						}

					}
					
					else if (gamepad->DpadDown() == true)
					{
						if (ConfirmationDialogBox::GetInstance()->getCanMoveSelection() == true)
						{
							std::cout << "Moving down" << std::endl;
							ConfirmationDialogBox::GetInstance()->MoveDown();
							ConfirmationDialogBox::GetInstance()->setCanMoveSelection(false);
						}

					}

					else ConfirmationDialogBox::GetInstance()->setCanMoveSelection(true);

					if (gamepad->A() == true)
					{
						if (raceAndGenderMenu->getCurrentState() == 0)
						{
							if (ConfirmationDialogBox::GetInstance()->getCurrentOption() == 0)
							{
								p->setRace(raceAndGenderMenu->getCurrentlySelectedRace());
								std::cout << "race: " << p->getRace() << std::endl;
								raceAndGenderMenu->setCurrentState(1);
								ConfirmationDialogBox::GetInstance()->setVisible(false);
							}
							else if (ConfirmationDialogBox::GetInstance()->getCurrentOption() == 1)
							{
								raceAndGenderMenu->setCurrentState(0);
								ConfirmationDialogBox::GetInstance()->setVisible(false);
							}
						}

						else if (raceAndGenderMenu->getCurrentState() == 1)
						{
							if (ConfirmationDialogBox::GetInstance()->getCurrentOption() == 0)
							{
								p->setGender(raceAndGenderMenu->getCurrentlySelectedGender());
								raceAndGenderMenu->setCurrentState(2);
								ConfirmationDialogBox::GetInstance()->setVisible(false);
								gState = GAME;
							}
							else if (ConfirmationDialogBox::GetInstance()->getCurrentOption() == 1)
							{
								raceAndGenderMenu->setCurrentState(1);
								ConfirmationDialogBox::GetInstance()->setVisible(false);
							}
						}

						else if (raceAndGenderMenu->getCurrentState() == 2)
						{
							if (ConfirmationDialogBox::GetInstance()->getCurrentOption() == 0)
							{
								p->setClass(raceAndGenderMenu->getCurrentlySelectedClass());
								std::cout << p->getRace() << ", " << p->getGender() << ", " << p->getClass() << std::endl;
								ConfirmationDialogBox::GetInstance()->setVisible(false);
								gState = GAME;
							}
							else if (ConfirmationDialogBox::GetInstance()->getCurrentOption() == 1)
							{
								raceAndGenderMenu->setCurrentState(2);
								ConfirmationDialogBox::GetInstance()->setVisible(false);
							}
						}
					}
					//ConfirmationDialogBox::GetInstance()->Draw(window);
				}


				ConfirmationDialogBox::GetInstance()->Draw(window);
			}
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
				//if (XInputGetState(0, &state) == ERROR_SUCCESS)
				//{
				//	//for thumbsticks
				//	leftStickXaxis = state.Gamepad.sThumbLX;
				//	leftStickYaxis = state.Gamepad.sThumbLY;

				//	//determine how far the controller is pushed
				//	float magnitude = sqrt(leftStickXaxis*leftStickXaxis + leftStickYaxis*leftStickYaxis);

				//	//determine the direction the controller is pushed
				//	float normalizedLX = leftStickXaxis / magnitude;
				//	float normalizedLY = leftStickYaxis / magnitude;
				//	float normalizedMagnitude = 0;

				//	//D-pad
				//	if (state.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER) 
				//		p->setIsRunning(true);
				//	else p->setIsRunning(false);

				//	if (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP)
				//	{
				//		if (p->getIsRunning() == false)
				//			p->Move(sf::Vector2f(0, -1));
				//		else if (p->getIsRunning() == true)
				//			p->Move(sf::Vector2f(0, -2.5f));
				//	}
				//	else if (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN)
				//	{
				//		if (p->getIsRunning() == false)
				//			p->Move(sf::Vector2f(0, 1));
				//		else if (p->getIsRunning() == true)
				//			p->Move(sf::Vector2f(0, 2.5f));
				//	}
				//	else if (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT)
				//	{
				//		if (p->getIsRunning() == false)
				//			p->Move(sf::Vector2f(1, 0));
				//		else if (p->getIsRunning() == true)
				//			p->Move(sf::Vector2f(2.5f, 0));
				//	}
				//	else if (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT)
				//	{
				//		if (p->getIsRunning() == false)
				//			p->Move(sf::Vector2f(-1, 0));
				//		else if (p->getIsRunning() == true)
				//			p->Move(sf::Vector2f(-2.5f, 0));
				//	}
				//	if (state.Gamepad.wButtons & XINPUT_GAMEPAD_A)
				//	{
				//		if (aPressed == false)
				//		{
				//			// Button A is pressed
				//			std::cout << "A button pressed" << std::endl;
				//			aPressed = true;
				//		}
				//	}
				//	else aPressed = false;
				//	//thumbsticks
				//	//check if the controller is outside a circular dead zone
				//	if (magnitude > XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)
				//	{
				//		//clip the magnitude at its expected maximum value
				//		if (magnitude > 32767) magnitude = 32767;

				//		//adjust magnitude relative to the end of the dead zone
				//		magnitude -= XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE;

				//		//optionally normalize the magnitude with respect to its expected range
				//		//giving a magnitude value of 0.0 to 1.0
				//		normalizedMagnitude = magnitude / (32767 - XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE);

				//		if (normalizedLX > 0.9f)
				//		{
				//			if (p->getIsRunning() == false)
				//				p->Move(sf::Vector2f(1, 0));
				//			else if (p->getIsRunning() == true)
				//				p->Move(sf::Vector2f(2.5f, 0));
				//		}
				//		else if (normalizedLX < -0.9f)
				//		{
				//			if (p->getIsRunning() == false)
				//				p->Move(sf::Vector2f(-1, 0));
				//			else if (p->getIsRunning() == true)
				//				p->Move(sf::Vector2f(-2.5f, 0));
				//		}
				//		if (normalizedLY > 0.9f)
				//		{
				//			if (p->getIsRunning() == false)
				//				p->Move(sf::Vector2f(0, -1));
				//			else if (p->getIsRunning() == true)
				//				p->Move(sf::Vector2f(0, -2.5f));
				//		}
				//		else if (normalizedLY < -0.9f)
				//		{
				//			if (p->getIsRunning() == false)
				//				p->Move(sf::Vector2f(0, 1));
				//			else if (p->getIsRunning() == true)
				//				p->Move(sf::Vector2f(0, 2.5f));
				//		}
				//	}
				//}
			}


			//else//use keyboard
			//{
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
			//}

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