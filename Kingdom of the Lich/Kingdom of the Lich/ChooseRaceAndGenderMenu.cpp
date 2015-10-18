#include "stdafx.h"
#include "ChooseRaceAndGenderMenu.h"

ChooseRaceAndGenderMenu::ChooseRaceAndGenderMenu(sf::Font f):font(f)
{
	//table
	if (tableTexture.loadFromFile("Assets/table1.png")) {}
	else tableTexture.loadFromFile("Assets/Debug.png");	//if it fails load placeholder
	table.setTexture(tableTexture);
	table.setPosition(0, 5);

	//parchment on table
	if (parchmentTexture.loadFromFile("Assets/parchment.png")) {}
	else parchmentTexture.loadFromFile("Assets/Debug.png");	//if it fails load placeholder
	parchment.setTexture(parchmentTexture);
	parchment.setOrigin(sf::Vector2f(parchmentTexture.getSize().x / 2, parchmentTexture.getSize().y / 2));
	parchment.setPosition(SCREENWIDTH/2, SCREENHEIGHT/2);

	//button to select male
	if (maleButtonTexture.loadFromFile("Assets/MaleButtonBlue.png")) {}
	else maleButtonTexture.loadFromFile("Assets/Debug.png");	//if it fails load placeholder
	maleButton.setTexture(maleButtonTexture);
	maleButton.setOrigin(sf::Vector2f(maleButtonTexture.getSize().x / 2, maleButtonTexture.getSize().y / 2));
	maleButton.setPosition(300, 500);

	//button to select female
	if (femaleButtonTexture.loadFromFile("Assets/FemaleButtonPink.png")) {}
	else femaleButtonTexture.loadFromFile("Assets/Debug.png");	//if it fails load placeholder
	femaleButton.setTexture(femaleButtonTexture);
	femaleButton.setOrigin(sf::Vector2f(femaleButtonTexture.getSize().x / 2, femaleButtonTexture.getSize().y / 2));
	femaleButton.setPosition(500, 500);

	//Header for choosing race
	ChooseRace.setFont(font);
	ChooseRace.setString("Choose your race.");
	ChooseRace.setColor(sf::Color::Black);
	ChooseRace.setPosition(sf::Vector2f(275, 80));

	//Header for choosing gender
	ChooseGender.setFont(font);
	ChooseGender.setString("Choose your gender.");
	ChooseGender.setColor(sf::Color::Black);
	ChooseGender.setPosition(sf::Vector2f(275, 425));

	//text for races
	races[HUMAN].setFont(font);
	races[HUMAN].setString("Human");
	races[HUMAN].setColor(sf::Color::Black);
	races[HUMAN].setPosition(sf::Vector2f(SCREENWIDTH / 5, SCREENHEIGHT / 4));

	races[ELF].setFont(font);
	races[ELF].setString("Elf");
	races[ELF].setColor(sf::Color::Black);
	races[ELF].setPosition(sf::Vector2f(SCREENWIDTH / 2, SCREENHEIGHT / 4));

	races[BEASTMAN].setFont(font);
	races[BEASTMAN].setString("Beastman");
	races[BEASTMAN].setColor(sf::Color::Black);
	races[BEASTMAN].setPosition(sf::Vector2f(550, SCREENHEIGHT / 4));

	mouseClicked = false;
}

ChooseRaceAndGenderMenu::~ChooseRaceAndGenderMenu()
{

}

void ChooseRaceAndGenderMenu::CheckMouseAgainstRaces(sf::Vector2i mousePos)
{
	for (int i = 0; i < 3; i++)
	{
		if (races[i].getGlobalBounds().contains(sf::Vector2f(mousePos.x, mousePos.y)))
		{
			races[i].setColor(sf::Color::Blue);
			if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)&& mouseClicked==false)
			{
				currentlySelectedRace = i;
				mouseClicked = true;
			}
		}
		else races[i].setColor(sf::Color::Black);
	}
	if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) == false)
		mouseClicked = false;
}

void ChooseRaceAndGenderMenu::CheckMouseAgainstGenders(sf::Vector2i mousePos)
{
	if (maleButton.getGlobalBounds().contains(sf::Vector2f(mousePos.x, mousePos.y)))
	{
		maleButton.setColor(sf::Color::Green);
		if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && mouseClicked == false)
		{
			currentlySelectedGender = MALE;
			mouseClicked = true;
		}
	}
	else maleButton.setColor(sf::Color::White);

	if (femaleButton.getGlobalBounds().contains(sf::Vector2f(mousePos.x, mousePos.y)))
	{
		femaleButton.setColor(sf::Color::Green);
		if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && mouseClicked == false)
		{
			currentlySelectedGender = FEMALE;
			mouseClicked = true;
		}
	}
	else femaleButton.setColor(sf::Color::White);

	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) == false)
		mouseClicked = false;
}

void ChooseRaceAndGenderMenu::Draw(sf::RenderWindow &window)
{
	window.draw(table);
	window.draw(parchment);
	window.draw(ChooseRace);
	window.draw(ChooseGender);
	window.draw(maleButton);
	window.draw(femaleButton);
	for (int i = 0; i < 3; i++)
	{
		window.draw(races[i]);
	}
}