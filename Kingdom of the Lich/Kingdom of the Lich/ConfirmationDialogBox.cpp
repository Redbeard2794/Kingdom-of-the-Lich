#include "stdafx.h"
#include "ConfirmationDialogBox.h"

bool ConfirmationDialogBox::instanceFlag = false;
ConfirmationDialogBox* ConfirmationDialogBox::instance = NULL;

ConfirmationDialogBox* ConfirmationDialogBox::GetInstance()
{
	if (!instanceFlag)
	{
		instance = new ConfirmationDialogBox();
		instanceFlag = true;
		return instance;
	}
	else return instance;
}

ConfirmationDialogBox::~ConfirmationDialogBox()
{
	instanceFlag = false;
}

//Set the text being displayed on the box
void ConfirmationDialogBox::setDialogText(sf::String dialog, int textSize)
{
	dialogText.setString(dialog);
	dialogText.setCharacterSize(textSize);
}

void ConfirmationDialogBox::Update()
{
	if (visible == true)
	{

	}
}

//for moving through options with a controller
void ConfirmationDialogBox::MoveUp()
{
	if (canMoveSelection == true)
	{
		if (currentOption == 0)
			currentOption = 1;
		else currentOption -= 1;

		for (int i = 0; i < 2; i++)
		{
			confirmationOptions[i]->setColor(sf::Color(80, 0, 0, 255));
		}
		confirmationOptions[currentOption]->setColor(sf::Color::Red);
	}
}

//for moving through options with a controller
void ConfirmationDialogBox::MoveDown()
{
	if (canMoveSelection == true)
	{
		if (currentOption == 1)
			currentOption = 0;
		else currentOption += 1;

		for (int i = 0; i < 2; i++)
		{
			confirmationOptions[i]->setColor(sf::Color(80, 0, 0, 255));
		}
		confirmationOptions[currentOption]->setColor(sf::Color::Red);
	}
}

void ConfirmationDialogBox::CheckMouseToOptions(sf::Vector2i mousePos)
{
	for (int i = 0; i < 2; i++)
	{
		if (confirmationOptions[i]->getGlobalBounds().contains(sf::Vector2f(mousePos.x, mousePos.y)))
		{
			confirmationOptions[i]->setColor(sf::Color::Red);
			if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && mouseClicked == false)
			{
				currentOption = i;
				mouseClicked = true;
				optionConfirmed = true;
			}
		}
		else confirmationOptions[i]->setColor(sf::Color(80, 0, 0, 255));
	}
	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) == false)
		mouseClicked = false;
}

//set position of yes option
void ConfirmationDialogBox::setConfirmPosition(sf::Vector2f conPos)
{
	confirmationOptions[0]->setPosition(conPos);
}

//set position of no option
void ConfirmationDialogBox::setNegativePosition(sf::Vector2f negPos)
{
	confirmationOptions[1]->setPosition(negPos);
}

//set up the hints for controller or mouse/keyboard
void ConfirmationDialogBox::setHints()
{
	//controller hints
	if (showControllerHints == true)
	{
		controllerMoveHintTexture.loadFromFile("Assets/ControllerHints/mainMenuMovementHint.png");
		controllerMoveHint.setTexture(controllerMoveHintTexture);
		controllerMoveHint.setOrigin(controllerMoveHintTexture.getSize().x / 2, controllerMoveHintTexture.getSize().y / 2);
		controllerMoveHint.setPosition(backgroundSprite.getPosition().x - 150, backgroundSprite.getPosition().y + 120);

		controllerMoveHintText.setFont(font);
		controllerMoveHintText.setString("Change selection");
		controllerMoveHintText.setCharacterSize(12);
		controllerMoveHintText.setPosition(backgroundSprite.getPosition().x - 110, backgroundSprite.getPosition().y + 110);
		controllerMoveHintText.setColor(sf::Color::Black);

		controllerSelectHintTexture.loadFromFile("Assets/ControllerHints/aButtonHintSmall.png");
		controllerSelectHint.setTexture(controllerSelectHintTexture);
		controllerSelectHint.setOrigin(controllerSelectHintTexture.getSize().x / 2, controllerSelectHintTexture.getSize().y / 2);
		controllerSelectHint.setPosition(backgroundSprite.getPosition().x + 150, backgroundSprite.getPosition().y + 120);

		controllerSelectHintText.setFont(font);
		controllerSelectHintText.setString("Confirm selection");
		controllerSelectHintText.setCharacterSize(12);
		controllerSelectHintText.setPosition(backgroundSprite.getPosition().x + 35, backgroundSprite.getPosition().y + 110);
		controllerSelectHintText.setColor(sf::Color::Black);

	}
	//mouse and keyboard hints
	else if (showControllerHints == false)
	{
		mouseMoveHintTexture.loadFromFile("Assets/KeyboardAndMouseHints/mouseBaseHint.png");
		mouseMoveHint.setTexture(mouseMoveHintTexture);
		mouseMoveHint.setOrigin(mouseMoveHintTexture.getSize().x / 2, mouseMoveHintTexture.getSize().y / 2);
		mouseMoveHint.setPosition(backgroundSprite.getPosition().x - 150, backgroundSprite.getPosition().y + 120);

		mouseMoveHintText.setFont(font);
		mouseMoveHintText.setString("Change selection");
		mouseMoveHintText.setCharacterSize(12);
		mouseMoveHintText.setPosition(backgroundSprite.getPosition().x - 110, backgroundSprite.getPosition().y + 110);
		mouseMoveHintText.setColor(sf::Color::Black);

		mouseSelectHintTexture.loadFromFile("Assets/KeyboardAndMouseHints/leftClickHint.png");
		mouseSelectHint.setTexture(mouseSelectHintTexture);
		mouseSelectHint.setOrigin(mouseSelectHintTexture.getSize().x / 2, mouseSelectHintTexture.getSize().y / 2);
		mouseSelectHint.setPosition(backgroundSprite.getPosition().x + 150, backgroundSprite.getPosition().y + 120);

		mouseSelectHintText.setFont(font);
		mouseSelectHintText.setString("Confirm selection");
		mouseSelectHintText.setCharacterSize(12);
		mouseSelectHintText.setPosition(backgroundSprite.getPosition().x + 35, backgroundSprite.getPosition().y + 110);
		mouseSelectHintText.setColor(sf::Color::Black);
	}
}

void ConfirmationDialogBox::setScreenSizes(int w, int h)
{
	screenW = w;
	screenH = h;
}

void ConfirmationDialogBox::setElementsOptions()
{
	backgroundSprite.setPosition(screenW / 2, screenH / 2);
	dialogText.setPosition((screenW / 2.65), screenH / 3);
	confirmationOptions[0]->setPosition(sf::Vector2f(backgroundSprite.getPosition().x - 30, backgroundSprite.getPosition().y - 50));
	confirmationOptions[1]->setPosition(sf::Vector2f(backgroundSprite.getPosition().x - 25, backgroundSprite.getPosition().y + 30));
}

void ConfirmationDialogBox::Draw(sf::RenderTarget & window)
{
	if (visible == true)
	{
		//draw the background
		window.draw(backgroundSprite);
		//draw the text on the dialog box
		window.draw(dialogText);
		//draw controller hints
		if (showControllerHints == true)
		{
			window.draw(controllerMoveHint);
			window.draw(controllerMoveHintText);
			window.draw(controllerSelectHint);
			window.draw(controllerSelectHintText);
		}
		//draw keyboard and mouse hints
		else
		{
			window.draw(mouseMoveHint);
			window.draw(mouseMoveHintText);
			window.draw(mouseSelectHint);
			window.draw(mouseSelectHintText);
		}

		//draw yes/no
		for (int i = 0; i < 2; i++)
		{
			window.draw(*confirmationOptions[i]);
		}
	}
}
