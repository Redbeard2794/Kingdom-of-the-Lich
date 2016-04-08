#include "stdafx.h"
#include "PauseMenu.h"

PauseMenu::PauseMenu(sf::Font f, int sw, int sh) : font(f), screenW(sw), screenH(sh)
{
	heading.setFont(font);
	heading.setString("Paused");
	heading.setPosition(screenW / 2.5, 50);
	heading.setColor(sf::Color::White);
	heading.setCharacterSize(60);
	flashClock.restart();

	menuItems[0].setFont(font);
	menuItems[0].setString("Save");
	menuItems[0].setColor(sf::Color::Green);
	menuItems[0].setCharacterSize(50);
	menuItems[0].setPosition(sf::Vector2f(screenW / 2.36, screenH / 4));

	menuItems[1].setFont(font);
	menuItems[1].setString("Options");
	menuItems[1].setColor(sf::Color::White);
	menuItems[1].setCharacterSize(50);
	menuItems[1].setPosition(sf::Vector2f(screenW / 2.5, screenH / 2.5));

	menuItems[2].setFont(font);
	menuItems[2].setString("Quit");
	menuItems[2].setColor(sf::Color::White);
	menuItems[2].setCharacterSize(50);
	menuItems[2].setPosition(sf::Vector2f(screenW / 2.36, screenH / 1.8));

	currentSelected = 0;

	canMove = true;
}

void PauseMenu::NavUp()
{
	if (currentSelected == 0)
		currentSelected = 2;
	else currentSelected -= 1;

	for (int i = 0; i < 3; i++)
	{
		menuItems[i].setColor(sf::Color::White);
	}
	menuItems[currentSelected].setColor(sf::Color::Green);
}

void PauseMenu::NavDown()
{
	if (currentSelected == 2)
		currentSelected = 0;
	else currentSelected += 1;

	for (int i = 0; i < 3; i++)
	{
		menuItems[i].setColor(sf::Color::White);
	}
	menuItems[currentSelected].setColor(sf::Color::Green);
}

void PauseMenu::Update()
{
	if (flashClock.getElapsedTime().asSeconds() > 1)
	{
		heading.setColor(sf::Color(rand() % 255, rand() % 255, rand() % 255, 255));
		flashClock.restart();
	}
}

void PauseMenu::Draw(sf::RenderTarget & window)
{
	window.draw(heading);
	for (int i = 0; i < 3; i++)
	{
		window.draw(menuItems[i]);
	}
}

bool PauseMenu::GetCanMove()
{
	return canMove;
}

void PauseMenu::SetCanMove(bool cm)
{
	canMove = cm;
}

bool PauseMenu::GetCanSelect()
{
	return canSelect;
}

void PauseMenu::SetCanSelect(bool cs)
{
	canSelect = cs;
}

int PauseMenu::GetCurrentSelected()
{
	return currentSelected;
}
