#include "stdafx.h"
#include "Player.h"

//constructor(param is a font)
Player::Player(sf::Font f) : font(f)
{
	setPosition(500, 400);//400

	isRunning = false;

	currentDirection = SOUTH;
	previousDirection = SOUTH;
	lockedDirection = 5;//assigning a number that does not correspond to a valid direction so that it does not lock anything yet

	boundingBox.setOutlineThickness(2);
	boundingBox.setOutlineColor(sf::Color::Green);
	boundingBox.setFillColor(sf::Color::Transparent);

	health = 75;
}

//destructor
Player::~Player()
{

}

void Player::Update()
{
	if (!colliding)// && (getPosition().x != preCollisionPosition.x || getPosition().y != preCollisionPosition.y))//if we are not colliding with something
	{
		if (getPosition().x != preCollisionPosition.x)
			preCollisionPosition.x = getPosition().x;
		if (getPosition().y != preCollisionPosition.y)
			preCollisionPosition.y = getPosition().y;
		//preCollisionPosition = getPosition();
	}

	if (isRunning)
		animationTime = 0.1;
	else animationTime = 0.18;
	Animate();
}

//Set the player's texture based on their chosen race
void Player::setTextures()
{
	numFrames = 3;
	animationClock.restart();
	animationTime = 0.2;

	if (race == HUMAN)//if the player is a human
	{
		if (gender == MALE)//if the player is male
		{
			upIdleTexture.loadFromFile("Assets/Player/Human/Male/Idle/upIdle.png");
			downIdleTexture.loadFromFile("Assets/Player/Human/Male/Idle/downIdle.png");
			leftIdleTexture.loadFromFile("Assets/Player/Human/Male/Idle/leftIdle.png");
			rightIdleTexture.loadFromFile("Assets/Player/Human/Male/Idle/rightIdle.png");

			upWalkTexture.loadFromFile("Assets/Player/Human/Male/Moving/upSheet.png");
			downWalkTexture.loadFromFile("Assets/Player/Human/Male/Moving/downSheet.png");
			leftWalkTexture.loadFromFile("Assets/Player/Human/Male/Moving/leftSheet.png");
			rightWalkTexture.loadFromFile("Assets/Player/Human/Male/Moving/rightSheet.png");
		}
		else if (gender == FEMALE)//if the player is female
		{
			upIdleTexture.loadFromFile("Assets/Player/Human/Female/Idle/upIdle.png");
			downIdleTexture.loadFromFile("Assets/Player/Human/Female/Idle/downIdle.png");
			leftIdleTexture.loadFromFile("Assets/Player/Human/Female/Idle/leftIdle.png");
			rightIdleTexture.loadFromFile("Assets/Player/Human/Female/Idle/rightIdle.png");

			upWalkTexture.loadFromFile("Assets/Player/Human/Female/Moving/upSheet.png");
			downWalkTexture.loadFromFile("Assets/Player/Human/Female/Moving/downSheet.png");
			leftWalkTexture.loadFromFile("Assets/Player/Human/Female/Moving/leftSheet.png");
			rightWalkTexture.loadFromFile("Assets/Player/Human/Female/Moving/rightSheet.png");
		}

		scale(1.3, 1.3);
	}
	else if (race == ELF)//if the player is an elf
	{
		if (gender == MALE)//if the player is male
		{
			upIdleTexture.loadFromFile("Assets/Player/Elf/Male/Idle/upIdle.png");
			downIdleTexture.loadFromFile("Assets/Player/Elf/Male/Idle/downIdle.png");
			leftIdleTexture.loadFromFile("Assets/Player/Elf/Male/Idle/leftIdle.png");
			rightIdleTexture.loadFromFile("Assets/Player/Elf/Male/Idle/rightIdle.png");

			upWalkTexture.loadFromFile("Assets/Player/Elf/Male/Moving/upSheet.png");
			downWalkTexture.loadFromFile("Assets/Player/Elf/Male/Moving/downSheet.png");
			leftWalkTexture.loadFromFile("Assets/Player/Elf/Male/Moving/leftSheet.png");
			rightWalkTexture.loadFromFile("Assets/Player/Elf/Male/Moving/rightSheet.png");
		}
		else if (gender == FEMALE)//if the player is a female
		{
			upIdleTexture.loadFromFile("Assets/Player/Elf/Female/Idle/upIdle.png");
			downIdleTexture.loadFromFile("Assets/Player/Elf/Female/Idle/downIdle.png");
			leftIdleTexture.loadFromFile("Assets/Player/Elf/Female/Idle/leftIdle.png");
			rightIdleTexture.loadFromFile("Assets/Player/Elf/Female/Idle/rightIdle.png");

			upWalkTexture.loadFromFile("Assets/Player/Elf/Female/Moving/upSheet.png");
			downWalkTexture.loadFromFile("Assets/Player/Elf/Female/Moving/downSheet.png");
			leftWalkTexture.loadFromFile("Assets/Player/Elf/Female/Moving/leftSheet.png");
			rightWalkTexture.loadFromFile("Assets/Player/Elf/Female/Moving/rightSheet.png");
		}

		scale(1.3, 1.4);
	}
	else if (race == Dwarf)//if the player is a dwarf
	{
		if (gender == MALE)//if the player is male
		{
			upIdleTexture.loadFromFile("Assets/Player/Dwarf/Male/Idle/upIdle.png");
			downIdleTexture.loadFromFile("Assets/Player/Dwarf/Male/Idle/downIdle.png");
			leftIdleTexture.loadFromFile("Assets/Player/Dwarf/Male/Idle/leftIdle.png");
			rightIdleTexture.loadFromFile("Assets/Player/Dwarf/Male/Idle/rightIdle.png");

			upWalkTexture.loadFromFile("Assets/Player/Dwarf/Male/Moving/upSheet.png");
			downWalkTexture.loadFromFile("Assets/Player/Dwarf/Male/Moving/downSheet.png");
			leftWalkTexture.loadFromFile("Assets/Player/Dwarf/Male/Moving/leftSheet.png");
			rightWalkTexture.loadFromFile("Assets/Player/Dwarf/Male/Moving/rightSheet.png");
		}
		else if (gender == FEMALE)//if the player is female
		{
			upIdleTexture.loadFromFile("Assets/Player/Dwarf/Female/Idle/upIdle.png");
			downIdleTexture.loadFromFile("Assets/Player/Dwarf/Female/Idle/downIdle.png");
			leftIdleTexture.loadFromFile("Assets/Player/Dwarf/Female/Idle/leftIdle.png");
			rightIdleTexture.loadFromFile("Assets/Player/Dwarf/Female/Idle/rightIdle.png");

			upWalkTexture.loadFromFile("Assets/Player/Dwarf/Female/Moving/upSheet.png");
			downWalkTexture.loadFromFile("Assets/Player/Dwarf/Female/Moving/downSheet.png");
			leftWalkTexture.loadFromFile("Assets/Player/Dwarf/Female/Moving/leftSheet.png");
			rightWalkTexture.loadFromFile("Assets/Player/Dwarf/Female/Moving/rightSheet.png");
		}

		scale(2, 2.1);
	}

	framePosition = sf::Vector2i(0, 0);

	setTexture(downIdleTexture);
	setOrigin(downIdleTexture.getSize().x / 2, downIdleTexture.getSize().y / 2);

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

		setTexture(upWalkTexture);
	}
	else if (currentDirection == SOUTH && lockedDirection != currentDirection)
	{
		if (isRunning == false)
			setPosition(getPosition().x, getPosition().y + 1);
		else setPosition(getPosition().x, getPosition().y + 2);

		setTexture(downWalkTexture);
	}
	else if (currentDirection == EAST && lockedDirection != currentDirection)
	{
		if (isRunning == false)
			setPosition(getPosition().x + 1, getPosition().y);
		else setPosition(getPosition().x + 2, getPosition().y);

		setTexture(rightWalkTexture);
	}
	else if (currentDirection == WEST && lockedDirection != currentDirection)
	{
		if (isRunning == false)
			setPosition(getPosition().x - 1, getPosition().y);
		else setPosition(getPosition().x - 2, getPosition().y);

		setTexture(leftWalkTexture);
	}

	frameSize = sf::Vector2i(getTexture()->getSize().x / numFrames, getTexture()->getSize().y);
	frame = sf::IntRect(framePosition, frameSize);
	setTextureRect(frame);
	setOrigin(frameSize.x / 2, frameSize.y / 2);

	previousDirection = currentDirection;
}

void Player::Animate()
{
	//idle
	if (currentDirection == NOTMOVING)
	{
		if (previousDirection == NORTH)
			setTexture(upIdleTexture);
		else if (previousDirection == SOUTH)
			setTexture(downIdleTexture);
		else if (previousDirection == WEST)
			setTexture(leftIdleTexture);
		else if (previousDirection == EAST)
			setTexture(rightIdleTexture);

		frameSize = sf::Vector2i(getTexture()->getSize().x, getTexture()->getSize().y);
		frame = sf::IntRect(framePosition, frameSize);
		setTextureRect(frame);
		setOrigin(frameSize.x / 2, frameSize.y / 2);
		framePosition.x = 0;
	}
	//moving
	else
	{
		if (animationClock.getElapsedTime().asSeconds() > animationTime)
		{
			if (framePosition.x <  getTexture()->getSize().x - frameSize.x)
				framePosition.x += frameSize.x;//move the frame forward

			else framePosition.x = 0;

			animationClock.restart();
		}
	}
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
