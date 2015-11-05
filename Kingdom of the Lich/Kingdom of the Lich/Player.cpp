#include "stdafx.h"
#include "Player.h"

Player::Player(sf::Font f) : font(f)
{
	//load the correct texture or load the debug texture if something is wrong
	if (mTexture.loadFromFile("Assets/Icons/goldskull.png")) {}
	else mTexture.loadFromFile("Assets/Debug.png");	//if it fails load placeholder
	mSprite.setOrigin(sf::Vector2f(mTexture.getSize().x / 2, mTexture.getSize().y / 2));
	mSprite.setTexture(mTexture);
	setPosition(400, 400);

	isRunning = false;

	hudBackgroundTexture.loadFromFile("Assets/HudBackground.png");
	hudBackground.setTexture(hudBackgroundTexture);
	hudBackground.setPosition(0, 600);
	currentQuestText.setFont(font);
	currentQuestText.setColor(sf::Color::Black);
	currentQuestText.setString("Current Quest Name: ");
	currentQuestText.setPosition(500, 550);
	currentQuestText.setCharacterSize(12);

	compass = new Compass();
	currentDirection = NOTMOVING;
	lockedDirection = 5;//assigning a number that does not correspond to a valid direction so that it does not lock anything yet
}

Player::~Player()
{

}

void Player::Update(sf::Vector2f objectivePos, std::string currentQuestName)
{
	hudBackground.setPosition(sf::Vector2f(getPosition().x - 400, getPosition().y + 200));
	currentQuestText.setPosition(sf::Vector2f(getPosition().x + 140, getPosition().y + 200));
	currentQuestText.setString("Current Quest Name: " + currentQuestName);
	compass->UpdateNeedle(getPosition(), objectivePos);
}

void Player::setTextures()
{
	if (race == HUMAN)
		mTexture.loadFromFile("Assets/Icons/humanSkull.png");
	else if(race == ELF)
		mTexture.loadFromFile("Assets/Icons/elfSkull.png");
	else if(race == BEASTMAN)
		mTexture.loadFromFile("Assets/Icons/beastmanSkull.png");

	mSprite.setOrigin(sf::Vector2f(mTexture.getSize().x / 2, mTexture.getSize().y / 2));
	mSprite.setTexture(mTexture);
}

void Player::Move(int newDir)
{
	currentDirection = newDir;

	if (currentDirection == NORTH && lockedDirection!= currentDirection)
	{
		if(isRunning == false)
			setPosition(getPosition().x, getPosition().y -1);
		else setPosition(getPosition().x, getPosition().y - 2);
	}
	else if (currentDirection == SOUTH && lockedDirection != currentDirection)
	{
		if (isRunning == false)
			setPosition(getPosition().x, getPosition().y + 1);
		else setPosition(getPosition().x, getPosition().y + 2);
	}
	else if (currentDirection == EAST && lockedDirection != currentDirection)
	{
		if (isRunning == false)
			setPosition(getPosition().x + 1, getPosition().y);
		else setPosition(getPosition().x + 2, getPosition().y);
	}
	else if (currentDirection == WEST && lockedDirection != currentDirection)
	{
		if (isRunning == false)
			setPosition(getPosition().x - 1, getPosition().y);
		else setPosition(getPosition().x - 2, getPosition().y);
	}
}

bool Player::CollisionWithChest(sf::Sprite chestSprite)//, Inventory* inv)
{
	if (chestSprite.getGlobalBounds().contains(getPosition()))
	{
		if (currentDirection != NOTMOVING)
			lockedDirection = currentDirection;
		return true;
	}
	else
	{
		lockedDirection = 5;//assigning a number that does not correspond to a valid direction so that it does not lock anything if they are not colliding
		return false;
	}
}

bool Player::CollisionWithNpc(Npc* npc)
{
	if (npc->getGlobalBounds().contains(getPosition()))
	{
		if (currentDirection != NOTMOVING)
			lockedDirection = currentDirection;
		std::cout << lockedDirection << std::endl;
		std::cout << currentDirection << std::endl;
		return true;
	}
	else
	{
		lockedDirection = 5;//assigning a number that does not correspond to a valid direction so that it does not lock anything if they are not colliding
		return false;
	}
}

void Player::draw(sf::RenderTarget& window, sf::RenderStates state) const{}

void Player::draw(sf::RenderTarget& window)
{
	window.draw(hudBackground);
	window.draw(currentQuestText);
	compass->draw(window);
	window.draw(mSprite, getTransform());
}
