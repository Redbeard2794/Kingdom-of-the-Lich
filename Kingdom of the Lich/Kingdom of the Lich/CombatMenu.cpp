#include "stdafx.h"
#include "CombatMenu.h"

/*constructor*/
CombatMenu::CombatMenu()
{
	backgroundTexture.loadFromFile("Assets/combatMoveSelectorBackground.png");
	backgroundSprite.setTexture(backgroundTexture);
	backgroundSprite.setPosition(0, 450);
}

/*destructor*/
CombatMenu::~CombatMenu()
{

}

/*Draw all elements of the menu*/
void CombatMenu::Draw(sf::RenderTarget & window)
{
	window.draw(backgroundSprite);
}
