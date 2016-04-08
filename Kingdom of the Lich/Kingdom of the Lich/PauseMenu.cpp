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

	
	punchAnimSprite.setTexture(punchAnimTexture);
	framePosition = sf::Vector2i(0, 0);
	frameSize = sf::Vector2i(14, 17);
	animationTime = 0.25;
	animationClock.restart();
	numFrames = 4;
	punchAnimSprite.setPosition(screenW / 1.93, 90);
	punchAnimSprite.scale(3, 3);

	if(backgroundTexture.loadFromFile("Assets/Splash Screen/circle5a.png")) {}
	else backgroundTexture.loadFromFile("Assets/Debug.png");
	backgroundSprite.setTexture(backgroundTexture);
	backgroundSprite.setScale(0.5f, 0.5f);
	backgroundSprite.setOrigin(backgroundTexture.getSize().x / 2, backgroundTexture.getSize().y / 2);
	backgroundSprite.setColor(sf::Color(backgroundSprite.getColor().r, backgroundSprite.getColor().g, backgroundSprite.getColor().b, 127));
	backgroundSprite.setPosition(screenW / 2.22 , 400);
	
}

PauseMenu::~PauseMenu()
{
}

/*Load the correct texture to represent the player waiting in the pause menu*/
void PauseMenu::SetPunchTexture(int race, int gender)
{
	if (race == 0)//human
	{
		if (gender == 0)//male
		{
			if (punchAnimTexture.loadFromFile("Assets/Player/Human/Male/Combat/leftAttackSheet.png")) {}
			else (punchAnimTexture.loadFromFile("Assets/Debug.png"));
		}
		else if (gender == 1)//female
		{
			if (punchAnimTexture.loadFromFile("Assets/Player/Human/Female/Combat/leftAttackSheet.png")) {}
			else (punchAnimTexture.loadFromFile("Assets/Debug.png"));
		}
	}
	else if (race == 1)//elf
	{

		if (gender == 0)//male
		{
			if (punchAnimTexture.loadFromFile("Assets/Player/Elf/Male/Combat/leftAttackSheet.png")) {}
			else (punchAnimTexture.loadFromFile("Assets/Debug.png"));
		}
		else if (gender == 1)//female
		{
			if (punchAnimTexture.loadFromFile("Assets/Player/Elf/Female/Combat/leftAttackSheet.png")) {}
			else (punchAnimTexture.loadFromFile("Assets/Debug.png"));
		}
	}
	else if (race == 2)//dwarf
	{
		if (gender == 0)//male
		{
			if (punchAnimTexture.loadFromFile("Assets/Player/Dwarf/Male/Combat/leftAttackSheet.png")) {}
			else (punchAnimTexture.loadFromFile("Assets/Debug.png"));
		}
		else if (gender == 1)//female
		{
			if (punchAnimTexture.loadFromFile("Assets/Player/Dwarf/Female/Combat/leftAttackSheet.png")) {}
			else (punchAnimTexture.loadFromFile("Assets/Debug.png"));
		}
	}
}

//move up through the menu
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

//Move down through the menu
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

//update animation and colour change
void PauseMenu::Update()
{
	if (flashClock.getElapsedTime().asSeconds() > 1.25)
	{
		heading.setColor(sf::Color(rand() % 255, rand() % 255, rand() % 255, 255));
		flashClock.restart();
	}

	if (animationClock.getElapsedTime().asSeconds() > animationTime)
	{
		if (framePosition.x < punchAnimTexture.getSize().x - frameSize.x)
			framePosition.x += frameSize.x;//move the frame forward

		else
		{
			framePosition.x = 0;
		}

		animationClock.restart();
	}

	//reset the texture rectangle
	frameSize = sf::Vector2i(punchAnimTexture.getSize().x / numFrames, punchAnimTexture.getSize().y);
	frame = sf::IntRect(framePosition, frameSize);
	punchAnimSprite.setTextureRect(frame);
	punchAnimSprite.setOrigin(frameSize.x / 2, frameSize.y / 2);
}

void PauseMenu::Draw(sf::RenderTarget & window)
{
	window.draw(backgroundSprite);
	window.draw(heading);
	for (int i = 0; i < 3; i++)
	{
		window.draw(menuItems[i]);
	}
	window.draw(punchAnimSprite);
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
