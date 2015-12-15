#include "stdafx.h"
#include "CombatMenu.h"

/*constructor*/
CombatMenu::CombatMenu(sf::Font f) : font(f)
{
	backgroundTexture.loadFromFile("Assets/combatMoveSelectorBackground.png");
	backgroundSprite.setTexture(backgroundTexture);
	backgroundSprite.setPosition(0, SCREENHEIGHT - backgroundTexture.getSize().y);

	menuItems[0].setFont(font);
	menuItems[0].setString("Fight");
	menuItems[0].setColor(sf::Color::Red);
	menuItems[0].setCharacterSize(40);
	menuItems[0].setPosition(sf::Vector2f(100, SCREENHEIGHT - 100));

	menuItems[1].setFont(font);
	menuItems[1].setString("Items");
	menuItems[1].setColor(sf::Color::Blue);
	menuItems[1].setCharacterSize(40);
	menuItems[1].setPosition(sf::Vector2f(350, SCREENHEIGHT - 100));

	menuItems[2].setFont(font);
	menuItems[2].setString("Flee");
	menuItems[2].setColor(sf::Color::Blue);
	menuItems[2].setCharacterSize(40);
	menuItems[2].setPosition(sf::Vector2f(650, SCREENHEIGHT - 100));

	selectorTexture.loadFromFile("Assets/combatUiSelector.png");
	selectorSprite.setTexture(selectorTexture);
	selectorSprite.setOrigin(selectorTexture.getSize().x / 2, selectorTexture.getSize().y / 2);
	selectorSprite.setPosition(225, SCREENHEIGHT - 70);

	//attack panel
	attackPanelTexture.loadFromFile("Assets/attackSelectionPanel.png");
	attackPanelSprite.setTexture(attackPanelTexture);
	attackPanelSprite.setOrigin(attackPanelTexture.getSize().x / 2, attackPanelTexture.getSize().y / 2);
	attackPanelSprite.setPosition(200, 200);

	currentOption = 0;
	canMove = true;
}

/*destructor*/
CombatMenu::~CombatMenu()
{

}

void CombatMenu::MoveSelectionRight()
{
	if (canMove == true)
	{
		std::cout << "Moving right" << std::endl;
		if (currentOption == 2)
			currentOption = 0;
		else currentOption += 1;

		for (int i = 0; i < 3; i++)
		{
			menuItems[i].setColor(sf::Color::Blue);
		}
		menuItems[currentOption].setColor(sf::Color::Red);
	}
}

void CombatMenu::MoveSelectionLeft()
{
	if (canMove == true)
	{
		if (currentOption == 0)
			currentOption = 2;
		else currentOption -= 1;

		for (int i = 0; i < 3; i++)
		{
			menuItems[i].setColor(sf::Color::Blue);
		}
		menuItems[currentOption].setColor(sf::Color::Red);
	}
}

/*Draw all elements of the menu*/
void CombatMenu::Draw(sf::RenderTarget & window)
{
	window.draw(backgroundSprite);
	for (int i = 0; i < 3; i++)
	{
		window.draw(menuItems[i]);
	}

	if (currentState == SelectAction)
	{
		window.draw(selectorSprite);
		if (currentOption == 0)
			selectorSprite.setPosition(225, selectorSprite.getPosition().y);
		else if(currentOption == 1)
			selectorSprite.setPosition(475, selectorSprite.getPosition().y);
		else if(currentOption == 2)
			selectorSprite.setPosition(750, selectorSprite.getPosition().y);
	}

	else if (currentState == SelectAttack)
	{
		window.draw(attackPanelSprite);
	}
	else if (currentState == SelectItem)
	{

	}
	else if (currentState == FleeAttempt)
	{

	}
}

int CombatMenu::getCurrentOption()
{
	return currentOption;
}

bool CombatMenu::getCanMove()
{
	return canMove;
}

void CombatMenu::setCanMove(bool cm)
{
	canMove = cm;
}

int CombatMenu::GetCurrentMenuState()
{
	return currentState;
}

void CombatMenu::SetCurrentMenuState(int newState)
{
	currentState = newState;
}
