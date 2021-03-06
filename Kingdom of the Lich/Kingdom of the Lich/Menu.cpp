#include "stdafx.h"
#include "Menu.h"

//constructor(params are font and whether to show controller hints or keyboard hints)
Menu::Menu(sf::Font f, bool controller, int screenW, int screenH):font(f),showControllerHints(controller)
{
	LoadText(screenW, screenH);
	LoadTexturesAndSprites(screenW, screenH);

	currentSelectedOption = 0;
	//if (showControllerHints == true)
	//{
	selectedOption = 0;
	menuItems[selectedOption].setColor(sf::Color::Blue);
	//}
	canMove = true;
}

//destructor
Menu::~Menu()
{

}

//load all text items(menu options)
void Menu::LoadText(int screenW, int screenH)
{
	menuItems[0].setFont(font);
	menuItems[0].setString("New Game");
	menuItems[0].setColor(sf::Color::White);
	menuItems[0].setCharacterSize(50);
	menuItems[0].setPosition(sf::Vector2f(screenW / 2.4, screenH / 6.5));//275, 125

	menuItems[1].setFont(font);
	menuItems[1].setString("Continue");
	menuItems[1].setColor(sf::Color::White);
	menuItems[1].setCharacterSize(50);
	menuItems[1].setPosition(sf::Vector2f(screenW / 2.33, screenH / 3.5));//295, 225

	menuItems[2].setFont(font);
	menuItems[2].setString("Options");
	menuItems[2].setColor(sf::Color::White);
	menuItems[2].setCharacterSize(50);
	menuItems[2].setPosition(sf::Vector2f(screenW / 2.27, screenH / 2.4));//305, 325

	menuItems[3].setFont(font);
	menuItems[3].setString("Credits");
	menuItems[3].setColor(sf::Color::White);
	menuItems[3].setCharacterSize(50);
	menuItems[3].setPosition(sf::Vector2f(screenW / 2.24, screenH / 1.8));//320, 425

	menuItems[4].setFont(font);
	menuItems[4].setString("Quit");
	menuItems[4].setColor(sf::Color::White);
	menuItems[4].setCharacterSize(50);
	menuItems[4].setPosition(sf::Vector2f(screenW / 2.17, screenH / 1.44));//350, 525
}

//load all sprites and textures needed for the menu
void Menu::LoadTexturesAndSprites(int screenW, int screenH)
{
	//load the correct texture or load the debug texture if something is wrong
	if (backgroundTexture.loadFromFile("Assets/mainMenu/MainMenuBackground" + std::to_string(screenW) + "x" + std::to_string(screenH) + ".png")) {}
	else backgroundTexture.loadFromFile("Assets/mainMenu/MainMenuBackground.png");	//if it fails load default background(800x600)
	background.setTexture(backgroundTexture);
	background.setPosition(0, 0);

	if (showControllerHints == true)//show controller hints
	{
		if (controllerMoveHintTexture.loadFromFile("Assets/ControllerHints/mainMenuMovementHint.png")) {}
		else controllerMoveHintTexture.loadFromFile("Assets/Debug.png");	//if it fails load placeholder

		controllerMoveHintSprite.setTexture(controllerMoveHintTexture);
		controllerMoveHintSprite.setOrigin(sf::Vector2f(controllerMoveHintTexture.getSize().x / 2,
			controllerMoveHintTexture.getSize().y / 2));
		controllerMoveHintSprite.setPosition(screenW / 12, screenH - 30);


		if (controllerSelectHintTexture.loadFromFile("Assets/ControllerHints/aButtonHintSmall.png")) {}
		else controllerSelectHintTexture.loadFromFile("Assets/Debug.png");	//if it fails load placeholder

		controllerSelectHintSprite.setTexture(controllerSelectHintTexture);
		controllerSelectHintSprite.setOrigin(sf::Vector2f(controllerSelectHintTexture.getSize().x / 2,
			controllerSelectHintTexture.getSize().y / 2));
		controllerSelectHintSprite.setPosition(screenW - 125, screenH - 30);

		controllerMoveHintText.setFont(font);
		controllerMoveHintText.setString("Change selection");
		controllerMoveHintText.setColor(sf::Color::White);
		controllerMoveHintText.setCharacterSize(15);
		controllerMoveHintText.setPosition(screenW / 8, screenH - 40);

		controllerSelectHintText.setFont(font);
		controllerSelectHintText.setString("Confirm selection");
		controllerSelectHintText.setColor(sf::Color::White);
		controllerSelectHintText.setCharacterSize(15);
		controllerSelectHintText.setPosition(screenW - 275, screenH - 40);
	}

	else if (showControllerHints == false)//show keyboard and mouse hints
	{
		if (mouseMoveHintTexture.loadFromFile("Assets/KeyboardAndMouseHints/mouseBaseHint.png")) {}
		else mouseMoveHintTexture.loadFromFile("Assets/Debug.png");	//if it fails load placeholder

		mouseMoveHintSprite.setTexture(mouseMoveHintTexture);
		mouseMoveHintSprite.setOrigin(sf::Vector2f(mouseMoveHintTexture.getSize().x / 2,
			mouseMoveHintTexture.getSize().y / 2));
		mouseMoveHintSprite.setPosition(screenW / 16, screenH - 30);

		if (mouseSelectHintTexture.loadFromFile("Assets/KeyboardAndMouseHints/leftClickHint.png")) {}
		else mouseSelectHintTexture.loadFromFile("Assets/Debug.png");	//if it fails load placeholder

		mouseSelectHintSprite.setTexture(mouseSelectHintTexture);
		mouseSelectHintSprite.setOrigin(sf::Vector2f(mouseSelectHintTexture.getSize().x / 2,
			mouseSelectHintTexture.getSize().y / 2));
		mouseSelectHintSprite.setPosition(screenW - 50, screenH - 30);

		mouseMoveHintText.setFont(font);
		mouseMoveHintText.setString("Move mouse to change selection");
		mouseMoveHintText.setColor(sf::Color::White);
		mouseMoveHintText.setCharacterSize(15);
		mouseMoveHintText.setPosition(screenW / 10, screenH - 40);

		mouseSelectHintText.setFont(font);
		mouseSelectHintText.setString("Left click to confirm selection");
		mouseSelectHintText.setColor(sf::Color::White);
		mouseSelectHintText.setCharacterSize(15);
		mouseSelectHintText.setPosition(screenW - 275, screenH - 40);
	}
}

//for moving up in the menu with a controller
void Menu::MoveDown()//for when the player is using a controller
{
	if (canMove == true)
	{
		if (selectedOption == 4)
			selectedOption = 0;
		else selectedOption += 1;

		for (int i = 0; i < MAX_MAIN_MENU_ITEMS; i++)
		{
			menuItems[i].setColor(sf::Color::White);
		}
		menuItems[selectedOption].setColor(sf::Color::Blue);
	}
}

//for moving down in the menu with a controller
void Menu::MoveUp()//for when the player is using a controller
{
	if (canMove == true)
	{
		if (selectedOption == 0)
			selectedOption = 4;
		else selectedOption -= 1;

		for (int i = 0; i < MAX_MAIN_MENU_ITEMS; i++)
		{
			menuItems[i].setColor(sf::Color::White);
		}
		menuItems[selectedOption].setColor(sf::Color::Blue);
	}
}

//check the mouse against the menu items
void Menu::CheckMouse(sf::Vector2i mousePos)
{
	for (int i = 0; i < MAX_MAIN_MENU_ITEMS; i++)
	{
		if (menuItems[i].getGlobalBounds().contains(sf::Vector2f(mousePos.x,mousePos.y)))
		{
			menuItems[i].setColor(sf::Color::Blue);
			if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
			{
				selectedOption = i;
			}
		}
		else menuItems[i].setColor(sf::Color::White);
	}
}

void Menu::Draw(sf::RenderWindow &window)
{

	window.draw(background);
	if (showControllerHints == true)//controller hints
	{
		window.draw(controllerMoveHintSprite);
		window.draw(controllerSelectHintSprite);
		window.draw(controllerMoveHintText);
		window.draw(controllerSelectHintText);
	}
	else if (showControllerHints == false)//keyboard and mouse hints
	{
		window.draw(mouseMoveHintSprite);
		window.draw(mouseSelectHintSprite);
		window.draw(mouseMoveHintText);
		window.draw(mouseSelectHintText);
	}
	for (int i = 0; i < MAX_MAIN_MENU_ITEMS; i++)
	{
		window.draw(menuItems[i]);
	}
}

void Menu::ResetMenu()
{
	selectedOption = 0;
}

