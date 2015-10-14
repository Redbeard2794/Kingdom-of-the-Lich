#include "stdafx.h"
#include "Player.h"

Player::Player()
{
	//load the correct texture or load the debug texture if something is wrong
	if (mTexture.loadFromFile("Assets/Icons/goldskull.png")) {}
	else mTexture.loadFromFile("Assets/Debug.png");	//if it fails load placeholder
	mSprite.setOrigin(sf::Vector2f(mTexture.getSize().x / 2, mTexture.getSize().y / 2));
	mSprite.setTexture(mTexture);
	setPosition(200, 200);
}

Player::~Player()
{

}

void Player::Update()
{

}

void Player::Move(sf::Vector2f direction)
{
	setPosition(getPosition() + direction);
}

void Player::draw(sf::RenderTarget& window, sf::RenderStates state) const{}

void Player::draw(sf::RenderTarget& window)
{
	window.draw(mSprite, getTransform());
}