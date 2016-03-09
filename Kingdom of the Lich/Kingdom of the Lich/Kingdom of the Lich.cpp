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
	//load a font
	sf::Font font;
	font.loadFromFile("Assets/Kelt Caps Freehand.TTF");

	// Create the main window 
	sf::RenderWindow window(sf::VideoMode(sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height, 32), "Kingdom of the Lich");// , sf::Style::Fullscreen);
	std::cout << sf::VideoMode::getDesktopMode().width << ", " << sf::VideoMode::getDesktopMode().height << std::endl;
	sf::RenderWindow *pWindow = &window;

	int screenW = sf::VideoMode::getDesktopMode().width;
	int screenH = sf::VideoMode::getDesktopMode().height;

	/* initialize random seed: */
	srand(time(NULL));
	AreaManager* areaManager = new AreaManager(font, screenW, screenH);
	enum Areas
	{
		TUTORIAL,
		SEWER,
		LellesQualityMerchandise,
		House1,
		House2,
		TheDrunkenDragonInn
	};
	int currentArea = areaManager->GetCurrentArea();

	//Door* sewerHatch = new Door(0, sf::Vector2f(1100, 1000), false, 1);
	//Door* sewerExit = new Door(1, sf::Vector2f(1300, 200), true, 0, 69);
	/*Door* generalStoreDoor = new Door(2, sf::Vector2f(500, 300), true, 2,69);*/

	//Door* houseOneDoor = new Door(1, sf::Vector2f(700, 350), true);
	//Door* houseTwoDoor = new Door(1, sf::Vector2f(900, 350), true);
	//each area should have its own door there?

	//https://github.com/edoren/STP
	tmx::TileMap tutorialAreaMap("Assets/tutorialArea.tmx");
	tmx::TileMap tutorialAreaLowPolyMap("Assets/lowPolyTutorialArea.tmx");

	tmx::TileMap sewerAreaMap("Assets/50x50SewerArea.tmx");

	tmx::TileMap generalStoreMap("Assets/generalStore1.tmx");
	tmx::TileMap houseOne("Assets/house1.tmx");
	tmx::TileMap houseTwo("Assets/house2.tmx");
	tmx::TileMap pubOne("Assets/pub1.tmx");

	//Area area("Assets/tutorialArea.tmx", "", "Assets/npcList.xml", "");
	//map.ShowObjects(); // Display all the layer objects.

	//tmx::ObjectGroup collisionGroup = map.GetObjectGroup("Collision");

	//for (int i = 0; i < collisionGroup.objects_.size(); i++)
	//{
	//	std::string test = collisionGroup.objects_[i].GetPropertyValue("x");
	//}
	//std::cout<<"object 0 x: " << collisionGroup.objects_[0].GetPropertyValue("x") << std::endl;
	//map.GetLayer("World").visible = false; // Hide a Layer named World

	//create sf::View
	sf::View player_view(sf::FloatRect(0, 0, window.getSize().x, window.getSize().y));
	//player_view.zoom(1.5f);
	//Set it to be size of window
	player_view.setViewport(sf::FloatRect(0, 0, 1, 1));
	player_view.zoom(.36);

	//minimap
	bool showMinimap = true;
	unsigned int size = 130;//100
	sf::View minimap(sf::FloatRect(player_view.getCenter().x, player_view.getCenter().y, size, window.getSize().y*size / window.getSize().x));
	if (screenW == 1366 && screenH == 768)
	{
		//change the viewport to change the maps size
		minimap.setViewport(sf::FloatRect(0.12f - (1.f*minimap.getSize().x) / window.getSize().x - 0.002f, 0.14f - (1.f*minimap.getSize().y) / window.getSize().y - 0.004f, (2.f*minimap.getSize().x) / window.getSize().x, (2.f*minimap.getSize().y) / (window.getSize().y)));
	}
	else if (screenW == 1600 && screenH == 900)
	{
		//change the viewport to change the maps size
		minimap.setViewport(sf::FloatRect(0.12f - (1.f*minimap.getSize().x) / window.getSize().x - 0.0195f, 0.14f - (1.f*minimap.getSize().y) / window.getSize().y - 0.02f, (2.f*minimap.getSize().x) / window.getSize().x, (2.f*minimap.getSize().y) / (window.getSize().y)));
	}
	minimap.zoom(6.f);//4......3(actual)



	//Player is created here(race,gender and maybe class will be set later)
	Player* p = new Player(font);
	Hud* hud = new Hud(font, screenW, screenH, sf::Vector2f((0.12f - (1.f*minimap.getSize().x) / window.getSize().x - 0.002f)+17, (0.14f - (1.f*minimap.getSize().y) / window.getSize().y - 0.004f)+20), sf::Vector2f(minimap.getSize().x/2.7, minimap.getSize().y/2.55));

	//window.setFramerateLimit(60);//is this causing the flickering in the mini map? yes, the alternative?
	window.setVerticalSyncEnabled(true);

	//text by cooltext.com
	//splash screen
	SplashScreen* splashScreen = new SplashScreen(sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height);

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
	int prevState = SPLASH;

	std::cout << "Current game state: " << gState << std::endl;

	Gamepad* gamepad = new Gamepad();
	useController = gamepad->CheckControllerConnection(true);

	Menu *mainMenu = new Menu(font, useController, screenW, screenH);

	ChooseRaceAndGenderMenu* raceAndGenderMenu = new ChooseRaceAndGenderMenu(font, useController, screenW, screenH);

	//hints for the splash screen
	sf::Sprite splashHintSprite;
	sf::Texture splashHintTexture;
	sf::Text splashHintText1;
	splashHintText1.setFont(font);
	splashHintText1.setString("Press");

	if (useController == true)//controller hints
	{
		splashHintTexture.loadFromFile("Assets/ControllerHints/startButtonHint.png");
		splashHintText1.setPosition(sf::Vector2f(screenW / 2-100, screenH - 175));
		ConfirmationDialogBox::GetInstance()->setShowControllerHints(true);
		ConfirmationDialogBox::GetInstance()->setScreenSizes(screenW, screenH);
	}
	else if (useController == false)//keyboard and mouse hints
	{
		splashHintTexture.loadFromFile("Assets/KeyboardAndMouseHints/spaceButtonHint.png");
		splashHintText1.setPosition(sf::Vector2f(screenW / 2.5, screenH - 175));
		ConfirmationDialogBox::GetInstance()->setShowControllerHints(false);
		ConfirmationDialogBox::GetInstance()->setScreenSizes(screenW, screenH);
	}

	ConfirmationDialogBox::GetInstance()->setElementsOptions();
	ConfirmationDialogBox::GetInstance()->setHints();

	splashHintSprite.setTexture(splashHintTexture);
	splashHintSprite.setOrigin(sf::Vector2f(splashHintTexture.getSize().x / 2, splashHintTexture.getSize().y / 2));
	splashHintSprite.setPosition(sf::Vector2f(screenW / 2, screenH - 150));

	bool spacePressed = false;
	bool enterPressed = false;
	int enterCount = 0;


	//for testing inventory
	Inventory* testInv = new Inventory(font, useController, screenW, screenH);
	testInv->PrintAllInventory();
	testInv->AddItemToInventory(testInv->i_gems.key, 5);

	//testing chest
	Chest* testChest = new Chest(testInv->i_healthPotion.key, 3);
	testChest->LoadInteractHintTexture(useController);

	bool showQuestComplete = false;

	AudioManager* audioManager = new AudioManager();
	//play the first song
	audioManager->PlayMusicById(0);

	//npcs :)
	/*std::vector<Npc*> npcVector;*/

	//xml_document<> doc;
	//std::ifstream file("Assets/npcList.xml");
	//std::stringstream buffer;
	//buffer << file.rdbuf();
	//file.close();
	//std::string content(buffer.str());
	//doc.parse<0>(&content[0]);

	//xml_node<> *pRoot = doc.first_node();
	////std::cout << "Name of root node is: " << doc.first_node()->name() << "\n" << std::endl;

	//xml_node<>* npcList = doc.first_node("npcList");
	//xml_node<>* npc = npcList->first_node("npc");

	////load in each npc's information and then create them
	//while (npc != NULL)
	//{
	//	//name, id, race, gender, texturePath, mapIconTexturePath, x, y, hasQuest, behaviour
	//	std::string name = "";
	//	int id = 0;
	//	std::string race = "";
	//	std::string gender = "";
	//	std::string texturePath = "";

	//	std::string idleUpPath = "";
	//	std::string idleDownPath = "";
	//	std::string idleLeftPath = "";
	//	std::string idleRightPath = "";

	//	int numberOfFrames = 0;

	//	std::string walkUpPath = "";
	//	std::string walkDownPath = "";
	//	std::string walkLeftPath = "";
	//	std::string walkRightPath = "";

	//	std::string mapIconTexturePath = "";
	//	float x = 0;
	//	float y = 0;
	//	std::string hasQuest = "";
	//	std::string interactable = "";
	//	std::string behaviour = "";

	//	/*Get the npc's name*/
	//	//std::cout << "Name: " << npc->first_attribute("name")->value() << std::endl;
	//	name = npc->first_attribute("name")->value();

	//	/*Get the npc's id*/
	//	//std::cout << "I.D: " << npc->first_node("id")->value() << std::endl;
	//	id = atoi(npc->first_node("id")->value());

	//	/*Get the npc's race*/
	//	//std::cout << "Race: " << npc->first_node("race")->value() << std::endl;
	//	race = npc->first_node("race")->value();

	//	/*Get the npc's gender*/
	//	//std::cout << "Gender: " << npc->first_node("gender")->value() << std::endl;
	//	gender = npc->first_node("gender")->value();

	//	/*get paths for idle sprites*/
	//	//std::cout << "Idle up path: " << npc->first_node("idleUpPath")->value() << std::endl;
	//	idleUpPath = npc->first_node("idleUpPath")->value();

	//	//std::cout << "Idle down path: " << npc->first_node("idleDownPath")->value() << std::endl;
	//	idleDownPath = npc->first_node("idleDownPath")->value();

	//	//std::cout << "Idle left path: " << npc->first_node("idleLeftPath")->value() << std::endl;
	//	idleLeftPath = npc->first_node("idleLeftPath")->value();

	//	//std::cout << "Idle right path: " << npc->first_node("idleRightPath")->value() << std::endl;
	//	idleRightPath = npc->first_node("idleRightPath")->value();

	//	/*Get the number of frames*/
	//	//std::cout << "Number of frames: " << npc->first_node("numberOfFrames")->value() << std::endl;
	//	numberOfFrames = atoi( npc->first_node("numberOfFrames")->value());

	//	/*get paths for walking sprites*/
	//	//std::cout << "Walk up path: " << npc->first_node("walkUpPath")->value() << std::endl;
	//	walkUpPath = npc->first_node("walkUpPath")->value();

	//	//std::cout << "Walk down path: " << npc->first_node("walkDownPath")->value() << std::endl;
	//	walkDownPath = npc->first_node("walkDownPath")->value();

	//	//std::cout << "Walk left path: " << npc->first_node("walkLeftPath")->value() << std::endl;
	//	walkLeftPath = npc->first_node("walkLeftPath")->value();

	//	//std::cout << "Walk right path: " << npc->first_node("walkRightPath")->value() << std::endl;
	//	walkRightPath = npc->first_node("walkRightPath")->value();

	//	/*minimap icon path*/
	//	//std::cout << "Map icon texture path: " << npc->first_node("mapIconTexturePath")->value() << std::endl;
	//	mapIconTexturePath = npc->first_node("mapIconTexturePath")->value();

	//	/*x position*/
	//	//std::cout << "X: " << npc->first_node("x")->value() << std::endl;
	//	x = atof(npc->first_node("x")->value());

	//	/*y position*/
	//	//std::cout << "Y: " << npc->first_node("y")->value() << std::endl;
	//	y = atof(npc->first_node("y")->value());

	//	/*Does the npc have a quest for the player*/
	//	//std::cout << "Has quest: " << npc->first_node("hasQuest")->value() << std::endl;
	//	hasQuest = npc->first_node("hasQuest")->value();

	//	/*Can the npc be interacted with?*/
	//	//std::cout << "Interactable: " << npc->first_node("interact")->value() << std::endl;
	//	interactable = npc->first_node("interact")->value();

	//	/*What behaviour do they have? e.g: wander, stand etc*/
	//	//std::cout << "Behaviour: " << npc->first_node("behaviour")->value() << std::endl;
	//	behaviour = npc->first_node("behaviour")->value();

	//	/*Create the npc*/
	//	Npc* n = new Npc(name, id, idleUpPath, idleDownPath, idleLeftPath, idleRightPath, numberOfFrames, walkUpPath, walkDownPath, walkLeftPath, walkRightPath, mapIconTexturePath, sf::Vector2f(x, y), hasQuest, interactable, behaviour, useController);
	//	npcVector.push_back(n);
	//	//std::cout << "Size of npcVector: " << npcVector.size() << std::endl;

	//	std::cout << "------------------------------------------------------------" << std::endl;
	//	/*Move onto the next npc tag*/
	//	npc = npc->next_sibling("npc");
	//}
	//houses
	//CollidableObject* house1 = new CollidableObject(500, 1050, 100, 100, true, false);
	//CollidableObject* house2 = new CollidableObject(500, 250, 100, 100, true, false);
	//CollidableObject* house3 = new CollidableObject(650, 250, 100, 100, true, false);
	//CollidableObject* house4 = new CollidableObject(800, 250, 100, 100, true, false);
	//CollidableObject* house5 = new CollidableObject(950, 250, 100, 100, true, false);
	//CollidableObject* house6 = new CollidableObject(1100, 250, 100, 100, true, false);
	//CollidableObject* house7 = new CollidableObject(1250, 250, 100, 100, true, false);
	//CollidableObject* house8 = new CollidableObject(1400, 250, 100, 100, true, false);
	////walls
	//CollidableObject* wall1 = new CollidableObject(300, 200, 1400, 50, true, false);
	//CollidableObject* wall2 = new CollidableObject(200, 300, 50, 1400, true, false);
	//CollidableObject* wall3 = new CollidableObject(300, 1750, 1400, 50, true, false);
	//CollidableObject* wall4 = new CollidableObject(1750, 300, 50, 1400, true, false);
	////towers
	//CollidableObject* tower1 = new CollidableObject(200, 200, 100, 100, true, false);
	//CollidableObject* tower2 = new CollidableObject(1700, 200, 100, 100, true, false);
	//CollidableObject* tower3 = new CollidableObject(200, 1700, 100, 100, true, false);
	//CollidableObject* tower4 = new CollidableObject(1700, 1700, 100, 100, true, false);
	////forge
	//CollidableObject* forge = new CollidableObject(350, 1000, 100, 100, true, false);
	////anvil
	//CollidableObject* anvil = new CollidableObject(363, 900, 20, 50, true, false);

	//std::vector<CollidableObject*> collidableObjects;
	//collidableObjects.push_back(house1);
	//collidableObjects.push_back(house2);
	//collidableObjects.push_back(house3);
	//collidableObjects.push_back(house4);
	//collidableObjects.push_back(house5);
	//collidableObjects.push_back(house6);
	//collidableObjects.push_back(house7);
	//collidableObjects.push_back(house8);

	//collidableObjects.push_back(wall1);
	//collidableObjects.push_back(wall2);
	//collidableObjects.push_back(wall3);
	//collidableObjects.push_back(wall4);

	//collidableObjects.push_back(tower1);
	//collidableObjects.push_back(tower2);
	//collidableObjects.push_back(tower3);
	//collidableObjects.push_back(tower4);

	//collidableObjects.push_back(forge);

	//collidableObjects.push_back(anvil);

	bool debugMode = true;

	//testing quest
	Quest* testQuest = new Quest(2, "Learn how chests work", "Commander Iron-Arm", sf::Vector2f(1000,1000), 1, 5, 5);

	Enemy* testEnemy = new Enemy("Assets/trainingTarget.png", 100, 20, 0, sf::Vector2f(800, 1600));

	CombatMenu* combatMenu = new CombatMenu(font, "Assets/trainingTarget.png", screenW, screenH);

	DamageCalculator* damageCalc = new DamageCalculator();

	//played the splash screen sound effect?
	bool playedSplashSound = false;

	Credits* credits = new Credits(screenW, screenH);

	PopupMessageHandler popupMessageHandler = PopupMessageHandler(font);

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

			if ((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::T))
				debugMode = !debugMode;

			if ((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::M))
				showMinimap = !showMinimap;

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

#pragma region SplashScreen
		case SPLASH:
			splashScreen->Update();
			splashScreen->Draw(window);
			window.draw(splashHintSprite);
			window.draw(splashHintText1);

			//flash the hint
			if (splashClock->getElapsedTime().asSeconds() > 1 && splashClock->getElapsedTime().asSeconds() < 2)
			{
				splashHintSprite.setColor(sf::Color::Transparent);
				splashHintText1.setColor(sf::Color::Transparent);
			}
			else if (splashClock->getElapsedTime().asSeconds() > 2)
			{
				splashHintSprite.setColor(sf::Color::White);
				splashHintText1.setColor(sf::Color::White);
				splashClock->restart();
			}

			if (splashScreen->isSummoned() && playedSplashSound == false)
			{
				audioManager->PlaySoundEffectById(7, true);
				playedSplashSound = true;
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
					prevState = gState;
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
#pragma endregion


#pragma region MainMenu
		case MAINMENU:
			mainMenu->Draw(window);
			audioManager->FadeOutSound(7);
			//if the player is using keyboard and mouse
			if (useController == false)
			{
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

				//which option is the player choosing
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return) && enterPressed == false)
				{
					enterPressed = true;
					audioManager->PlaySoundEffectById(2, true);
					if (mainMenu->getSelectedOption() == 0)//new game
					{
						enterPressed = false;
						//audioManager->PlaySoundEffectById(0, true);
						prevState = gState;
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
						prevState = gState;
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
						//audioManager->PlaySoundEffectById(0, true);
						prevState = gState;
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
						prevState = gState;
						gState = CREDITS;
					}
					else if (mainMenu->getSelectedOption() == 4)//quit
					{
						window.close();
					}
				}
			}
			break;
#pragma endregion


#pragma region ChooseRaceAndGender
		case CHOOSERACEGENDER:
			audioManager->StopMusic(0);

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
								prevState = gState;
								gState = GAME;
								popupMessageHandler.AddCustomMessage("TUTORIAL", sf::Vector2f(screenW / 2.3, 50), 25, sf::Color::Black);
								p->setTextures();
								std::cout << "Race: " << p->getRace() << ", " << "Gender: " << p->getGender() << std::endl;
								splashClock->restart();
								audioManager->PlaySoundEffectById(2, true);
								audioManager->PlayMusicById(1);
								popupMessageHandler.AddCustomMessage("Go and talk to Commander Iron-Arm. Use your compass to find him.", sf::Vector2f(screenW / 5, screenH / 3), 5, sf::Color::Black);
								popupMessageHandler.AddPreBuiltMessage(1, sf::Vector2f(screenW / 2, screenH / 4), 5);
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
								popupMessageHandler.AddCustomMessage("Go and talk to Commander Iron-Arm. Use your compass to find him.", sf::Vector2f(screenW / 18, screenH / 4), 5, sf::Color::Black);
								prevState = gState;
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
								prevState = gState;
								gState = GAME;
								popupMessageHandler.AddCustomMessage("TUTORIAL", sf::Vector2f(screenW / 2.3, 50), 25, sf::Color::White);
								p->setTextures();
								std::cout << "Race: " << p->getRace() << ", " << "Gender: " << p->getGender() << std::endl;
								splashClock->restart();
								audioManager->PlaySoundEffectById(2, true);
								audioManager->PlayMusicById(1);
								popupMessageHandler.AddCustomMessage("Go and talk to Commander Iron-Arm. Use your compass to find him.", sf::Vector2f(screenW / 5, screenH / 3), 5, sf::Color::Black);
								popupMessageHandler.AddPreBuiltMessage(1, sf::Vector2f(screenW / 2, screenH / 4), 2);
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
								popupMessageHandler.AddCustomMessage("Go and talk to Commander Iron-Arm. Use your compass to find him.", sf::Vector2f(screenW / 18, screenH / 4), 5, sf::Color::Black);
								prevState = gState;
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
#pragma endregion


		case CHOOSECLASS:

			break;

#pragma region Game
		case GAME:
			popupMessageHandler.UpdateMessages();
			
			audioManager->FadeOutSound(0);
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
				

				//temporarily remove(or maybe permanently)
				//move with d-pad
				//if (gamepad->DpadUp() && p->IsColliding() == false)
				//	p->Move(0);
				//else if (gamepad->DpadDown() && p->IsColliding() == false)
				//	p->Move(1);
				//else if (gamepad->DpadRight() && p->IsColliding() == false)
				//	p->Move(2);
				//else if (gamepad->DpadLeft() && p->IsColliding() == false)
				//	p->Move(3);
				//else p->setCurrentDirection(4);

				//move with analog sticks
				if (gamepad->getNormalisedLeftStickAxis().x > 0.9f && gamepad->isLeftAxisOutOfDeadzone() == true && p->IsColliding() == false)
					p->Move(2);
				else if (gamepad->getNormalisedLeftStickAxis().x < -0.9f && gamepad->isLeftAxisOutOfDeadzone() == true && p->IsColliding() == false)
					p->Move(3);
				else if (gamepad->getNormalisedLeftStickAxis().y > 0.9f && gamepad->isLeftAxisOutOfDeadzone() == true && p->IsColliding() == false)
					p->Move(0);
				else if (gamepad->getNormalisedLeftStickAxis().y < -0.9f && gamepad->isLeftAxisOutOfDeadzone() == true && p->IsColliding() == false)
					p->Move(1);
				else p->setCurrentDirection(4);

				//access inventory
				if (gamepad->B())
				{
					//testInv->OpenInventory();
					prevState = gState;
					gState = INVENTORY;
					audioManager->PlaySoundEffectById(3, true);
				}

				//check for collision between player and chest and update quest
				if (p->getGlobalBounds().intersects(testChest->getGlobalBounds()) && areaManager->GetCurrentArea() == TUTORIAL)
				{
					if (gamepad->A() == true)
					{
						if (testChest->getOpened() == false)
						{
							if (testQuest->getCurrentStageIndex() == 1)
							{
								testChest->OpenChest(testInv);
								testQuest->getCurrentStage()->setCompletionStatus(true);
								//testQuest->setCompletionStatus(true);
								testQuest->setCurrentStageIndex(2);
								//std::cout << "You completed your first quest!" << std::endl;
								splashClock->restart();
								audioManager->PlaySoundEffectById(4, true);
								if (useController)
									popupMessageHandler.AddCustomMessage("Objective complete. You got 3 potions from the chest. Press 'B' now.", sf::Vector2f(screenW / 6, screenH / 4), 5, sf::Color::Black);
								else popupMessageHandler.AddCustomMessage("Objective complete. You got 3 potions from the chest. Press 'I' now.", sf::Vector2f(screenW / 6, screenH / 4), 5, sf::Color::Black);
							}
							else
							{
								std::cout << "You may not open this chest right now." << std::endl;
								audioManager->PlaySoundEffectById(5, true);
							}
						}
						else std::cout << "This chest has already been opened. There is nothing in it." << std::endl;
					}
					p->setCollidingStatus(true);
					//get the distance between the player and the thing they hit
					float distance = sqrtf((((p->getPosition().x - testChest->getPosition().x)*(p->getPosition().x - testChest->getPosition().x))
						+ ((p->getPosition().y - testChest->getPosition().y)*(p->getPosition().y - testChest->getPosition().y))));
					//get the direction between them
					sf::Vector2f dir = sf::Vector2f((p->getPosition().x - testChest->getPosition().x) / distance,
						(p->getPosition().y - testChest->getPosition().y) / distance);
					//move the player out of collision
					p->setPosition(sf::Vector2f(p->GetPreCollisionPosition().x + dir.x * 3, p->GetPreCollisionPosition().y + dir.y * 3));
				}
				else p->setCollidingStatus(false);

			}


			else//use keyboard
			{
					//check if running
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
					p->setIsRunning(true);
				else { p->setIsRunning(false); }

				if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && p->IsColliding() == false)//up
					p->Move(0);
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && p->IsColliding() == false)//down
					p->Move(1);
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && p->IsColliding() == false)//left
					p->Move(3);
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && p->IsColliding() == false)//right
					p->Move(2);
				else p->setCurrentDirection(4);

				if (sf::Keyboard::isKeyPressed(sf::Keyboard::I))
				{
					audioManager->PlaySoundEffectById(3, true);
					prevState = gState;
					gState = INVENTORY;
				}

				//check for collision between player and chest and update quest
				if (p->getGlobalBounds().intersects(testChest->getGlobalBounds()) && areaManager->GetCurrentArea() == TUTORIAL)// , testInv);
				{
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
					{
						if (testChest->getOpened() == false)
						{
							if (testQuest->getCurrentStageIndex() == 1)
							{
								testChest->OpenChest(testInv);
								testQuest->getCurrentStage()->setCompletionStatus(true);
								testQuest->setCurrentStageIndex(2);
								//testQuest->setCompletionStatus(true);
								//std::cout << "You completed your first quest!" << std::endl;
								if (useController)
									popupMessageHandler.AddCustomMessage("Objective complete. You got 3 potions from the chest. Press 'B' now.", sf::Vector2f(screenW / 6, screenH / 4), 5, sf::Color::Black);
								else popupMessageHandler.AddCustomMessage("Objective complete. You got 3 potions from the chest. Press 'I' now.", sf::Vector2f(screenW / 6, screenH / 4), 5, sf::Color::Black);
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
					p->setCollidingStatus(true);
					//get the distance between the player and the thing they hit
					float distance = sqrtf((((p->getPosition().x - testChest->getPosition().x)*(p->getPosition().x - testChest->getPosition().x))
						+ ((p->getPosition().y - testChest->getPosition().y)*(p->getPosition().y - testChest->getPosition().y))));
					//get the direction between them
					sf::Vector2f dir = sf::Vector2f((p->getPosition().x - testChest->getPosition().x) / distance,
						(p->getPosition().y - testChest->getPosition().y) / distance);
					//move the player out of collision
					p->setPosition(sf::Vector2f(p->GetPreCollisionPosition().x + dir.x * 3, p->GetPreCollisionPosition().y + dir.y * 3));
				
				}
				else
				{
					p->setCollidingStatus(false);
				}
			}
			if (areaManager->GetCurrentArea() == TUTORIAL)
				window.draw(tutorialAreaMap);
			else if (areaManager->GetCurrentArea() == SEWER)
				window.draw(sewerAreaMap);
			else if (areaManager->GetCurrentArea() == LellesQualityMerchandise)
				window.draw(generalStoreMap);
			else if (areaManager->GetCurrentArea() == House1)
				window.draw(houseOne);
			else if (areaManager->GetCurrentArea() == House2)
				window.draw(houseTwo);
			else if (areaManager->GetCurrentArea() == TheDrunkenDragonInn)
				window.draw(pubOne);
			
			//update the player
			p->Update();

			if (areaManager->GetCurrentArea() == TUTORIAL)
			{
				testChest->Update(p->getPosition());
				window.draw(*testChest);
				testChest->DrawHint(*pWindow);
				if (debugMode)
					testChest->DrawBoundingBox(window);
			}
			
			areaManager->CheckDoors(p->getPosition(), p->getGlobalBounds());

			if (areaManager->GetCurrentArea() == TUTORIAL)
			{
				//window.draw(*sewerHatch);
				//window.draw(*generalStoreDoor);
				if (areaManager->GetAreaToChangeTo() == SEWER && gamepad->A())//(sewerHatch->IsPlayerInDoorway(p->getPosition()) && gamepad->A() && sewerHatch->IsOpen())
				{
					audioManager->PlaySoundEffectById(9, false);
					audioManager->StopMusic(1);
					audioManager->PlayMusicById(2);
					areaManager->ChangeArea(SEWER);
					p->setPosition(1325, 275);
					testQuest->getCurrentStage()->setCompletionStatus(true);
					testQuest->setCompletionStatus(true);
				}

				else if (areaManager->GetAreaToChangeTo() == LellesQualityMerchandise && gamepad->A())// && generalStoreDoor->IsOpen())
				{
					audioManager->PlaySoundEffectById(9, false);
					audioManager->StopMusic(1);
					areaManager->ChangeArea(LellesQualityMerchandise);
					p->setPosition(415, 400);
				}

				else if (areaManager->GetAreaToChangeTo() == House1 && gamepad->A())// && generalStoreDoor->IsOpen())
				{
					audioManager->PlaySoundEffectById(9, false);
					audioManager->StopMusic(1);
					areaManager->ChangeArea(House1);
					p->setPosition(80, 300);
				}
				else if (areaManager->GetAreaToChangeTo() == House2 && gamepad->A())// && generalStoreDoor->IsOpen())
				{
					audioManager->PlaySoundEffectById(9, false);
					audioManager->StopMusic(1);
					areaManager->ChangeArea(House2);
					p->setPosition(80, 300);
				}
				else if (areaManager->GetAreaToChangeTo() == TheDrunkenDragonInn && gamepad->A())// && generalStoreDoor->IsOpen())
				{
					audioManager->PlaySoundEffectById(9, false);
					audioManager->StopMusic(1);
					areaManager->ChangeArea(TheDrunkenDragonInn);
					p->setPosition(250, 175);
				}
			}
			else if (areaManager->GetCurrentArea() == SEWER)
			{
				//window.draw(*sewerExit);
				if (areaManager->GetAreaToChangeTo() == TUTORIAL && gamepad->A())// && sewerExit->IsOpen())
				{
					audioManager->PlaySoundEffectById(9, false);
					audioManager->StopMusic(2);
					audioManager->PlayMusicById(1);
					areaManager->ChangeArea(TUTORIAL);
					p->setPosition(1100+50, 1000);
				}
			}
			else if (areaManager->GetCurrentArea() == LellesQualityMerchandise)
			{
				if (areaManager->GetAreaToChangeTo() == TUTORIAL && gamepad->A())// && sewerExit->IsOpen())
				{
					audioManager->PlaySoundEffectById(9, false);
					audioManager->StopMusic(2);
					audioManager->PlayMusicById(1);
					areaManager->ChangeArea(TUTORIAL);
					p->setPosition(500, 400);
				}
			}
			else if (areaManager->GetCurrentArea() == House1)
			{
				if (areaManager->GetAreaToChangeTo() == TUTORIAL && gamepad->A())// && sewerExit->IsOpen())
				{
					audioManager->PlaySoundEffectById(9, false);
					audioManager->StopMusic(2);
					audioManager->PlayMusicById(1);
					areaManager->ChangeArea(TUTORIAL);
					p->setPosition(600, 400);
				}
			}

			else if (areaManager->GetCurrentArea() == House2)
			{
				if (areaManager->GetAreaToChangeTo() == TUTORIAL && gamepad->A())// && sewerExit->IsOpen())
				{
					audioManager->PlaySoundEffectById(9, false);
					audioManager->StopMusic(2);
					audioManager->PlayMusicById(1);
					areaManager->ChangeArea(TUTORIAL);
					p->setPosition(600, 400);
				}
			}

			else if (areaManager->GetCurrentArea() == TheDrunkenDragonInn)
			{
				if (areaManager->GetAreaToChangeTo() == TUTORIAL && gamepad->A())// && sewerExit->IsOpen())
				{
					audioManager->PlaySoundEffectById(9, false);
					audioManager->StopMusic(2);
					audioManager->PlayMusicById(1);
					areaManager->ChangeArea(TUTORIAL);
					p->setPosition(530, 1200);
				}
			}

			areaManager->Update(p->getPosition());
			areaManager->Draw(window, debugMode);
			
			window.draw(*p);
			if (debugMode)
				p->DrawBoundingBox(window);

				if (areaManager->CheckPlayerCollidableObjectsCollisions(p->getGlobalBounds()))
				{
					p->setCollidingStatus(true);

					if (p->getCurrentDirection() == 0)//up
					{
						p->setPosition(p->getPosition().x, p->getPosition().y + 2);
					}
					else if (p->getCurrentDirection() == 1)//down
					{
						p->setPosition(p->getPosition().x, p->getPosition().y - 2);
					}
					else if (p->getCurrentDirection() == 2)//right
					{
						p->setPosition(p->getPosition().x - 2, p->getPosition().y);
					}
					else if (p->getCurrentDirection() == 3)//left
					{
						p->setPosition(p->getPosition().x + 2, p->getPosition().y);
					}


				}
				else p->setCollidingStatus(false);

				if (areaManager->CheckCollisionPlayerNpcs(p).first)
				{
					p->setCollidingStatus(true);
					//npcVector.at(i)->setColliding(true);

					if (areaManager->CheckCollisionPlayerNpcs(p).second == 0 && (sf::Keyboard::isKeyPressed(sf::Keyboard::E) || gamepad->A() == true))
					{
						if (testQuest->getCurrentStageIndex() == 0)
						{
							std::cout << "Go and open that chest and retrieve the items within. Walk up to it and press the 'E'" << std::endl;
							testQuest->getCurrentStage()->setCompletionStatus(true);
							testQuest->setCurrentStageIndex(1);
							if (useController)
								popupMessageHandler.AddCustomMessage("Go and open that chest and retrieve the items within. Walk up to it and press 'A'", sf::Vector2f(screenW / 6, screenH / 4), 5, sf::Color::Black);
							else popupMessageHandler.AddCustomMessage("Go and open that chest and retrieve the items within. Walk up to it and press 'E'", sf::Vector2f(screenW / 6, screenH / 4), 5, sf::Color::Black);

							popupMessageHandler.AddCustomMessage("Hold 'RT' to run", sf::Vector2f(screenW / 2.5, screenH / 3), 2, sf::Color::Black);
						}
						
					}

					//move the player out of collision
					if (areaManager->CheckCollisionPlayerNpcs(p).second != 2)
					{
						if (p->getCurrentDirection() == 0)//up
						{
							p->setPosition(p->getPosition().x, p->getPosition().y + 2);//2
						}
						else if (p->getCurrentDirection() == 1)//down
						{
							p->setPosition(p->getPosition().x, p->getPosition().y - 2);//2
						}
						else if (p->getCurrentDirection() == 2)//right
						{
							p->setPosition(p->getPosition().x - 2, p->getPosition().y);//2
						}
						else if (p->getCurrentDirection() == 3)//left
						{
							p->setPosition(p->getPosition().x + 2, p->getPosition().y);//2
						}
					}
				}
				else
				{
					p->setCollidingStatus(false);
					//npcVector.at(i)->setColliding(false);//this was causing the npcs to just ignore collisions!!!! need something along the line of this though to stop them getting stuck.
				}
			//}

			//player and enemy
			if (p->getGlobalBounds().intersects(testEnemy->getGlobalBounds()) && testEnemy->GetHealth() > 0 && areaManager->GetCurrentArea() == TUTORIAL)
			{
				p->setCollidingStatus(true);

				if ((sf::Keyboard::isKeyPressed(sf::Keyboard::E) || gamepad->A() == true) && testQuest->getCurrentStageIndex() == 2)
				{
					audioManager->StopMusic(1);
					audioManager->PlayMusicById(3);
					popupMessageHandler.AddCustomMessage("Fight this stone golem to complete your training!", sf::Vector2f(screenW / 4, 20), 1, sf::Color::Black);
					combatMenu->SetPlayerRepSprite(p->getRace(), p->getGender());
					prevState = gState;
					gState = COMBAT;
				}

				//move the player out of collision

				if (p->getCurrentDirection() == 0)//up
				{
					p->setPosition(p->getPosition().x, p->getPosition().y + 3);
				}
				else if (p->getCurrentDirection() == 1)//down
				{
					p->setPosition(p->getPosition().x, p->getPosition().y - 3);
				}
				else if (p->getCurrentDirection() == 2)//right
				{
					p->setPosition(p->getPosition().x - 3, p->getPosition().y);
				}
				else if (p->getCurrentDirection() == 3)//left
				{
					p->setPosition(p->getPosition().x + 3, p->getPosition().y);
				}
			}
			else
			{
				p->setCollidingStatus(false);
			}
			
			if (testEnemy->GetHealth() > 0 && areaManager->GetCurrentArea() == TUTORIAL)
			{
				window.draw(*testEnemy);
				if (debugMode)
					testEnemy->DrawBoundingBox(window);
			}

			//draw hints based on time(fade in/out) on the default view so they are not affected by other views
			window.setView(window.getDefaultView());
			popupMessageHandler.DrawMessages(*pWindow);
			
			hud->Draw(window);
			areaManager->DrawCurrentAreaText(window);
			//hud->Update(testQuest->getCurrentStage()->getObjective(), testInv->CheckQuantity(testInv->i_gems.key, false), testQuest->getCurrentStage()->getObjectiveLocation(), p->getPosition(), showMinimap);

			if (testQuest->getCompletionStatus() == false)
				hud->Update(testQuest->getCurrentStage()->getObjective(), testInv->CheckQuantity(testInv->i_gems.key, false), testQuest->getCurrentStage()->getObjectiveLocation(), p->getPosition(), showMinimap, p->getHealth());
			else hud->Update("No active quest", testInv->CheckQuantity(testInv->i_gems.key, false), sf::Vector2f(0,0), p->getPosition(), showMinimap, p->getHealth());

			//if (gamepad->Back())
			//{
			//	showMinimap = !showMinimap;
			//}

			//drawing the minimap
			if (showMinimap)
			{
				window.setView(minimap);
				minimap.setCenter(p->getPosition());

				if (areaManager->GetCurrentArea() == TUTORIAL)
					window.draw(tutorialAreaLowPolyMap);//do I need this? or could I make something nicer to show
				else if (areaManager->GetCurrentArea() == SEWER)
				{
					window.draw(sewerAreaMap);
					//window.draw(*sewerExit);
				}
				if (areaManager->GetCurrentArea() == TUTORIAL)
				{
					window.draw(*testChest);
					//window.draw(*sewerHatch);
					//window.draw(*generalStoreDoor);
				}
				if (testEnemy->GetHealth() > 0 && areaManager->GetCurrentArea() == TUTORIAL)
					testEnemy->MinimapDraw(window);

				areaManager->MinimapDraw(window);

				p->MinimapDraw(*pWindow);
			}


			break;
#pragma endregion


#pragma region Combat
		case COMBAT:
			window.setView(window.getDefaultView());

			popupMessageHandler.UpdateMessages();

			if (popupMessageHandler.GetActiveMessageCount() == 0 && combatMenu->GetTurnCount() == 0)
				combatMenu->SetPlayersTurn(true);

			testEnemy->Update();

			if (!combatMenu->IsPlayersTurn() && combatMenu->GetTurnCount() > 0 && popupMessageHandler.GetActiveMessageCount() == 0)
			{
				popupMessageHandler.AddCustomMessage(testEnemy->TakeTurn(p), sf::Vector2f(screenW / 2.5, screenH/2.5), 0.7, sf::Color::Red);

				int soundCoin = rand() % 2;
				if (soundCoin == 0)
					audioManager->PlaySoundEffectById(14, false);
				else audioManager->PlaySoundEffectById(15, false);

				combatMenu->SetPlayersTurn(true);
				combatMenu->IncrementTurnCount();
			}

			if (useController == true)//if we are using a controller
			{
				gamepad->CheckAllButtons();

				if (combatMenu->GetCurrentMenuState() == 0 && combatMenu->IsPlayersTurn() && popupMessageHandler.GetActiveMessageCount() == 0)
				{
					if (gamepad->DpadRight() == true || (gamepad->getNormalisedLeftStickAxis().x > 0.9f && gamepad->isLeftAxisOutOfDeadzone() == true))
					{
						if (combatMenu->getCanMove() == true)
						{
							audioManager->PlaySoundEffectById(1, false);
							combatMenu->MoveSelectionRight();
							combatMenu->setCanMove(false);
						}
					}

					else if (gamepad->DpadLeft() == true || (gamepad->getNormalisedLeftStickAxis().x < -0.9f && gamepad->isLeftAxisOutOfDeadzone() == true))
					{
						if (combatMenu->getCanMove() == true)
						{
							audioManager->PlaySoundEffectById(1, false);
							combatMenu->MoveSelectionLeft();
							combatMenu->setCanMove(false);
						}
					}

					else combatMenu->setCanMove(true);
				}

				else if ((combatMenu->GetCurrentMenuState() == 1 || combatMenu->GetCurrentMenuState() == 2) && combatMenu->IsPlayersTurn() && popupMessageHandler.GetActiveMessageCount() == 0)
				{
					if (gamepad->DpadDown() == true || (gamepad->getNormalisedLeftStickAxis().y < -0.9f && gamepad->isLeftAxisOutOfDeadzone() == true))
					{
						if (combatMenu->getCanMove() == true)
						{
							audioManager->PlaySoundEffectById(1, false);
							combatMenu->MoveSelectionDown();
							combatMenu->setCanMove(false);
						}
					}

					else if (gamepad->DpadUp() == true || (gamepad->getNormalisedLeftStickAxis().y > 0.9f && gamepad->isLeftAxisOutOfDeadzone() == true))
					{
						if (combatMenu->getCanMove() == true)
						{
							audioManager->PlaySoundEffectById(1, false);
							combatMenu->MoveSelectionUp();
							combatMenu->setCanMove(false);
						}
					}

					else combatMenu->setCanMove(true);
				}

				if (combatMenu->GetCurrentMenuState() != 0 && combatMenu->IsPlayersTurn() && popupMessageHandler.GetActiveMessageCount() == 0)
				{
					if (gamepad->B())
					{
						if (combatMenu->GetCurrentMenuState() == 1)
						{
							combatMenu->SetSelectorPosition(sf::Vector2f(screenW / 4.7, screenH - 100));
						}
						else if (combatMenu->GetCurrentMenuState() == 2)
						{
							combatMenu->SetSelectorPosition(sf::Vector2f(screenW / 1.8, screenH - 100));
						}

						combatMenu->SetCurrentMenuState(0);
					}
				}

				if (gamepad->A() == true && combatMenu->IsPlayersTurn() && popupMessageHandler.GetActiveMessageCount() == 0)
				{
					//audioManager->PlaySoundEffectById(2, true);
					

						if (combatMenu->GetCurrentMenuState() == 0)
						{
							if (combatMenu->getCurrentAction() == 0)//we are now choosing to attack
							{
								combatMenu->SetCurrentMenuState(1);
								combatMenu->SetSelectorPosition(sf::Vector2f(screenW / 5, screenH / 16.3));//325, 45
							}
							else if (combatMenu->getCurrentAction() == 1)//we are now choosing to use an item
							{
								//combatMenu->SetCurrentMenuState(2);
								prevState = gState;
								gState = INVENTORY;
								testInv->setCurrentlySelectedItem(0);
								combatMenu->SetCurrentMenuState(0);
								combatMenu->SetSelectorPosition(sf::Vector2f(screenW / 4.7, screenH - 100));

								combatMenu->SetPlayersTurn(false);
								combatMenu->IncrementTurnCount();
								//combatMenu->SetSelectorPosition(sf::Vector2f(screenW / 3, screenH / 16.3));//525, 45
							}
							else if (combatMenu->getCurrentAction() == 2)//we are now choosing to flee
							{
								combatMenu->setCombatOver(true);
							}
						}
						else if (combatMenu->GetCurrentMenuState() == 1 && combatMenu->getCanSelect() == true)
						{
							
							if (combatMenu->getCurrentOption() == 0)
							{
								audioManager->PlaySoundEffectById(10, false);
								popupMessageHandler.AddCustomMessage("You stab the golem!", sf::Vector2f(screenW / 2.5, screenH / 2.5), 0.7, sf::Color::Blue);
								testEnemy->setHealth(testEnemy->GetHealth() - 15);
							}
							else if (combatMenu->getCurrentOption() == 1)
							{
								audioManager->PlaySoundEffectById(11, false);
								popupMessageHandler.AddCustomMessage("You chop at the golem!", sf::Vector2f(screenW / 2.5, screenH/2.5), 0.7, sf::Color::Blue);
								testEnemy->setHealth(testEnemy->GetHealth() - 20);
							}
							else if (combatMenu->getCurrentOption() == 2)
							{
								audioManager->PlaySoundEffectById(12, false);
								popupMessageHandler.AddCustomMessage("You slice the golem!", sf::Vector2f(screenW / 2.5, screenH / 2.5), 0.7, sf::Color::Blue);
								testEnemy->setHealth(testEnemy->GetHealth() - 25);
							}
							combatMenu->SetCurrentMenuState(0);
							combatMenu->SetSelectorPosition(sf::Vector2f(screenW / 4.7, screenH - 100));
							
							combatMenu->SetPlayersTurn(false);
							combatMenu->IncrementTurnCount();

						}
						else if (combatMenu->GetCurrentMenuState() == 2 && combatMenu->getCanSelect() == true)
						{

						}

						combatMenu->setCanSelect(false);
					}
				else combatMenu->setCanSelect(true);
			}
			

			else//we are using a keyboard
			{
				if (combatMenu->GetCurrentMenuState() == 0 && combatMenu->IsPlayersTurn())
				{
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
					{
						if (combatMenu->getCanMove() == true)
						{
							audioManager->PlaySoundEffectById(1, false);
							combatMenu->MoveSelectionRight();
							combatMenu->setCanMove(false);
						}
					}

					else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
					{
						if (combatMenu->getCanMove() == true)
						{
							audioManager->PlaySoundEffectById(1, false);
							combatMenu->MoveSelectionLeft();
							combatMenu->setCanMove(false);
						}
					}

					else combatMenu->setCanMove(true);
				}

				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return) && combatMenu->IsPlayersTurn())
				{
					audioManager->PlaySoundEffectById(2, true);

					if (combatMenu->GetCurrentMenuState() == 0)
					{
						if (combatMenu->getCurrentAction() == 0)//we are now choosing to attack
						{
							combatMenu->SetCurrentMenuState(1);
							combatMenu->SetSelectorPosition(sf::Vector2f(325, 45));
						}
						else if (combatMenu->getCurrentAction() == 1)//we are now choosing to item
						{
							combatMenu->SetCurrentMenuState(2);
							combatMenu->SetSelectorPosition(sf::Vector2f(525, 45));
						}
						else if (combatMenu->getCurrentAction() == 2)//we are no choosing to flee
						{
							combatMenu->setCombatOver(true);
						}
					}
				}
			}

			if (testEnemy->GetHealth() <= 0)
			{
				combatMenu->setCombatOver(true);
				audioManager->PlaySoundEffectById(6, true);
			}

			if (p->getHealth() <= 0)
			{
				combatMenu->setCombatOver(true);
				audioManager->PlaySoundEffectById(13, true);
			}

			if (combatMenu->IsCombatOver() == true)//if combat is over
			{
				combatMenu->setCombatOver(false);
				testQuest->getCurrentStage()->setCompletionStatus(true);
				testQuest->setCurrentStageIndex(3);
				//sewerHatch->SetOpen(true);
				if(p->getHealth() > 0)
					popupMessageHandler.AddCustomMessage("Go to the sewers.", sf::Vector2f(screenW / 3, screenH / 4), 5, sf::Color::White);
				else
				{
					popupMessageHandler.AddCustomMessage("You were beaten! Go to the sewers and get out of my sight.", sf::Vector2f(screenW / 3, screenH / 4), 5, sf::Color::White);
				}
				//testQuest->getCurrentStage()->setCompletionStatus(true);
				//testQuest->setCompletionStatus(true);
				audioManager->StopMusic(3);
				audioManager->PlayMusicById(1);
				prevState = gState;
				gState = GAME;//return to free roam
			}

			combatMenu->Update(p->getHealth(), testEnemy->GetHealth());
			combatMenu->Draw(window);
			popupMessageHandler.DrawMessages(*pWindow);
			break;
#pragma endregion

#pragma region Conversation

		case CONVERSATION:
			//really need to do this
			break;
#pragma endregion

#pragma region Inventory
		case INVENTORY:
			window.setView(window.getDefaultView());
			testInv->Draw(window);

			if (useController == true)
			{
				gamepad->CheckAllButtons();
				if (gamepad->Back())
				{
					gState = prevState;
					prevState = INVENTORY;
				}

				if (gamepad->DpadRight() == true || (gamepad->getNormalisedLeftStickAxis().y > 0.9f && gamepad->isLeftAxisOutOfDeadzone() == true))
				{
					testInv->NavigateDown();
					testInv->setCanMove(false);
				}

				else if (gamepad->DpadUp() == true || (gamepad->getNormalisedLeftStickAxis().y < -0.9f && gamepad->isLeftAxisOutOfDeadzone() == true))
				{
					testInv->NavigateUp();
					testInv->setCanMove(false);
				}

				else testInv->setCanMove(true);


				if (gamepad->A() == true)
				{
					if (testInv->getCanSelect())
					{
						testInv->UseItem(*p, *audioManager);
						testInv->setCanSelect(false);
					}
				}
				else
				{
					testInv->setCanSelect(true);
					//std::cout << "A released" << std::endl;
				}

			}
			else if (useController == false)
			{
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
				{
					prevState = gState;
					gState = GAME;
				}
			}

			break;
#pragma endregion

#pragma region Credits
		case CREDITS:
			credits->Update();
			credits->Draw(window);

			if (useController)
			{
				gamepad->CheckAllButtons();
				if (gamepad->B())
				{
					prevState = gState;
					gState = MAINMENU;
				}
			}

			else
			{
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace))
				{
					prevState = gState;
					gState = MAINMENU;
				}
			}
			break;
#pragma endregion
		}


	

		

		 // Finally, display rendered frame on screen 
		window.display();
	} //loop back for next frame

	return EXIT_SUCCESS;
}