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
	isRunning = false;

	hudBackgroundTexture.loadFromFile("Assets/HudBackground.png");
	hudBackground.setTexture(hudBackgroundTexture);
	hudBackground.setPosition(0, 600);

	compass = new Compass();
}

Player::~Player()
{

}

void Player::Update()
{
	hudBackground.setPosition(sf::Vector2f(getPosition().x - 400, getPosition().y + 200));
	compass->UpdateNeedle(getPosition(), sf::Vector2f(400, 200));
}

void Player::Move(sf::Vector2f direction)
{
	setPosition(getPosition() + direction);
}

void Player::draw(sf::RenderTarget& window, sf::RenderStates state) const{}

void Player::draw(sf::RenderTarget& window)
{
	window.draw(hudBackground);
	compass->draw(window);
	window.draw(mSprite, getTransform());
}
