#include "stdafx.h"
#include "Player.h"

//constructor(param is a font)
Player::Player(sf::Font f) : font(f)
{
	//load the correct texture or load the debug texture if something is wrong
	if (mTexture.loadFromFile("Assets/Icons/goldskull.png")) {}
	else mTexture.loadFromFile("Assets/Debug.png");	//if it fails load placeholder
	mSprite.setOrigin(sf::Vector2f(mTexture.getSize().x / 2, mTexture.getSize().y / 2));
	mSprite.setTexture(mTexture);
	setPosition(500, 400);

	isRunning = false;

	currentDirection = NOTMOVING;
	lockedDirection = 5;//assigning a number that does not correspond to a valid direction so that it does not lock anything yet
}

//destructor
Player::~Player()
{

}

void Player::Update()
{

}

//Set the player's texture based on their chosen race
void Player::setTextures()
{
	if (race == HUMAN)
		mTexture.loadFromFile("Assets/Icons/humanSkull.png");
	else if(race == ELF)
		mTexture.loadFromFile("Assets/Icons/elfSkull.png");
	else if(race == Dwarf)
		mTexture.loadFromFile("Assets/Icons/beastmanSkull.png");

	mSprite.setOrigin(sf::Vector2f(mTexture.getSize().x / 2, mTexture.getSize().y / 2));
	mSprite.setTexture(mTexture);
}

void Player::Move(int newDir)
{
	currentDirection = newDir;
	/*Move the player in the direction they are travelling in
	Don't allow them to move if that direction is locked due to collision with another object*/
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

	previousDirection = currentDirection;
}

/*Check to see if the player is colliding with a chest*/
bool Player::CollisionWithChest(sf::Sprite chestSprite)
{
	/*If the player is colliding with a chest then lock the direction they are travelling in currently so that they can't move further*/
	if (chestSprite.getGlobalBounds().contains(getPosition()))
	{
		if (previousDirection != NOTMOVING)
			lockedDirection = previousDirection;
		return true;
	}
	else
	{
		lockedDirection = 5;//assigning a number that does not correspond to a valid direction so that it does not lock anything if they are not colliding
		return false;
	}
}

/*Check to see if the player is colliding with an npc*/
bool Player::CollisionWithNpc(Npc* npc)
{
	/*If the player is colliding with an npc then lock the direction they are travelling in currently so that they can't move further*/
	sf::Vector2f pos = getPosition();
	if (npc->getGlobalBounds().contains(pos))
	{
		if (previousDirection != NOTMOVING)
			lockedDirection = previousDirection;
		return true;
	}
	else
	{
		lockedDirection = 5;//assigning a number that does not correspond to a valid direction so that it does not lock anything if they are not colliding
		return false;
	}
}

void Player::draw(sf::RenderTarget& window, sf::RenderStates state) const{}

/*Draw the player*/
void Player::draw(sf::RenderTarget& window)
{
	window.draw(mSprite, getTransform());
}
