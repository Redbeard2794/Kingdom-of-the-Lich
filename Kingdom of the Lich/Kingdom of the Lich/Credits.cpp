#include "stdafx.h"
#include "Credits.h"

/*constructor. params: screen width and screen height*/
Credits::Credits(int sw, int sh) : screenW(sw), screenH(sh)
{
	summoningCircleTexture.loadFromFile("Assets/Credits/circle4a.png");
	summoningCircleSprite.setTexture(summoningCircleTexture);
	summoningCircleSprite.setOrigin(summoningCircleTexture.getSize().x / 2, summoningCircleTexture.getSize().y / 2);
	summoningCircleSprite.setScale(0.6, 0.6);
	summoningCircleSprite.setPosition(screenW / 2, screenH / 2);
}

//destructor
Credits::~Credits()
{

}

//update
void Credits::Update()
{

}

//draw. param: render target
void Credits::Draw(sf::RenderTarget& window)
{
	window.draw(summoningCircleSprite);
}