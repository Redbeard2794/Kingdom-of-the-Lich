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

	//attack options
	sf::Text* attack1 = new sf::Text();
	attack1->setFont(font);
	attack1->setString("Stab");
	attack1->setColor(sf::Color::Red);
	attack1->setCharacterSize(25);
	attack1->setPosition(sf::Vector2f(75, 25));
	attackOptions.push_back(attack1);

	sf::Text* attack2 = new sf::Text();
	attack2->setFont(font);
	attack2->setString("Quick Chop");
	attack2->setColor(sf::Color::Blue);
	attack2->setCharacterSize(25);
	attack2->setPosition(sf::Vector2f(75, 75));
	attackOptions.push_back(attack2);

	sf::Text* attack3 = new sf::Text();
	attack3->setFont(font);
	attack3->setString("Slice");
	attack3->setColor(sf::Color::Blue);
	attack3->setCharacterSize(25);
	attack3->setPosition(sf::Vector2f(75, 125));
	attackOptions.push_back(attack3);

	//item panel
	itemPanelTexture.loadFromFile("Assets/itemSelectionPanel.png");
	itemPanelSprite.setTexture(itemPanelTexture);
	itemPanelSprite.setOrigin(itemPanelTexture.getSize().x / 2, itemPanelTexture.getSize().y / 2);
	itemPanelSprite.setPosition(400, 200);

	//item options
	sf::Text* item1 = new sf::Text();
	item1->setFont(font);
	item1->setString("Health Potion");
	item1->setColor(sf::Color::Red);
	item1->setCharacterSize(25);
	item1->setPosition(sf::Vector2f(260, 25));
	itemOptions.push_back(item1);

	sf::Text* item2 = new sf::Text();
	item2->setFont(font);
	item2->setString("Bottle of Ale");
	item2->setColor(sf::Color::Blue);
	item2->setCharacterSize(25);
	item2->setPosition(sf::Vector2f(260, 75));
	itemOptions.push_back(item2);

	sf::Text* item3 = new sf::Text();
	item3->setFont(font);
	item3->setString("Apple");
	item3->setColor(sf::Color::Blue);
	item3->setCharacterSize(25);
	item3->setPosition(sf::Vector2f(260, 125));
	itemOptions.push_back(item3);

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

void CombatMenu::MoveSelectionUp()
{
	int size = 0;
	if (currentState == SelectAttack)
		size = attackOptions.size();
	else if (currentState == SelectItem)
		size = itemOptions.size();

	if (canMove == true)
	{
		if (currentOption == 0)
		{
			currentOption = size - 1;

			if(currentState == SelectAttack)
				selectorSprite.setPosition(sf::Vector2f(325, 135));
			else if (currentState == SelectItem)
				selectorSprite.setPosition(sf::Vector2f(525, 135));
		}
		else
		{
			currentOption -= 1;
			selectorSprite.setPosition(selectorSprite.getPosition().x, selectorSprite.getPosition().y - 45);
		}

		for (int i = 0; i < size; i++)
		{
			if(currentState == SelectAttack)
				attackOptions.at(i)->setColor(sf::Color::Blue);
			else if(currentState == SelectItem)
				itemOptions.at(i)->setColor(sf::Color::Blue);
		}

		if (currentState == SelectAttack)
			attackOptions.at(currentOption)->setColor(sf::Color::Red);
		else if (currentState == SelectItem)
			itemOptions.at(currentOption)->setColor(sf::Color::Red);
	}
}

void CombatMenu::MoveSelectionDown()
{
	int size = 0;
	if (currentState == SelectAttack)
		size = attackOptions.size();
	else if (currentState == SelectItem)
		size = itemOptions.size();

	if (canMove == true)
	{
		if (currentOption == size - 1)
		{
			currentOption = 0;

			if (currentState == SelectAttack)
				selectorSprite.setPosition(sf::Vector2f(325, 45));
			else if(currentState == SelectItem)
				selectorSprite.setPosition(sf::Vector2f(525, 45));
		}
		else
		{
			currentOption += 1;
			selectorSprite.setPosition(selectorSprite.getPosition().x, selectorSprite.getPosition().y + 45);
		}

		for (int i = 0; i < attackOptions.size(); i++)
		{
			if (currentState == SelectAttack)
				attackOptions.at(i)->setColor(sf::Color::Blue);
			else if (currentState == SelectItem)
				itemOptions.at(i)->setColor(sf::Color::Blue);
		}

		if (currentState == SelectAttack)
			attackOptions.at(currentOption)->setColor(sf::Color::Red);
		else if (currentState == SelectItem)
			itemOptions.at(currentOption)->setColor(sf::Color::Red);
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
		window.draw(selectorSprite);
		for (int i = 0; i < attackOptions.size(); i++)
		{
			window.draw(*attackOptions.at(i));
		}
	}
	else if (currentState == SelectItem)
	{
		window.draw(itemPanelSprite);
		window.draw(selectorSprite);
		for (int i = 0; i < itemOptions.size(); i++)
		{
			window.draw(*itemOptions.at(i));
		}
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

void CombatMenu::SetSelectorPosition(sf::Vector2f pos)
{
	selectorSprite.setPosition(pos);
}

sf::Vector2f CombatMenu::GetSelectorPosition()
{
	return selectorSprite.getPosition();
}
