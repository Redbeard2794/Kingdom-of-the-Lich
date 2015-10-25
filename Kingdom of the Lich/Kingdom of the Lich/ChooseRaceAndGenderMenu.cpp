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
	maleButton.setPosition(300, 250);//y=500

	//button to select female
	if (femaleButtonTexture.loadFromFile("Assets/FemaleButtonPink.png")) {}
	else femaleButtonTexture.loadFromFile("Assets/Debug.png");	//if it fails load placeholder
	femaleButton.setTexture(femaleButtonTexture);
	femaleButton.setOrigin(sf::Vector2f(femaleButtonTexture.getSize().x / 2, femaleButtonTexture.getSize().y / 2));
	femaleButton.setPosition(500, 250);

	//Header for choosing race
	ChooseRace.setFont(font);
	ChooseRace.setString("Choose your race.");
	ChooseRace.setColor(sf::Color::Black);
	ChooseRace.setPosition(sf::Vector2f(275, 80));

	//Header for choosing gender
	ChooseGender.setFont(font);
	ChooseGender.setString("Choose your gender.");
	ChooseGender.setColor(sf::Color::Black);
	ChooseGender.setPosition(sf::Vector2f(275, 80));//425

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

	//text for classes
	classes[ARCHER].setFont(font);
	classes[ARCHER].setString("Archer");
	classes[ARCHER].setColor(sf::Color::Black);
	classes[ARCHER].setPosition(sf::Vector2f(SCREENWIDTH / 5, SCREENHEIGHT / 4));

	classes[KNIGHT].setFont(font);
	classes[KNIGHT].setString("Knight");
	classes[KNIGHT].setColor(sf::Color::Black);
	classes[KNIGHT].setPosition(sf::Vector2f(SCREENWIDTH / 2, SCREENHEIGHT / 4));

	classes[SPELLBLADE].setFont(font);
	classes[SPELLBLADE].setString("Spellblade");
	classes[SPELLBLADE].setColor(sf::Color::Black);
	classes[SPELLBLADE].setPosition(sf::Vector2f(550, SCREENHEIGHT / 4));

	mouseClicked = false;

	currentState = CHOOSERACE;

	currentlySelectedRace = 0;
	currentlySelectedGender = 0;
	currentlySelectedClass = 0;

	canMoveSelection = true;
	canSelect = true;
}

ChooseRaceAndGenderMenu::~ChooseRaceAndGenderMenu()
{

}

//update the state of the menu(choosing race+gender, choosing class)
void ChooseRaceAndGenderMenu::Update(sf::Vector2i mousePos)
{
	switch (currentState)
	{
	case CHOOSERACE://player is selecting their race and gender
		CheckMouseAgainstRaces(mousePos);
		//CheckMouseAgainstGenders(mousePos);
		break;

	case CHOOSEGENDER:
		CheckMouseAgainstGenders(mousePos);
		break;

	case CHOOSECLASS://player is selecting their class
		CheckMouseAgainstClasses(mousePos);
		break;
	}
}

//check the mouse against the different options for choosing the race of the character
void ChooseRaceAndGenderMenu::CheckMouseAgainstRaces(sf::Vector2i mousePos)
{
	for (int i = 0; i < 3; i++)
	{
		if (races[i].getGlobalBounds().contains(sf::Vector2f(mousePos.x, mousePos.y)))
		{
			//races[i].setColor(sf::Color::Blue);
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

//check the mouse against the different options for choosing the gender of the character
void ChooseRaceAndGenderMenu::CheckMouseAgainstGenders(sf::Vector2i mousePos)
{
	if (maleButton.getGlobalBounds().contains(sf::Vector2f(mousePos.x, mousePos.y)))
	{
		maleButton.setColor(sf::Color::Green);
		if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && mouseClicked == false)
		{
			currentlySelectedGender = MALE;
			std::cout << "You have selected MALE as your gender" << std::endl;
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
			std::cout << "You have selected FEMALE as your gender" << std::endl;
			mouseClicked = true;
		}
	}
	else femaleButton.setColor(sf::Color::White);

	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) == false)
		mouseClicked = false;
}

//check the mouse against the different options for choosing the class of the character
void ChooseRaceAndGenderMenu::CheckMouseAgainstClasses(sf::Vector2i mousePos)
{
	for (int i = 0; i < 3; i++)
	{
		if (classes[i].getGlobalBounds().contains(sf::Vector2f(mousePos.x, mousePos.y)))
		{
			//classes[i].setColor(sf::Color::Blue);
			if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && mouseClicked == false)
			{
				currentlySelectedClass = i;
				mouseClicked = true;
			}
		}
		else classes[i].setColor(sf::Color::Black);
	}
	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) == false)
		mouseClicked = false;
}

//for moving right through the race choices with a controller
void ChooseRaceAndGenderMenu::moveRaceSelectionRight()
{
	if (canMoveSelection == true)
	{
		if (currentlySelectedRace == 2)
			currentlySelectedRace = 0;
		else currentlySelectedRace += 1;
	}
}

//for moving left through the race choices with a controller
void ChooseRaceAndGenderMenu::moveRaceSelectionLeft()
{
	if (canMoveSelection == true)
	{
		if (currentlySelectedRace == 0)
			currentlySelectedRace = 2;
		else currentlySelectedRace -= 1;
	}
}

//for moving right through the gender choices with a controller
void ChooseRaceAndGenderMenu::moveGenderSelectionRight()
{
	if (canMoveSelection == true)
	{
		if (currentlySelectedGender == MALE)
		{
			currentlySelectedGender = FEMALE;
		}
		else if (currentlySelectedGender == FEMALE)
			currentlySelectedGender = MALE;

		std::cout << "Currently selected gender: " << currentlySelectedGender << std::endl;
	}
}

//for moving left through the gender choices with a controller
void ChooseRaceAndGenderMenu::moveGenderSelectionLeft()
{
	if (canMoveSelection == true)
	{
		if (currentlySelectedGender == FEMALE)
		{
			currentlySelectedGender = MALE;
		}
		else if (currentlySelectedGender == MALE)
			currentlySelectedGender = FEMALE;

		std::cout << "Currently selected gender: " << currentlySelectedGender << std::endl;
	}
}

//for moving right through the class choices with a controller
void ChooseRaceAndGenderMenu::moveClassSelectionRight()
{
	if (canMoveSelection == true)
	{
		if (currentlySelectedClass == 2)
			currentlySelectedClass = 0;
		else currentlySelectedClass += 1;
	}
}

//for moving left through the class choices with a controller
void ChooseRaceAndGenderMenu::moveClassSelectionLeft()
{
	if (canMoveSelection == true)
	{
		if (currentlySelectedClass == 0)
			currentlySelectedClass = 2;
		else currentlySelectedClass -= 1;
	}
}

//draw the menu
void ChooseRaceAndGenderMenu::Draw(sf::RenderWindow &window)
{
	window.draw(table);
	window.draw(parchment);
	switch (currentState)
	{
	case CHOOSERACE:
		window.draw(ChooseRace);

		for (int i = 0; i < 3; i++)
		{
			races[i].setColor(sf::Color::Black);
		}
		races[currentlySelectedRace].setColor(sf::Color::Red);
		

		for (int i = 0; i < 3; i++)
		{
			window.draw(races[i]);
		}
		break;

	case CHOOSEGENDER:
		window.draw(ChooseGender);
		window.draw(maleButton);
		window.draw(femaleButton);
		break;

	case CHOOSECLASS:
		window.draw(ChooseRace);
		classes[currentlySelectedClass].setColor(sf::Color::Red);
		for (int i = 0; i < 3; i++)
		{
			window.draw(classes[i]);
		}
		break;
	}
}