#include "stdafx.h"
#include "OptionsMenu.h"

OptionsMenu::OptionsMenu(sf::Font f, int sw, int sh) : font(f), screenW(sw), screenH(sh)
{
	audioWaveTexture.loadFromFile("Assets/audioWave.png");

	menuItems[0].setFont(font);
	menuItems[0].setColor(sf::Color::White);
	menuItems[0].setString("Music Volume: ");
	menuItems[0].setPosition(screenW / 2.5, 50);

	menuItems[1].setFont(font);
	menuItems[1].setColor(sf::Color::White);
	menuItems[1].setString("Sfx Volume: ");
	menuItems[1].setPosition(screenW / 2.5, 300);

	menuItems[2].setFont(font);
	menuItems[2].setColor(sf::Color::White);
	menuItems[2].setString("Back");
	menuItems[2].setPosition(screenW/2.1, screenH-100);

	currentHighlighted = 0;
	currentSelected = -1;

	currentMenuState = NAV;
	canSelect = true;
	canMove = true;

	musicBar.setSize(sf::Vector2f(10, 50));
	musicBar.setFillColor(sf::Color::White);
	musicBar.setOutlineColor(sf::Color::Red);
	musicBar.setPosition(sf::Vector2f(screenW / 2.5, 150));
	musicBar.setOutlineThickness(2);
	musicBar.setTexture(&audioWaveTexture);

	sfxBar.setSize(sf::Vector2f(10, 50));
	sfxBar.setFillColor(sf::Color::White);
	sfxBar.setOutlineColor(sf::Color::Red);
	sfxBar.setPosition(sf::Vector2f(screenW / 2.5, 400));
	sfxBar.setOutlineThickness(2);
	sfxBar.setTexture(&audioWaveTexture);
}

OptionsMenu::~OptionsMenu()
{
}

void OptionsMenu::Update(AudioManager * audioManager)
{
	if (currentMenuState == NAV)
	{

	}
	else if (currentMenuState == MUSIC)
	{
		audioManager->SetMusicVolume(musicBar.getSize().x / 2);
	}
	else if (currentMenuState == SFX)
	{
		audioManager->SetSfxVolume(sfxBar.getSize().x / 2);
	}

	for (int i = 0; i < 3; i++)
	{
		if (currentHighlighted == i)
		{
			menuItems[i].setColor(sf::Color::Red);
		}
		else
		{
			menuItems[i].setColor(sf::Color::White);
		}
	}
}

void OptionsMenu::MoveUp()
{
	if (canMove)
	{
		if (currentHighlighted == 0)
			currentHighlighted = 2;
		else currentHighlighted--;
	}
}

void OptionsMenu::MoveDown()
{
	if (canMove)
	{
		if (currentHighlighted == 2)
			currentHighlighted = 0;
		else currentHighlighted++;
	}
}

void OptionsMenu::IncreaseMusicVol()
{
	if (canMove)
	{
		if (musicBar.getSize().x <= 200)
		{
			musicBar.setSize(sf::Vector2f(musicBar.getSize().x + 1, musicBar.getSize().y));
		}
	}
}

void OptionsMenu::DecreaseMusicVol()
{
	if (canMove)
	{
		if (musicBar.getSize().x >= 0)
		{
			musicBar.setSize(sf::Vector2f(musicBar.getSize().x - 1, musicBar.getSize().y));
		}
	}
}

void OptionsMenu::IncreaseSFXVol()
{
	if (canMove)
	{
		if (sfxBar.getSize().x <= 200)
		{
			sfxBar.setSize(sf::Vector2f(sfxBar.getSize().x + 1, sfxBar.getSize().y));
		}
	}
}

void OptionsMenu::DecreaseSFXVol()
{
	if (canMove)
	{
		if (sfxBar.getSize().x >= 0)
		{
			sfxBar.setSize(sf::Vector2f(sfxBar.getSize().x - 1, sfxBar.getSize().y));
		}
	}
}

void OptionsMenu::Draw(sf::RenderTarget & window)
{
	for (int i = 0; i < 3; i++)
	{
		window.draw(menuItems[i]);
	}

	window.draw(musicBar);
	window.draw(sfxBar);
}

bool OptionsMenu::GetCanMove()
{
	return canMove;
}

void OptionsMenu::SetCanMove(bool cm)
{
	canMove = cm;
}

int OptionsMenu::GetCurrentHighlighted()
{
	return currentHighlighted;
}

void OptionsMenu::SetCurrentHighlighted(int ch)
{
	currentHighlighted = ch;
}

int OptionsMenu::GetCurrentSelected()
{
	return currentSelected;
}

void OptionsMenu::SetCurrentSelected(int cs)
{
	currentSelected = cs;
}

int OptionsMenu::GetState()
{
	return currentMenuState;
}

void OptionsMenu::SetState(int s)
{
	currentMenuState = s;
}

bool OptionsMenu::GetCanSelect()
{
	return canSelect;
}

void OptionsMenu::SetCanSelect(bool cse)
{
	canSelect = cse;
}
