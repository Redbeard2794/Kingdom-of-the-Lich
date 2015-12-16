#include "stdafx.h"
#include "Player.h"

//constructor(param is a font)
Player::Player(sf::Font f) : font(f)
{
	//load the correct texture or load the debug texture if something is wrong
	if (mTexture.loadFromFile("Assets/Icons/goldskull.png")) {}
	else mTexture.loadFromFile("Assets/Debug.png");	//if it fails load placeholder
	setOrigin(sf::Vector2f(mTexture.getSize().x / 2, mTexture.getSize().y / 2));
	setTexture(mTexture);
	setPosition(500, 400);

	isRunning = false;

	currentDirection = NOTMOVING;
	lockedDirection = 5;//assigning a number that does not correspond to a valid direction so that it does not lock anything yet

	boundingBox.setOutlineThickness(2);
	boundingBox.setOutlineColor(sf::Color::Green);
	boundingBox.setFillColor(sf::Color::Transparent);

	health = 100;
}

//destructor
Player::~Player()
{

}

void Player::Update()
{
	if (!colliding && (getPosition().x != preCollisionPosition.x || getPosition().y != preCollisionPosition.y))//if we are not colliding with something
	{
		preCollisionPosition = getPosition();
	}
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

	setOrigin(sf::Vector2f(mTexture.getSize().x / 2, mTexture.getSize().y / 2));
	setTexture(mTexture);

	//set up player's minimap icon
	if (minimapTexture.loadFromFile("Assets/Player/minimapIcon/playerMinimapIcon2.png")) {}
	else minimapTexture.loadFromFile("Assets/Debug.png");	//if it fails load placeholder
	minimapSprite.setTexture(minimapTexture);
	minimapSprite.setOrigin(minimapTexture.getSize().x / 2, minimapTexture.getSize().y / 2);
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

/*draw the player on the minimap*/
void Player::MinimapDraw(sf::RenderTarget& window)
{
	window.draw(minimapSprite, getTransform());
}

void Player::DrawBoundingBox(sf::RenderTarget& window)
{
	boundingBox.setPosition(sf::Vector2f(getGlobalBounds().left, getGlobalBounds().top));
	boundingBox.setSize(sf::Vector2f(getGlobalBounds().width, getGlobalBounds().height));
	boundingBox.setRotation(getRotation());
	window.draw(boundingBox);
}
