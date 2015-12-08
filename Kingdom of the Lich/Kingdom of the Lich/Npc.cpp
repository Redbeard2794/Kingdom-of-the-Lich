#include "stdafx.h"
#include "Npc.h"

//name, id, race, gender, texturePath, mapIconTexturePath, x, y, hasQuest, behaviour, show keyboard or controller hint
Npc::Npc(std::string n, int i, std::string idleUpPath, std::string idleDownPath, std::string idleLeftPath, std::string idleRightPath,
	int numFrames, std::string walkUpPath, std::string walkDownPath, std::string walkLeftPath, std::string walkRightPath, std::string mapIconTexturePath, 
	sf::Vector2f pos, bool quest, std::string beh, bool controller)
	: name(n), id(i), hasQuest(quest), behaviour(beh), numberOfFrames(numFrames)
{
	//load all idle textures
	if (downIdleTexture.loadFromFile(idleDownPath)) { }
	else downIdleTexture.loadFromFile("Assets/Debug.png");
	if (upIdleTexture.loadFromFile(idleUpPath)) { }
	else upIdleTexture.loadFromFile("Assets/Debug.png");
	if (rightIdleTexture.loadFromFile(idleRightPath)) { }
	else rightIdleTexture.loadFromFile("Assets/Debug.png");
	if (leftIdleTexture.loadFromFile(idleLeftPath)) { }
	else leftIdleTexture.loadFromFile("Assets/Debug.png");
	//load all walking sprite sheets
	if (upWalkTexture.loadFromFile(walkUpPath)) { }
	else upWalkTexture.loadFromFile("Assets/Debug.png");
	if (downWalkTexture.loadFromFile(walkDownPath)) { }
	else downWalkTexture.loadFromFile("Assets/Debug.png");
	if (leftWalkTexture.loadFromFile(walkLeftPath)) { }
	else leftWalkTexture.loadFromFile("Assets/Debug.png");
	if (rightWalkTexture.loadFromFile(walkRightPath)) { }
	else rightWalkTexture.loadFromFile("Assets/Debug.png");

	framePosition = sf::Vector2i(0, 0);
	idle = true;
	currentDirection = DOWN;

	setTexture(downIdleTexture);
	setOrigin(downIdleTexture.getSize().x / 2, downIdleTexture.getSize().y / 2);
	setPosition(pos);
	prevPos = getPosition();

	if (npcMinimapIconTexture.loadFromFile(mapIconTexturePath)) {}
	else npcMinimapIconTexture.loadFromFile("Assets/Debug.png");	//if it fails load placeholder
	npcMinimapIcon.setTexture(npcMinimapIconTexture);
	npcMinimapIcon.setOrigin(npcMinimapIconTexture.getSize().x / 2, npcMinimapIconTexture.getSize().y / 2);
	npcMinimapIcon.setPosition(pos);

	LoadInteractHintTexture(controller);

	if (behaviour == "wander")//if the npc is to wander
	{
		wanderPos = sf::Vector2f(getPosition().x + (rand() % 100 + 10), getPosition().y);
		std::cout << name << " is wandering to " << wanderPos.x << ", " << wanderPos.y << std::endl;
		timeBetweenWander = rand() % 7 + 2;
	}
	else if (behaviour == "walkPattern")//if the npc is to walk around in a pattern
	{
		patternPoints.push_back(getPosition());
		patternPoints.push_back(sf::Vector2f(patternPoints.at(0).x, patternPoints.at(0).y + 400));
		patternPoints.push_back(sf::Vector2f(patternPoints.at(1).x-400, patternPoints.at(1).y));
		patternPoints.push_back(sf::Vector2f(patternPoints.at(2).x, patternPoints.at(2).y - 400));
		currentPointIndex = 0;
		prevPointIndex = 5;
	}
}

//Load the correct texture for the interact hint
void Npc::LoadInteractHintTexture(bool controllerHint)
{
	if (controllerHint == true)
	{
		if (interactHintTexture.loadFromFile("Assets/ControllerHints/pressAtoTalkHint.png")) {}
		else interactHintTexture.loadFromFile("Assets/Debug.png");	//if it fails load placeholder
	}
	else
	{
		if (interactHintTexture.loadFromFile("Assets/KeyboardAndMouseHints/pressEtoTalkHint.png")) {}
		else interactHintTexture.loadFromFile("Assets/Debug.png");	//if it fails load placeholder
	}
	interactHintSprite.setTexture(interactHintTexture);
	interactHintSprite.setOrigin(interactHintTexture.getSize().x / 2, interactHintTexture.getSize().y / 2);
	interactHintSprite.setPosition(sf::Vector2f(getPosition().x,getPosition().y+50));
}

Npc::~Npc()
{

}

void Npc::Update(sf::Vector2f playerPos)
{
	sf::Vector2f pos = getPosition();
	float distance = sqrtf((((pos.x - playerPos.x)*(pos.x - playerPos.x)) + ((pos.y - playerPos.y)*(pos.y - playerPos.y))));
	
	//show the interaction hint sprite
	if(distance < 25)
		interactHintSprite.setColor(sf::Color::White);
	else interactHintSprite.setColor(sf::Color::Transparent);

	npcMinimapIcon.setPosition(getPosition());

	if (idle == false)
	{
		if (animationClock.getElapsedTime().asMilliseconds() > 55)
		{
			if (framePosition.x < getTexture()->getSize().x-frameSize.x)
				framePosition.x += frameSize.x;

			else framePosition.x = 0;

			animationClock.restart();
		}
	}
	else
	{
		if (currentDirection == UP)
			setTexture(upIdleTexture);
		else if (currentDirection == DOWN)
			setTexture(downIdleTexture);
		else if (currentDirection == LEFT)
			setTexture(leftIdleTexture);
		else if (currentDirection == RIGHT)
			setTexture(rightIdleTexture);

		framePosition = sf::Vector2i(0, 0);
		frameSize = sf::Vector2i(getTexture()->getSize().x, getTexture()->getSize().y);
		frame = sf::IntRect(framePosition, frameSize);
		setTextureRect(frame);
	}

	if (behaviour == "wander")
	{
		Wander();
	}
	else if (behaviour == "walkPattern")
	{
		walkPattern();
	}
	else if (behaviour == "follow")
	{
		Follow(playerPos);
	}

}

/*Wander to random points within 100 pixels on either the x or y and then stand there for up to 7 seconds*/
void Npc::Wander()
{
	if (behaviourClock.getElapsedTime().asSeconds() > timeBetweenWander)
	{
		idle = false;

		//get the distance between current position and position we are to wander to
		float distance = sqrtf((((getPosition().x - wanderPos.x)*(getPosition().x - wanderPos.x)) + ((getPosition().y - wanderPos.y)*(getPosition().y - wanderPos.y))));
		//get the direction
		sf::Vector2f dir = sf::Vector2f((wanderPos.x - getPosition().x) / distance, (wanderPos.y - getPosition().y) / distance);

		if (distance > 0.5)//.5 because we are dealing with floats so will never get to the exact right position
		{
			setPosition(sf::Vector2f(getPosition().x + dir.x, getPosition().y + dir.y));
		}

		else
		{
			//flip a coin to decide where we should wander to
			int coin = rand() % 2;

			if (coin == 1)//go to a new position
			{
				float xChange = rand() % 100 + 10;
				float yChange = rand() % 100 + 10;

				//make sure we can only go up, down, left or right but not more than one at a time
				int dirCoin = rand() % 2;
				if (dirCoin == 1)
					yChange = 0;
				else if (dirCoin == 0)
					xChange = 0;

				//throw in something different(make a distance to wander negative to go in the opposite direction some times)
				int negCoin = rand() % 2;
				if (yChange == 0 && negCoin == 1)
					xChange = -xChange;
				else if (xChange == 0 && negCoin == 0)
					yChange = -yChange;

				//set the next position to wnder to
				wanderPos = sf::Vector2f(getPosition().x + xChange, getPosition().y + yChange);
			}

			else wanderPos = prevPos;//go to the previous position

			//set the time between each movement
			timeBetweenWander = rand() % 7 + 2;

			//restart the clock
			behaviourClock.restart();
		}

		//sort out orientation here
		if (dir.x > 0)
		{
			currentDirection = RIGHT;
			setTexture(rightWalkTexture);
		}
		else if (dir.x < 0)
		{
			currentDirection = LEFT;
			setTexture(leftWalkTexture);
		}
		if (dir.y > 0)
		{
			currentDirection = DOWN;
			setTexture(downWalkTexture);
		}
		else if (dir.y < 0)
		{
			currentDirection = UP;
			setTexture(upWalkTexture);
		}

		frameSize = sf::Vector2i(getTexture()->getSize().x / numberOfFrames, getTexture()->getSize().y);//numberOfFrames is the number of frames
		frame = sf::IntRect(framePosition, frameSize);
		setTextureRect(frame);

	}
	else
	{
		prevPos = getPosition();
		idle = true;
	}
}

/*Walk around in a rectangle from the points set in the constructor*/
void Npc::walkPattern()
{
	idle = false;
	//deal with the first 3 points
	if (currentPointIndex < 3)
	{
		//get the distance between current position and position we are to wander to
		float distance = sqrtf((((getPosition().x - patternPoints.at(currentPointIndex+1).x)*(getPosition().x - patternPoints.at(currentPointIndex + 1).x))
			+ ((getPosition().y - patternPoints.at(currentPointIndex + 1).y)*(getPosition().y - patternPoints.at(currentPointIndex + 1).y))));
			
		if (prevPointIndex != currentPointIndex)
		{
			//get the direction, but only once per point
			direction = sf::Vector2f((patternPoints.at(currentPointIndex + 1).x - patternPoints.at(currentPointIndex).x) / distance, (patternPoints.at(currentPointIndex + 1).y - patternPoints.at(currentPointIndex).y) / distance);
			prevPointIndex = currentPointIndex;
		}

		if ((int)distance > 1)
		{
			setPosition(sf::Vector2f(getPosition().x + direction.x, getPosition().y + direction.y));
		}
		else//move onto the next point and adjust position so it is correct
		{
			currentPointIndex += 1;
			setPosition(patternPoints.at(currentPointIndex));
		}
	}

	else//deal with the last point
	{
		//get the distance between current position and position we are to wander to
		float distance = sqrtf((((getPosition().x - patternPoints.at(0).x)*(getPosition().x - patternPoints.at(0).x))
			+ ((getPosition().y - patternPoints.at(0).y)*(getPosition().y - patternPoints.at(0).y))));

		if (prevPointIndex != currentPointIndex)
		{
			//get the direction but only once per point
			direction = sf::Vector2f((patternPoints.at(0).x - patternPoints.at(currentPointIndex).x) / distance, (patternPoints.at(0).y - patternPoints.at(currentPointIndex).y) / distance);
			prevPointIndex = currentPointIndex;
		}

		if ((int)distance > 1)
		{
			setPosition(sf::Vector2f(getPosition().x + direction.x, getPosition().y + direction.y));
		}
		else //go back to the first point and adjust position so it is correct
		{
			currentPointIndex = 0;
			setPosition(patternPoints.at(currentPointIndex));
		}
	}

	//sort out orientation here
	if (direction.x > 0)
	{
		currentDirection = RIGHT;
		setTexture(rightWalkTexture);
		if (prevDirection != currentDirection)
		{
			framePosition.x = 0;
			prevDirection = currentDirection;
		}
	}
	else if (direction.x < 0)
	{
		currentDirection = LEFT;
		setTexture(leftWalkTexture);
		if (prevDirection != currentDirection)
		{
			framePosition.x = 0;
			prevDirection = currentDirection;
		}
	}
	if (direction.y > 0)
	{
		currentDirection = DOWN;
		setTexture(downWalkTexture);
		if (prevDirection != currentDirection)
		{
			framePosition.x = 0;
			prevDirection = currentDirection;
		}
	}
	else if (direction.y < 0)
	{
		currentDirection = UP;
		setTexture(upWalkTexture);
		if (prevDirection != currentDirection)
		{
			framePosition.x = 0;
			prevDirection = currentDirection;
		}
	}

	frameSize = sf::Vector2i(getTexture()->getSize().x / numberOfFrames, getTexture()->getSize().y);
	frame = sf::IntRect(framePosition, frameSize);
	setTextureRect(frame);
}

/*Follow the position that is passed in. This is a modified Seek algorithm
(it can only move up, down, left or right but can not move in more than one direction at a time). Only allows 4 directions of movement*/
void Npc::Follow(sf::Vector2f positionToFollow)
{
	//get the vector between the positionToFollow and our position
	direction = sf::Vector2f(positionToFollow - getPosition());
	//get the length of the direction
	float length = sqrtf((direction.x * direction.x) + (direction.y * direction.y));

	direction.x /= length;
	direction.y /= length;

	//move left or right
	if (getPosition().x > positionToFollow.x + 10 || getPosition().x < positionToFollow.x - 10)//let them get roughly close because we are dealing with floats so will never be exact
	{
		setPosition(sf::Vector2f(getPosition().x + direction.x, getPosition().y));
		direction.y = 0;
	}
	//move up or down
	else if (getPosition().y > positionToFollow.y + 10 || getPosition().y < positionToFollow.y - 10)//let them get roughly close because we are dealing with floats so will never be exact
	{
		setPosition(sf::Vector2f(getPosition().x, getPosition().y + direction.y));
		direction.x = 0;
	}
	else
	{
		direction = sf::Vector2f(0, 0);
	}

	//sort out orientation here
	if (direction.x > 0)
	{
		idle = false;
		currentDirection = RIGHT;
		setTexture(rightWalkTexture);
		if (prevDirection != currentDirection)
		{
			framePosition.x = 0;
			prevDirection = currentDirection;
		}
	}
	else if (direction.x < 0)
	{
		idle = false;
		currentDirection = LEFT;
		setTexture(leftWalkTexture);
		if (prevDirection != currentDirection)
		{
			framePosition.x = 0;
			prevDirection = currentDirection;
		}
	}
	if (direction.y > 0)
	{
		idle = false;
		currentDirection = DOWN;
		setTexture(downWalkTexture);
		if (prevDirection != currentDirection)
		{
			framePosition.x = 0;
			prevDirection = currentDirection;
		}
	}
	else if (direction.y < 0)
	{
		idle = false;
		currentDirection = UP;
		setTexture(upWalkTexture);
		if (prevDirection != currentDirection)
		{
			framePosition.x = 0;
			prevDirection = currentDirection;
		}
	}

	frameSize = sf::Vector2i(getTexture()->getSize().x / numberOfFrames, getTexture()->getSize().y);
	frame = sf::IntRect(framePosition, frameSize);
	setTextureRect(frame);

	if (direction.x == 0 && direction.y == 0)
	{
		idle = true;
		if (currentDirection == UP)
			setTexture(upIdleTexture);
		else if (currentDirection == DOWN)
			setTexture(downIdleTexture);
		else if (currentDirection == LEFT)
			setTexture(leftIdleTexture);
		else if (currentDirection == RIGHT)
			setTexture(rightIdleTexture);

		framePosition = sf::Vector2i(0, 0);
		frameSize = sf::Vector2i(getTexture()->getSize().x, getTexture()->getSize().y);
		frame = sf::IntRect(framePosition, frameSize);
		setTextureRect(frame);
	}
}

/*Draw the interaction hint sprite*/
void Npc::draw(sf::RenderTarget& window)
{
	window.draw(interactHintSprite);
}

/*Draw the npc on the minimap as an icon*/
void Npc::MinimapDraw(sf::RenderTarget& window)
{
	window.draw(npcMinimapIcon);
	interactHintSprite.setPosition(sf::Vector2f(getPosition().x, getPosition().y + 50));
}

std::string Npc::getNpcName()
{
	return name;
}

int Npc::getNpcId()
{
	return id;
}

bool Npc::doesNpcHaveQuest()
{
	return hasQuest;
}

std::string Npc::getBehaviour()
{
	return behaviour;
}
