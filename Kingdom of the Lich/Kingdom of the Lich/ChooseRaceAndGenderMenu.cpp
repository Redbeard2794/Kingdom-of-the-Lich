#include "stdafx.h"
#include "ChooseRaceAndGenderMenu.h"

ChooseRaceAndGenderMenu::ChooseRaceAndGenderMenu(sf::Font f, bool controller):font(f), showControllerHints(controller)
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
	//maleButton.setTexture(maleButtonTexture);
	//maleButton.setOrigin(sf::Vector2f(maleButtonTexture.getSize().x / 2, maleButtonTexture.getSize().y / 2));
	//maleButton.setPosition(300, 250);//y=500
	genders[0].setTexture(maleButtonTexture);
	genders[0].setOrigin(sf::Vector2f(maleButtonTexture.getSize().x / 2, maleButtonTexture.getSize().y / 2));
	genders[0].setPosition(300, 250);//y=500

	//button to select female
	if (femaleButtonTexture.loadFromFile("Assets/FemaleButtonPink.png")) {}
	else femaleButtonTexture.loadFromFile("Assets/Debug.png");	//if it fails load placeholder
	//femaleButton.setTexture(femaleButtonTexture);
	//femaleButton.setOrigin(sf::Vector2f(femaleButtonTexture.getSize().x / 2, femaleButtonTexture.getSize().y / 2));
	//femaleButton.setPosition(500, 250);
	genders[1].setTexture(femaleButtonTexture);
	genders[1].setOrigin(sf::Vector2f(femaleButtonTexture.getSize().x / 2, femaleButtonTexture.getSize().y / 2));
	genders[1].setPosition(500, 250);

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

	//Header for choosing class
	ChooseClass.setFont(font);
	ChooseClass.setString("Choose your class.");
	ChooseClass.setColor(sf::Color::Black);
	ChooseClass.setPosition(sf::Vector2f(275, 80));

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

	if (showControllerHints == true)
	{
		controllerMoveHintTexture.loadFromFile("Assets/ControllerHints/characterCreationMovementHint.png");
		controllerMoveHint.setTexture(controllerMoveHintTexture);
		controllerMoveHint.setOrigin(controllerMoveHintTexture.getSize().x / 2, controllerMoveHintTexture.getSize().y / 2);
		controllerMoveHint.setPosition(SCREENWIDTH / 12, SCREENHEIGHT - 30);

		controllerMoveHintText.setFont(font);
		controllerMoveHintText.setString("Change selection");
		controllerMoveHintText.setCharacterSize(15);
		controllerMoveHintText.setPosition(SCREENWIDTH / 8, SCREENHEIGHT - 40);
		controllerMoveHintText.setColor(sf::Color::White);

		controllerSelectHintTexture.loadFromFile("Assets/ControllerHints/rbButtonHint.png");
		controllerSelectHint.setTexture(controllerSelectHintTexture);
		controllerSelectHint.setOrigin(controllerSelectHintTexture.getSize().x / 2, controllerSelectHintTexture.getSize().y / 2);
		controllerSelectHint.setPosition(SCREENWIDTH - 75, SCREENHEIGHT - 30);

		controllerSelectHintText.setFont(font);
		controllerSelectHintText.setString("Confirm selection");
		controllerSelectHintText.setCharacterSize(15);
		controllerSelectHintText.setPosition(SCREENWIDTH - 225, SCREENHEIGHT - 40);
		controllerSelectHintText.setColor(sf::Color::White);

	}
	else
	{
		mouseMoveHintTexture.loadFromFile("Assets/KeyboardAndMouseHints/mouseMoveAndLeftClick.png");
		mouseMoveHint.setTexture(mouseMoveHintTexture);
		mouseMoveHint.setOrigin(mouseMoveHintTexture.getSize().x / 2, mouseMoveHintTexture.getSize().y / 2);
		mouseMoveHint.setPosition(SCREENWIDTH / 12, SCREENHEIGHT - 30);

		mouseMoveHintText.setFont(font);
		mouseMoveHintText.setString("Change selection");
		mouseMoveHintText.setCharacterSize(15);
		mouseMoveHintText.setPosition(SCREENWIDTH / 7, SCREENHEIGHT - 40);
		mouseMoveHintText.setColor(sf::Color::White);

		keyboardSelectHintTexture.loadFromFile("Assets/KeyboardAndMouseHints/enterHint.png");
		keyboardSelectHint.setTexture(keyboardSelectHintTexture);
		keyboardSelectHint.setOrigin(keyboardSelectHintTexture.getSize().x / 2, keyboardSelectHintTexture.getSize().y / 2);
		keyboardSelectHint.setPosition(SCREENWIDTH - 75, SCREENHEIGHT - 30);

		keyboardSelectHintText.setFont(font);
		keyboardSelectHintText.setString("Confirm selection");
		keyboardSelectHintText.setCharacterSize(15);
		keyboardSelectHintText.setPosition(SCREENWIDTH - 225, SCREENHEIGHT - 40);
		keyboardSelectHintText.setColor(sf::Color::White);
	}
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
	if (genders[0].getGlobalBounds().contains(sf::Vector2f(mousePos.x, mousePos.y)))
	{
		genders[0].setColor(sf::Color::Green);
		if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && mouseClicked == false)
		{
			currentlySelectedGender = MALE;
			std::cout << "You have selected MALE as your gender" << std::endl;
			mouseClicked = true;
		}
	}
	else genders[0].setColor(sf::Color::White);

	if (genders[1].getGlobalBounds().contains(sf::Vector2f(mousePos.x, mousePos.y)))
	{
		genders[1].setColor(sf::Color::Green);
		if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && mouseClicked == false)
		{
			currentlySelectedGender = FEMALE;
			std::cout << "You have selected FEMALE as your gender" << std::endl;
			mouseClicked = true;
		}
	}
	else genders[1].setColor(sf::Color::White);

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
		//if (currentlySelectedGender == MALE)
		//{
		//	currentlySelectedGender = FEMALE;
		//}
		//else if (currentlySelectedGender == FEMALE)
		//	currentlySelectedGender = MALE;
		if (currentlySelectedGender == 1)
			currentlySelectedGender = 0;
		else currentlySelectedGender += 1;

		for (int i = 0; i < MAX_MAIN_MENU_ITEMS; i++)
		{
			genders[i].setColor(sf::Color::Green);
		}
		genders[currentlySelectedGender].setColor(sf::Color::White);

		std::cout << "Currently selected gender: " << currentlySelectedGender << std::endl;
	}
}

//for moving left through the gender choices with a controller
void ChooseRaceAndGenderMenu::moveGenderSelectionLeft()
{
	if (canMoveSelection == true)
	{
		if (currentlySelectedGender == 0)
			currentlySelectedGender = 1;
		else currentlySelectedGender -= 1;

		for (int i = 0; i < MAX_MAIN_MENU_ITEMS; i++)
		{
			genders[i].setColor(sf::Color::Green);
		}
		genders[currentlySelectedGender].setColor(sf::Color::White);

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
	if (showControllerHints == true)
	{
		window.draw(controllerMoveHint);
		window.draw(controllerMoveHintText);
		window.draw(controllerSelectHint);
		window.draw(controllerSelectHintText);
	}
	else
	{
		window.draw(mouseMoveHint);
		window.draw(mouseMoveHintText);
		window.draw(keyboardSelectHint);
		window.draw(keyboardSelectHintText);
	}
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
		//window.draw(maleButton);
		//window.draw(femaleButton);
		for (int i = 0; i < 2; i++)
		{
			window.draw(genders[i]);
		}
		break;

	case CHOOSECLASS:
		window.draw(ChooseClass);
		classes[currentlySelectedClass].setColor(sf::Color::Red);
		for (int i = 0; i < 3; i++)
		{
			window.draw(classes[i]);
		}
		break;
	}
}