#include "stdafx.h"
#include "Credits.h"

Credits::Credits(int sw, int sh) : screenW(sw), screenH(sh)
{
	summoningCircleTexture.loadFromFile("Assets/Credits/circle4a.png");
	summoningCircleSprite.setTexture(summoningCircleTexture);
	summoningCircleSprite.setOrigin(summoningCircleTexture.getSize().x / 2, summoningCircleTexture.getSize().y / 2);
	summoningCircleSprite.setScale(0.6, 0.6);
	summoningCircleSprite.setPosition(screenW / 2, screenH / 2);
}

Credits::~Credits()
{

}

void Credits::Update()
{

}

void Credits::Draw(sf::RenderTarget& window)
{
	window.draw(summoningCircleSprite);
}