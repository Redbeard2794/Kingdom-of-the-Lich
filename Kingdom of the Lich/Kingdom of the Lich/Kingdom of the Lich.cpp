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

#include <ctime>

//rapidxml stuff
#include "rapidxml_utils.hpp"
using namespace rapidxml;
#include <sstream> // std::stringstream

////////////////////////////////////////////////////////////
///Entrypoint of application 
//////////////////////////////////////////////////////////// 


int main()
{
	/* initialize random seed: */
	srand(time(NULL));

	//https://github.com/edoren/STP
	tmx::TileMap map("Assets/tutorialArea.tmx");
	tmx::TileMap lowPolyMap("Assets/lowPolyTutorialArea.tmx");

	map.ShowObjects(); // Display all the layer objects.

	tmx::ObjectGroup collisionGroup = map.GetObjectGroup("Collision");

	//map.GetLayer("World").visible = false; // Hide a Layer named World

	// Create the main window 
	sf::RenderWindow window(sf::VideoMode(SCREENWIDTH, SCREENHEIGHT, 32), "Kingdom of the Lich");// , sf::Style::Titlebar);
	sf::RenderWindow *pWindow = &window;

	//create sf::View
	sf::View player_view(sf::FloatRect(0, 0, window.getSize().x, window.getSize().y));
	//player_view.zoom(1.5f);
	//Set it to be size of window
	player_view.setViewport(sf::FloatRect(0, 0, 1, 1));

	//minimap
	unsigned int size = 130;//100
	sf::View minimap(sf::FloatRect(player_view.getCenter().x, player_view.getCenter().y, size, window.getSize().y*size / window.getSize().x));
	//change the viewport to change the maps size
	minimap.setViewport(sf::FloatRect(0.6f - (1.f*minimap.getSize().x) / window.getSize().x - 0.10f, 1.f - (1.f*minimap.getSize().y) / window.getSize().y - 0.004f, (2.0f*minimap.getSize().x) / window.getSize().x, (1.f*minimap.getSize().y) / (window.getSize().y)));
	minimap.zoom(3.f);//4

	//load a font
	sf::Font font;
	font.loadFromFile("Assets/Kelt Caps Freehand.TTF");

	//Player is created here(race,gender and maybe class will be set later)
	Player* p = new Player(font);
	Hud* hud = new Hud(font);

	window.setFramerateLimit(60);//is this causing the flickering in the mini map

	//text by cooltext.com
	//splash screen
	sf::Sprite startup;
	sf::Texture startupTexture;
	startupTexture.loadFromFile("Assets/Splash Screen/startScreenIcon.png");
	startup.setTexture(startupTexture);
	startup.setScale(sf::Vector2f(.5f, .5f));
	startup.setPosition(85, 260);

	//clock for fading stuff in and out and changing colours
	sf::Clock* splashClock = new sf::Clock();

	//cursor
	sf::Sprite cursor;
	sf::Texture defaultCursor;
	defaultCursor.loadFromFile("Assets/Icons/Cursors/defaultCursor.png");
	cursor.setTexture(defaultCursor);


	//potions by http://opengameart.org/users/clint-bellanger

	//Icon for window corner
	//icon by http://opengameart.org/users/cron
	sf::Image icon;
	icon.loadFromFile("Assets/Icons/goldskull.png");
	window.setIcon(32, 32, icon.getPixelsPtr());

	//are we using a controller
	bool useController = false;

	float leftStickXaxis;
	float leftStickYaxis;

	sf::Image screenShot;

	window.setMouseCursorVisible(false);

	//game states
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
	int gState = SPLASH;//current state
	std::cout << "Current game state: " << gState << std::endl;

	Gamepad* gamepad = new Gamepad();
	useController = gamepad->CheckControllerConnection(true);

	Menu *mainMenu = new Menu(font, useController);

	ChooseRaceAndGenderMenu* raceAndGenderMenu = new ChooseRaceAndGenderMenu(font, useController);

	//hints for the splash screen
	sf::Sprite splashHintSprite;
	sf::Texture splashHintTexture;
	sf::Text splashHintText1;
	splashHintText1.setFont(font);
	splashHintText1.setString("Press");

	if (useController == true)//controller hints
	{
		splashHintTexture.loadFromFile("Assets/ControllerHints/startButtonHint.png");
		splashHintText1.setPosition(sf::Vector2f(SCREENWIDTH / 2-100, SCREENHEIGHT - 75));
		ConfirmationDialogBox::GetInstance()->setShowControllerHints(true);
	}
	else if (useController == false)//keyboard and mouse hints
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
	int enterCount = 0;


	//for testing inventory
	Inventory* testInv = new Inventory(font, useController);
	testInv->PrintAllInventory();
	testInv->AddItemToInventory(testInv->i_gems.key, 5);


	//testing npc
	//Npc* CommanderIronArm = new Npc("Commander Iron-Arm", 1, sf::Vector2f(1000, 1000));
	//CommanderIronArm->LoadInteractHintTexture(useController);


	//testing chest
	Chest* testChest = new Chest(testInv->i_healthPotion.key, 3);
	testChest->LoadInteractHintTexture(useController);


	//hint for showing the player how to walk around
	sf::Texture moveHintTexture;
	sf::Sprite moveHintSprite;
	if (useController == true)
		moveHintTexture.loadFromFile("Assets/ControllerHints/useDpadToMoveHint.png");
	else moveHintTexture.loadFromFile("Assets/KeyboardAndMouseHints/useWASDToMoveHint.png");
	moveHintSprite.setTexture(moveHintTexture);
	moveHintSprite.setOrigin(moveHintTexture.getSize().x / 2, moveHintTexture.getSize().y / 2);
	moveHintSprite.setPosition(SCREENWIDTH/2, SCREENHEIGHT/2);


	//quest stuff is temporary until I figure out what I am doing with the quest controller
	sf::Text objective;
	objective.setFont(font);
	objective.setString("Go and talk to Commander Iron-Arm. Use your compass to find him.");
	objective.setPosition(sf::Vector2f(SCREENWIDTH / 18, SCREENHEIGHT / 2));
	objective.setColor(sf::Color::Black);
	objective.setCharacterSize(22);
	objective.setStyle(sf::Text::Bold);

	sf::Text questCompletePopup;
	questCompletePopup.setFont(font);
	if(useController == true)
		questCompletePopup.setString("Quest complete. You got 3 potions from the chest. Press 'B' now.");
	else questCompletePopup.setString("Quest complete. You got 3 potions from the chest. Press 'I' now.");
	questCompletePopup.setPosition(sf::Vector2f(SCREENWIDTH / 18, SCREENHEIGHT / 2));
	questCompletePopup.setColor(sf::Color::Black);
	questCompletePopup.setCharacterSize(20);
	questCompletePopup.setStyle(sf::Text::Bold);

	bool showQuestComplete = false;

	AudioManager* audioManager = new AudioManager();
	//play the first song
	audioManager->PlayMusicById(0);

	//npcs :)
	std::vector<Npc*> npcVector;

	xml_document<> doc;
	std::ifstream file("Assets/npcList.xml");
	std::stringstream buffer;
	buffer << file.rdbuf();
	file.close();
	std::string content(buffer.str());
	doc.parse<0>(&content[0]);

	xml_node<> *pRoot = doc.first_node();
	std::cout << "Name of root node is: " << doc.first_node()->name() << "\n" << std::endl;

	xml_node<>* npcList = doc.first_node("npcList");
	xml_node<>* npc = npcList->first_node("npc");

	//load in each npc's information and then create them
	while (npc != NULL)
	{
		//name, id, race, gender, texturePath, mapIconTexturePath, x, y, hasQuest, behaviour
		std::string name = "";
		int id = 0;
		std::string race = "";
		std::string gender = "";
		std::string texturePath = "";

		std::string idleUpPath = "";
		std::string idleDownPath = "";
		std::string idleLeftPath = "";
		std::string idleRightPath = "";

		int numberOfFrames = 0;

		std::string walkUpPath = "";
		std::string walkDownPath = "";
		std::string walkLeftPath = "";
		std::string walkRightPath = "";

		std::string mapIconTexturePath = "";
		float x = 0;
		float y = 0;
		bool hasQuest = false;
		std::string behaviour = "";

		/*Get the npc's name*/
		std::cout << "Name: " << npc->first_attribute("name")->value() << std::endl;
		name = npc->first_attribute("name")->value();

		/*Get the npc's id*/
		std::cout << "I.D: " << npc->first_node("id")->value() << std::endl;
		id = atoi(npc->first_node("id")->value());

		/*Get the npc's race*/
		std::cout << "Race: " << npc->first_node("race")->value() << std::endl;
		race = npc->first_node("race")->value();

		/*Get the npc's gender*/
		std::cout << "Gender: " << npc->first_node("gender")->value() << std::endl;
		gender = npc->first_node("gender")->value();

		/*get paths for idle sprites*/
		std::cout << "Idle up path: " << npc->first_node("idleUpPath")->value() << std::endl;
		idleUpPath = npc->first_node("idleUpPath")->value();

		std::cout << "Idle down path: " << npc->first_node("idleDownPath")->value() << std::endl;
		idleDownPath = npc->first_node("idleDownPath")->value();

		std::cout << "Idle left path: " << npc->first_node("idleLeftPath")->value() << std::endl;
		idleLeftPath = npc->first_node("idleLeftPath")->value();

		std::cout << "Idle right path: " << npc->first_node("idleRightPath")->value() << std::endl;
		idleRightPath = npc->first_node("idleRightPath")->value();

		/*Get the number of frames*/
		std::cout << "Number of frames: " << npc->first_node("numberOfFrames")->value() << std::endl;
		numberOfFrames = atoi( npc->first_node("numberOfFrames")->value());

		/*get paths for walking sprites*/
		std::cout << "Walk up path: " << npc->first_node("walkUpPath")->value() << std::endl;
		walkUpPath = npc->first_node("walkUpPath")->value();

		std::cout << "Walk down path: " << npc->first_node("walkDownPath")->value() << std::endl;
		walkDownPath = npc->first_node("walkDownPath")->value();

		std::cout << "Walk left path: " << npc->first_node("walkLeftPath")->value() << std::endl;
		walkLeftPath = npc->first_node("walkLeftPath")->value();

		std::cout << "Walk right path: " << npc->first_node("walkRightPath")->value() << std::endl;
		walkRightPath = npc->first_node("walkRightPath")->value();

		/*minimap icon path*/
		std::cout << "Map icon texture path: " << npc->first_node("mapIconTexturePath")->value() << std::endl;
		mapIconTexturePath = npc->first_node("mapIconTexturePath")->value();

		/*x position*/
		std::cout << "X: " << npc->first_node("x")->value() << std::endl;
		x = atof(npc->first_node("x")->value());

		/*y position*/
		std::cout << "Y: " << npc->first_node("y")->value() << std::endl;
		y = atof(npc->first_node("y")->value());

		/*Does the npc have a quest for the player*/
		std::cout << "Has quest: " << npc->first_node("hasQuest")->value() << std::endl;
		hasQuest = npc->first_node("hasQuest")->value();

		/*What behaviour do they have? e.g: wander, stand etc*/
		std::cout << "Behaviour: " << npc->first_node("behaviour")->value() << std::endl;
		behaviour = npc->first_node("behaviour")->value();

		/*Create the npc*/
		Npc* n = new Npc(name, id, idleUpPath, idleDownPath, idleLeftPath, idleRightPath, numberOfFrames, walkUpPath, walkDownPath, walkLeftPath, walkRightPath, mapIconTexturePath, sf::Vector2f(x, y), hasQuest, behaviour, useController);
		npcVector.push_back(n);
		std::cout << "Size of npcVector: " << npcVector.size() << std::endl;

		std::cout << "------------------------------------------------------------" << std::endl;
		/*Move onto the next npc tag*/
		npc = npc->next_sibling("npc");
	}


	//testing quest
	Quest* testQuest = new Quest(2, "Learn how chests work", npcVector.at(0)->getNpcName(), npcVector.at(0)->getPosition(), 1, 5, 5);

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

			//change the colour of the splash image based on time
			if (splashClock->getElapsedTime().asSeconds() > 1 && splashClock->getElapsedTime().asSeconds() < 2)
			{
				startup.setColor(sf::Color::Blue);
				splashHintSprite.setColor(sf::Color::Transparent);
				splashHintText1.setColor(sf::Color::Transparent);
			}
			else if (splashClock->getElapsedTime().asSeconds() > 2)
			{
				startup.setColor(sf::Color::White);
				splashHintSprite.setColor(sf::Color::White);
				splashHintText1.setColor(sf::Color::White);
				splashClock->restart();
			}
			
			//if the player is using a controller
			if (useController == true)
			{
				gamepad->CheckAllButtons();
				if (gamepad->CheckControllerConnection(false) == false)
					useController = false;
				if (gamepad->Start() == true)
				{
					audioManager->PlaySoundEffectById(2, true);
					gState = MAINMENU;
					gamepad->Rumble(800, 0);
				}
			}
			//if the player is using keyboard/mouse
			else
			{
				if (gamepad->CheckControllerConnection(false) == true)
					useController = true;
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))//up
				{
					audioManager->PlaySoundEffectById(2, true);
					gState = MAINMENU;
					std::cout << "Current game state: " << gState << std::endl;
				}
			}
			break;

		case MAINMENU:
			mainMenu->Draw(window);

			//if the player is using keyboard and mouse
			if (useController == false)
			{
				//show the cursor
				//sf::Vector2i mousePos = sf::Mouse::getPosition(window);
				//cursor.setPosition(sf::Vector2f(mousePos.x,mousePos.y));
				//window.draw(cursor);

				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
				{
					if (mainMenu->getCanMove() == true)
					{
						audioManager->PlaySoundEffectById(1, false);
						mainMenu->MoveUp();
						mainMenu->setCanMove(false);
					}
				}

				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
				{
					if (mainMenu->getCanMove() == true)
					{
						audioManager->PlaySoundEffectById(1, false);
						mainMenu->MoveDown();
						mainMenu->setCanMove(false);
					}
				}

				else mainMenu->setCanMove(true);

				//mainMenu->CheckMouse(sf::Mouse::getPosition(window));

				//which option is the player choosing
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return) && enterPressed == false)
				{
					enterPressed = true;
					audioManager->PlaySoundEffectById(2, true);
					if (mainMenu->getSelectedOption() == 0)//new game
					{
						enterPressed = false;
						audioManager->PlaySoundEffectById(0, true);
						gState = CHOOSERACEGENDER;
					}
					else if (mainMenu->getSelectedOption() == 1)//continue game
					{
						enterPressed = false;
						//std::cout << "Continue game not available yet" << std::endl;
					}
					else if (mainMenu->getSelectedOption() == 2)//options
					{
						enterPressed = false;
						//std::cout << "Options not available yet" << std::endl;
					}
					else if (mainMenu->getSelectedOption() == 3)//credits
					{
						enterPressed = false;
						gState = CREDITS;
					}
					else if (mainMenu->getSelectedOption() == 4)//quit
					{
						enterPressed = false;
						window.close();
					}

					
				}
			}

			//if the player is using a controller
			else if (useController == true)
			{
				gamepad->CheckAllButtons();

				if (gamepad->DpadUp() == true || (gamepad->getNormalisedLeftStickAxis().y > 0.9f && gamepad->isLeftAxisOutOfDeadzone() == true))
				{
					if (mainMenu->getCanMove() == true)
					{
						audioManager->PlaySoundEffectById(1, false);
						mainMenu->MoveUp();
						mainMenu->setCanMove(false);
					}
				}

				else if (gamepad->DpadDown() == true || (gamepad->getNormalisedLeftStickAxis().y < -0.9f && gamepad->isLeftAxisOutOfDeadzone() == true))
				{
					if (mainMenu->getCanMove() == true)
					{
						audioManager->PlaySoundEffectById(1, false);
						mainMenu->MoveDown();
						mainMenu->setCanMove(false);
					}
				}
				else mainMenu->setCanMove(true);

				if (gamepad->A() == true)
				{
					audioManager->PlaySoundEffectById(2, true);

					if (mainMenu->getSelectedOption() == 0)//new game
					{
						audioManager->PlaySoundEffectById(0, true);
						gState = CHOOSERACEGENDER;
					}
					else if (mainMenu->getSelectedOption() == 1)//continue game
					{
						std::cout << "Continue game not available yet" << std::endl;
					}
					else if (mainMenu->getSelectedOption() == 2)//options
					{
						std::cout << "Options not available yet" << std::endl;
					}
					else if (mainMenu->getSelectedOption() == 3)//credits
					{
						gState = CREDITS;
					}
					else if (mainMenu->getSelectedOption() == 4)//quit
					{
						window.close();
					}
				}
			}
			break;

		case CHOOSERACEGENDER:
			audioManager->FadeOutMusic(0);

			raceAndGenderMenu->Draw(window);

			if (useController == false)//using keyboard and mouse
			{
				sf::Vector2i mousePos = sf::Mouse::getPosition(window);
				//set up the dialog box based on menu state and allow player to choose
				if (ConfirmationDialogBox::GetInstance()->getVisible() == false)
				{
					enterPressed = false;
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
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
							audioManager->PlaySoundEffectById(1, false);
						}
					}

					else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
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
							audioManager->PlaySoundEffectById(1, false);
						}
					}
					else
					{
						raceAndGenderMenu->setCanMoveSelection(true);
						raceAndGenderMenu->setCanSelect(true);
					}

					//raceAndGenderMenu->Update(sf::Mouse::getPosition(window));
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))// && enterPressed==false)//up
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
					//ConfirmationDialogBox::GetInstance()->CheckMouseToOptions(mousePos);

					//move up and down through yes and no in the dialog box
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
					{
						if (ConfirmationDialogBox::GetInstance()->getCanMoveSelection() == true)
						{
							ConfirmationDialogBox::GetInstance()->MoveUp();
							ConfirmationDialogBox::GetInstance()->setCanMoveSelection(false);
							audioManager->PlaySoundEffectById(1, false);
						}

					}

					else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
					{
						if (ConfirmationDialogBox::GetInstance()->getCanMoveSelection() == true)
						{
							ConfirmationDialogBox::GetInstance()->MoveDown();
							ConfirmationDialogBox::GetInstance()->setCanMoveSelection(false);
							audioManager->PlaySoundEffectById(1, false);
						}

					}
					else ConfirmationDialogBox::GetInstance()->setCanMoveSelection(true);


					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
					{
						if (raceAndGenderMenu->getCurrentState() == 0)//choosing race
						{
							if (ConfirmationDialogBox::GetInstance()->getCurrentOption() == 0)
							{
								p->setRace(raceAndGenderMenu->getCurrentlySelectedRace());
								std::cout << "race: " << p->getRace() << std::endl;
								raceAndGenderMenu->setCurrentState(1);
								ConfirmationDialogBox::GetInstance()->setVisible(false);
								audioManager->PlaySoundEffectById(2, true);
							}
							else if (ConfirmationDialogBox::GetInstance()->getCurrentOption() == 1)
							{
								raceAndGenderMenu->setCurrentState(0);
								ConfirmationDialogBox::GetInstance()->setVisible(false);
								audioManager->PlaySoundEffectById(2, true);
							}
						}

						else if (raceAndGenderMenu->getCurrentState() == 1)//choosing gender
						{
							if (ConfirmationDialogBox::GetInstance()->getCurrentOption() == 0)
							{
								p->setGender(raceAndGenderMenu->getCurrentlySelectedGender());
								raceAndGenderMenu->setCurrentState(2);
								ConfirmationDialogBox::GetInstance()->setVisible(false);
								gState = GAME;
								p->setTextures();
								std::cout << "Race: " << p->getRace() << ", " << "Gender: " << p->getGender() << std::endl;
								splashClock->restart();
								audioManager->PlaySoundEffectById(2, true);
								audioManager->PlayMusicById(1);
							}
							else if (ConfirmationDialogBox::GetInstance()->getCurrentOption() == 1)
							{
								raceAndGenderMenu->setCurrentState(1);
								ConfirmationDialogBox::GetInstance()->setVisible(false);
								audioManager->PlaySoundEffectById(2, true);
							}
						}

						else if (raceAndGenderMenu->getCurrentState() == 2)//choosing class(not functional :( )
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
								audioManager->PlaySoundEffectById(2, true);
							}
						}
					}
				}
				
				ConfirmationDialogBox::GetInstance()->Draw(window);


				cursor.setPosition(sf::Vector2f(mousePos.x, mousePos.y));
				window.draw(cursor);

			}

			//if the player is using a controller
			else if (useController == true)
			{
				gamepad->CheckAllButtons();
				//set up the dialog box based on menu state and allow player to choose
				if (ConfirmationDialogBox::GetInstance()->getVisible() == false)
				{
					if (gamepad->DpadRight() == true || (gamepad->getNormalisedLeftStickAxis().x > 0.9f && gamepad->isLeftAxisOutOfDeadzone() == true))
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
							audioManager->PlaySoundEffectById(1, false);
						}
					}

					else if (gamepad->DpadLeft() == true || (gamepad->getNormalisedLeftStickAxis().x < -0.9f && gamepad->isLeftAxisOutOfDeadzone() == true))
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
							audioManager->PlaySoundEffectById(1, false);
						}
					}
					else
					{
						raceAndGenderMenu->setCanMoveSelection(true);
						raceAndGenderMenu->setCanSelect(true);
					}
					//confirm the players choice and present the dialog box
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
					//move up and down through yes and no in the dialog box
					if (gamepad->DpadUp() == true || (gamepad->getNormalisedLeftStickAxis().y > 0.9f && gamepad->isLeftAxisOutOfDeadzone() == true))
					{
						if (ConfirmationDialogBox::GetInstance()->getCanMoveSelection() == true)
						{
							ConfirmationDialogBox::GetInstance()->MoveUp();
							ConfirmationDialogBox::GetInstance()->setCanMoveSelection(false);
							audioManager->PlaySoundEffectById(1, false);
						}

					}
					
					else if (gamepad->DpadDown() == true || (gamepad->getNormalisedLeftStickAxis().y < -0.9f && gamepad->isLeftAxisOutOfDeadzone() == true))
					{
						if (ConfirmationDialogBox::GetInstance()->getCanMoveSelection() == true)
						{
							ConfirmationDialogBox::GetInstance()->MoveDown();
							ConfirmationDialogBox::GetInstance()->setCanMoveSelection(false);
							audioManager->PlaySoundEffectById(1, false);
						}

					}

					else ConfirmationDialogBox::GetInstance()->setCanMoveSelection(true);

					if (gamepad->A() == true)
					{
						if (raceAndGenderMenu->getCurrentState() == 0)//choosing race
						{
							if (ConfirmationDialogBox::GetInstance()->getCurrentOption() == 0)
							{
								p->setRace(raceAndGenderMenu->getCurrentlySelectedRace());
								std::cout << "race: " << p->getRace() << std::endl;
								raceAndGenderMenu->setCurrentState(1);
								ConfirmationDialogBox::GetInstance()->setVisible(false);
								audioManager->PlaySoundEffectById(2, true);
							}
							else if (ConfirmationDialogBox::GetInstance()->getCurrentOption() == 1)
							{
								raceAndGenderMenu->setCurrentState(0);
								ConfirmationDialogBox::GetInstance()->setVisible(false);
								audioManager->PlaySoundEffectById(2, true);
							}
						}

						else if (raceAndGenderMenu->getCurrentState() == 1)//choosing gender
						{
							if (ConfirmationDialogBox::GetInstance()->getCurrentOption() == 0)
							{
								p->setGender(raceAndGenderMenu->getCurrentlySelectedGender());
								raceAndGenderMenu->setCurrentState(2);
								ConfirmationDialogBox::GetInstance()->setVisible(false);
								gState = GAME;
								p->setTextures();
								std::cout << "Race: " << p->getRace() << ", " << "Gender: " << p->getGender() << std::endl;
								splashClock->restart();
								audioManager->PlaySoundEffectById(2, true);
								audioManager->PlayMusicById(1);
							}
							else if (ConfirmationDialogBox::GetInstance()->getCurrentOption() == 1)
							{
								raceAndGenderMenu->setCurrentState(1);
								ConfirmationDialogBox::GetInstance()->setVisible(false);
								audioManager->PlaySoundEffectById(2, true);
							}
						}

						else if (raceAndGenderMenu->getCurrentState() == 2)//choosing class(not functional :( )
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
								audioManager->PlaySoundEffectById(2, true);
							}
						}
					}
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

				gamepad->CheckAllButtons();

				//is player running
				if (gamepad->RT())
					p->setIsRunning(true);
				else p->setIsRunning(false);

				//move with d-pad
				if (gamepad->DpadUp())
					p->Move(0);
				else if (gamepad->DpadDown())
					p->Move(1);
				else if (gamepad->DpadRight())
					p->Move(2);
				else if (gamepad->DpadLeft())
					p->Move(3);
				else p->setCurrentDirection(4);

				//move with analog sticks
				if (gamepad->getNormalisedLeftStickAxis().x > 0.9f && gamepad->isLeftAxisOutOfDeadzone() == true)
					p->Move(2);
				else if (gamepad->getNormalisedLeftStickAxis().x < -0.9f && gamepad->isLeftAxisOutOfDeadzone() == true)
					p->Move(3);
				if (gamepad->getNormalisedLeftStickAxis().y > 0.9f && gamepad->isLeftAxisOutOfDeadzone() == true)
					p->Move(0);
				else if (gamepad->getNormalisedLeftStickAxis().y < -0.9f && gamepad->isLeftAxisOutOfDeadzone() == true)
					p->Move(1);
				else p->setCurrentDirection(4);


				//access inventory
				if (gamepad->B())
				{
					gState = INVENTORY;
					audioManager->PlaySoundEffectById(3, true);
				}

				//check for collision between player and commander and update quest
				if (p->CollisionWithNpc(npcVector.at(0)) == true && gamepad->A() == true)
				{
					if (testQuest->getCurrentStageIndex() == 0)
					{
						std::cout << "Go and open that chest and retrieve the items within. Walk up to it and press the 'A' button" << std::endl;
						testQuest->getCurrentStage()->setCompletionStatus(true);
						testQuest->setCurrentStageIndex(1);
					}
				}
				//check for collision between player and chest and update quest
				if (p->CollisionWithChest(testChest->getSprite()) == true && gamepad->A() == true)
				{
					if (testChest->getOpened() == false)
					{
						if (testQuest->getCurrentStageIndex() == 1)
						{
							testChest->OpenChest(testInv);
							testQuest->getCurrentStage()->setCompletionStatus(true);
							testQuest->setCompletionStatus(true);
							std::cout << "You completed your first quest!" << std::endl;
							splashClock->restart();
							audioManager->PlaySoundEffectById(4, true);
						}
						else
						{
							std::cout << "You may not open this chest right now." << std::endl;
							audioManager->PlaySoundEffectById(5, true);
						}
					}
					else std::cout << "This chest has already been opened. There is nothing in it." << std::endl;
				}
			}


			else//use keyboard
			{
					//check if running
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
					p->setIsRunning(true);
				else { p->setIsRunning(false); }

				if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))//up
					p->Move(0);
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))//down
					p->Move(1);
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))//left
					p->Move(3);
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))//right
					p->Move(2);
				else p->setCurrentDirection(4);

				if (sf::Keyboard::isKeyPressed(sf::Keyboard::I))
				{
					audioManager->PlaySoundEffectById(3, true);
					gState = INVENTORY;
				}

				//check for collision between player and commander and update quest
				if (p->CollisionWithNpc(npcVector.at(0)) == true && sf::Keyboard::isKeyPressed(sf::Keyboard::E))// , testInv);
				{
					if (testQuest->getCurrentStageIndex() == 0)
					{
						std::cout << "Go and open that chest and retrieve the items within. Walk up to it and press the 'E'" << std::endl;
						testQuest->getCurrentStage()->setCompletionStatus(true);
						testQuest->setCurrentStageIndex(1);
					}
				}
				//check for collision between player and chest and update quest
				if (p->CollisionWithChest(testChest->getSprite()) == true && sf::Keyboard::isKeyPressed(sf::Keyboard::E))// , testInv);
				{
					if (testChest->getOpened() == false)
					{
						if (testQuest->getCurrentStageIndex() == 1)
						{
							testChest->OpenChest(testInv);
							testQuest->getCurrentStage()->setCompletionStatus(true);
							testQuest->setCompletionStatus(true);
							std::cout << "You completed your first quest!" << std::endl;
							splashClock->restart();
							audioManager->PlaySoundEffectById(4, true);
						}
						else
						{
							std::cout << "You may not open this chest right now." << std::endl;
							audioManager->PlaySoundEffectById(5, true);
						}
					}
					else std::cout << "This chest has already been opened. There is nothing in it." << std::endl;
				}
			}

			window.draw(map);

			//update the player
			p->Update();

			testChest->Update(p->getPosition());
			testChest->draw(*pWindow);
			testChest->DrawHint(*pWindow);
			
			//update and draw npcs
			for (int i = 0; i < npcVector.size(); i++)
			{
				npcVector.at(i)->Update(p->getPosition());
				window.draw(*npcVector.at(i));
				npcVector.at(i)->draw(window);
			}
			
			p->draw(*pWindow);


			//draw hints based on time(fade in/out) on the default view so they are not affected by other views
			window.setView(window.getDefaultView());
			
			hud->Draw(window);
			hud->Update(testQuest->getCurrentStage()->getObjective(), testInv->CheckQuantity(testInv->i_gems.key, false), testQuest->getCurrentStage()->getObjectiveLocation(), p->getPosition());

			if (testQuest->getCompletionStatus() == false)
				hud->Update(testQuest->getCurrentStage()->getObjective(), testInv->CheckQuantity(testInv->i_gems.key, false), testQuest->getCurrentStage()->getObjectiveLocation(), p->getPosition());
			else hud->Update("No active quest", testInv->CheckQuantity(testInv->i_gems.key, false), sf::Vector2f(0,0), p->getPosition());

			if (splashClock->getElapsedTime().asSeconds() > 0.5 && splashClock->getElapsedTime().asSeconds() < 1)
				moveHintSprite.setColor(sf::Color(255, 255, 255, 200));
			else if (splashClock->getElapsedTime().asSeconds() > 1 && splashClock->getElapsedTime().asSeconds() < 1.5)
				moveHintSprite.setColor(sf::Color(255, 255, 255, 150));
			else if (splashClock->getElapsedTime().asSeconds() > 1.5 && splashClock->getElapsedTime().asSeconds() < 2)
				moveHintSprite.setColor(sf::Color(255, 255, 255, 100));
			else if (splashClock->getElapsedTime().asSeconds() > 2 && splashClock->getElapsedTime().asSeconds() < 2.5)
				moveHintSprite.setColor(sf::Color(255, 255, 255, 50));
			else if (splashClock->getElapsedTime().asSeconds() > 2.5 && splashClock->getElapsedTime().asSeconds() < 3)
				moveHintSprite.setColor(sf::Color(255, 255, 255, 0));

			if (splashClock->getElapsedTime().asSeconds() > 3 && splashClock->getElapsedTime().asSeconds() < 4.5)
				objective.setColor(sf::Color(0, 0, 0, 200));
			else if (splashClock->getElapsedTime().asSeconds() > 4.5 && splashClock->getElapsedTime().asSeconds() < 6)
				objective.setColor(sf::Color(0, 0, 0, 100));
			else if (splashClock->getElapsedTime().asSeconds() > 6 && splashClock->getElapsedTime().asSeconds() < 7.5)
				objective.setColor(sf::Color(0, 0, 0, 0));

			if (splashClock->getElapsedTime().asSeconds() < 3 && testQuest->getCompletionStatus() == false)
				window.draw(moveHintSprite);
			else if (splashClock->getElapsedTime().asSeconds() > 3 && splashClock->getElapsedTime().asSeconds() < 8 && testQuest->getCompletionStatus() == false)
				window.draw(objective);

			if (testQuest->getCompletionStatus() == true)
			{
				window.draw(questCompletePopup);

				if (splashClock->getElapsedTime().asSeconds() > 1.5 && splashClock->getElapsedTime().asSeconds() < 3)
					questCompletePopup.setColor(sf::Color(0, 0, 0, 200));
				else if (splashClock->getElapsedTime().asSeconds() > 3 && splashClock->getElapsedTime().asSeconds() < 4.5)
					questCompletePopup.setColor(sf::Color(0, 0, 0, 100));
				else if (splashClock->getElapsedTime().asSeconds() > 4.5 && splashClock->getElapsedTime().asSeconds() < 6)
					questCompletePopup.setColor(sf::Color(0, 0, 0, 0));
			}

			//drawing the minimap
			window.setView(minimap);
			minimap.setCenter(p->getPosition());
			window.draw(lowPolyMap);
			testChest->draw(*pWindow);
			
			//draw npcs on minimap
			for (int i = 0; i < npcVector.size(); i++)
			{
				npcVector.at(i)->MinimapDraw(*pWindow);
			}

			p->MinimapDraw(*pWindow);


			break;

		case COMBAT:

			break;

		case CONVERSATION:

			break;

		case INVENTORY:
			window.setView(window.getDefaultView());
			testInv->Draw(window);
			if (useController == true)
			{
				gamepad->CheckAllButtons();
				if (gamepad->Back())
					gState = GAME;
			}
			else if (useController == false)
			{
				if(sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
					gState = GAME;
			}
			questCompletePopup.setColor(sf::Color(0, 0, 0, 0));
			break;

		case CREDITS:

			break;
		}


	

		

		 // Finally, display rendered frame on screen 
		window.display();
	} //loop back for next frame

	return EXIT_SUCCESS;
}