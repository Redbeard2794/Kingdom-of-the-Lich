#include "stdafx.h"
#include "Player.h"

Player::Player(sf::String r, sf::String g, sf::String c)
{
	//load the correct texture or load the debug texture if something is wrong
	if (mTexture.loadFromFile("Assets/Icons/goldskull.png")) {}
	else mTexture.loadFromFile("Assets/Debug.png");	//if it fails load placeholder
	mSprite.setOrigin(sf::Vector2f(mTexture.getSize().x / 2, mTexture.getSize().y / 2));
	mSprite.setTexture(mTexture);
	setPosition(400, 400);

	race = r;
	gender = g;
	playerClass = c;

	std::cout << "Race: " + race.toAnsiString() << ", Gender: " + gender.toAnsiString() << ", Class: " + playerClass.toAnsiString() << std::endl;

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