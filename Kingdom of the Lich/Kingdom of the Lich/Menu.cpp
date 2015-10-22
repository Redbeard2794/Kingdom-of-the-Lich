#include "stdafx.h"
#include "Menu.h"

Menu::Menu(sf::Font f):font(f)
{
	//load the correct texture or load the debug texture if something is wrong
	if (backgroundTexture.loadFromFile("Assets/MainMenuBackground.png")) {}
	else backgroundTexture.loadFromFile("Assets/Debug.png");	//if it fails load placeholder
	background.setTexture(backgroundTexture);
	background.setPosition(0, 0);

	menuItems[0].setFont(font);
	menuItems[0].setString("New Game");
	menuItems[0].setColor(sf::Color::White);
	menuItems[0].setCharacterSize(50);
	menuItems[0].setPosition(sf::Vector2f(275, 125));

	menuItems[1].setFont(font);
	menuItems[1].setString("Continue");
	menuItems[1].setColor(sf::Color::White);
	menuItems[1].setCharacterSize(50);
	menuItems[1].setPosition(sf::Vector2f(295, 225));

	menuItems[2].setFont(font);
	menuItems[2].setString("Options");
	menuItems[2].setColor(sf::Color::White);
	menuItems[2].setCharacterSize(50);
	menuItems[2].setPosition(sf::Vector2f(305, 325));

	menuItems[3].setFont(font);
	menuItems[3].setString("Credits");
	menuItems[3].setColor(sf::Color::White);
	menuItems[3].setCharacterSize(50);
	menuItems[3].setPosition(sf::Vector2f(320, 425));

	menuItems[4].setFont(font);
	menuItems[4].setString("Quit");
	menuItems[4].setColor(sf::Color::White);
	menuItems[4].setCharacterSize(50);
	menuItems[4].setPosition(sf::Vector2f(350, 525));

	currentSelectedOption = 0;
	selectedOption = -1;
	canMove = true;
}

Menu::~Menu()
{

}

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
	for (int i = 0; i < MAX_MAIN_MENU_ITEMS; i++)
	{
		window.draw(menuItems[i]);
	}
}

