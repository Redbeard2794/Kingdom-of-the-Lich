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

void ConfirmationDialogBox::MoveUp()
{
	if (canMoveSelection == true)
	{
		std::cout << "I'm where I should be" << std::endl;
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

void ConfirmationDialogBox::setConfirmPosition(sf::Vector2f conPos)
{
	confirmationOptions[0]->setPosition(conPos);
}

void ConfirmationDialogBox::setNegativePosition(sf::Vector2f negPos)
{
	confirmationOptions[1]->setPosition(negPos);
}

void ConfirmationDialogBox::Draw(sf::RenderTarget & window)
{
	if (visible == true)
	{
		window.draw(backgroundSprite);
		window.draw(dialogText);

		for (int i = 0; i < 2; i++)
		{
			window.draw(*confirmationOptions[i]);
		}
	}
}
