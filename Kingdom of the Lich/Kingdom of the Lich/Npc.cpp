#include "stdafx.h"
#include "Npc.h"

//name, id, race, gender, texturePath, mapIconTexturePath, x, y, hasQuest, behaviour, show keyboard or controller hint
Npc::Npc(std::string n, int i, std::string idleUpPath, std::string idleDownPath, std::string idleLeftPath, std::string idleRightPath,
	int numFrames, std::string walkUpPath, std::string walkDownPath, std::string walkLeftPath, std::string walkRightPath, std::string mapIconTexturePath, 
	sf::Vector2f pos, std::string quest, std::string interact, std::string beh, bool controller)
	: name(n), id(i), currentBehaviour(beh), numberOfFrames(numFrames)
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
	

	if (currentBehaviour == "forge")
	{
		setTexture(leftIdleTexture);
		setOrigin(leftIdleTexture.getSize().x / 2, leftIdleTexture.getSize().y / 2);
		currentDirection = LEFT;
		atAnvil = true;
		atForge = false;
		behaviourClock.restart();
		anvilAnimTime = 0.4;
		forgeAnimTime = 1;
		workPoint = 0;
		workAnimTexture.loadFromFile("Assets/Npcs/blacksmith/hammerSheet.png");
	}
	else
	{
		setTexture(downIdleTexture);
		setOrigin(downIdleTexture.getSize().x / 2, downIdleTexture.getSize().y / 2);
		currentDirection = DOWN;
	}
	setPosition(pos);
	prevPos = getPosition();
	scale(2.6, 2.9);

	if (npcMinimapIconTexture.loadFromFile(mapIconTexturePath)) {}
	else npcMinimapIconTexture.loadFromFile("Assets/Debug.png");	//if it fails load placeholder
	npcMinimapIcon.setTexture(npcMinimapIconTexture);
	npcMinimapIcon.setOrigin(npcMinimapIconTexture.getSize().x / 2, npcMinimapIconTexture.getSize().y / 2);
	npcMinimapIcon.setPosition(pos);

	LoadInteractHintTexture(controller);

	//if (currentBehaviour == "wander" || currentBehaviour == "patrol")//if the npc is to wander
	//{
		wanderPos = sf::Vector2f(getPosition().x + (rand() % 100 + 10), getPosition().y);
		std::cout << name << " is wandering to " << wanderPos.x << ", " << wanderPos.y << std::endl;
		timeBetweenWander = rand() % 7 + 2;
		wanderCount = 0;
	//}
	if (currentBehaviour == "walkPattern")//if the npc is to walk around in a pattern
	{
		patternPoints.push_back(getPosition());
		patternPoints.push_back(sf::Vector2f(patternPoints.at(0).x, patternPoints.at(0).y + 400));
		patternPoints.push_back(sf::Vector2f(patternPoints.at(1).x-400, patternPoints.at(1).y));
		patternPoints.push_back(sf::Vector2f(patternPoints.at(2).x, patternPoints.at(2).y - 400));
		currentPointIndex = 0;
		prevPointIndex = 5;
	}

	colliding = false;
	boundingBox.setOutlineThickness(2);
	boundingBox.setOutlineColor(sf::Color(20, 69, 247, 255));
	boundingBox.setFillColor(sf::Color::Transparent);

	if (interact == "true")
		interactable = true;
	else interactable = false;

	if (quest == "true")
		hasQuest = true;
	else hasQuest = false;

	footprintEmitter = new FootprintEmitter(sf::Vector2f(0, 0), 0.3f, 1);

	timeForBed = false;
	inBed = false;

	bedTexture.loadFromFile("Assets/bedRoll.png");
	bedSprite.setTexture(bedTexture);
	bedSprite.setOrigin(bedTexture.getSize().x / 2, bedTexture.getSize().y / 2);
	//bedSprite.scale(0.8, 0.8);

	patrolPoint1 = sf::Vector2f(rand() % 1000 + 400, 400);
	patrolPoint2 = sf::Vector2f(rand() % 1000 + 400, 400);
	patrolPoint3 = sf::Vector2f(rand() % 1000 + 400, 800);
	patrolPoint4 = sf::Vector2f(rand() % 1000 + 400, 800);
	patrolPointsPicked = true;
	patrolWanderClock.restart();
	currentPatrolPoint = 1;

	
	font.loadFromFile("Assets/Kelt Caps Freehand.TTF");
	greetingText.setString("");
	greetingText.setPosition(sf::Vector2f(getPosition().x + 20, getPosition().y - 60));
	greetingText.setFont(font);
	greetingText.setCharacterSize(12);
	greetingText.setColor(sf::Color::Black);
	displayGreeting = false;
	greetingClock.restart();

	speechBubbleTexture.loadFromFile("Assets/Greetings/speechBubble.png");
	speechBubbleSprite.setTexture(speechBubbleTexture);
	speechBubbleSprite.setOrigin(0, speechBubbleTexture.getSize().y / 2);
	speechBubbleSprite.setPosition(sf::Vector2f(getPosition().x + 10, getPosition().y - 40));
	speechBubbleSprite.scale(2, 1);

	itemStolen = false;

	appleStartPoint = sf::Vector2f(1160, 1500);
	appleEndPoint = sf::Vector2f(1160, 1725);
	spotPicked = false;
	reachedAppleStart = false;
	currentApplePoint = 0;
	applePoints.push_back(appleStartPoint);
	applePoints.push_back(sf::Vector2f(appleStartPoint.x, appleStartPoint.y + 50));
	applePoints.push_back(sf::Vector2f(appleStartPoint.x, appleStartPoint.y + 100));
	applePoints.push_back(sf::Vector2f(appleStartPoint.x, appleStartPoint.y + 150));
	applePoints.push_back(appleEndPoint);

	wanderClock.restart();

	eatClock.restart();
	eating = true;
	foodTexture.loadFromFile("Assets/Icons/Items/apple.png");
	foodSprite.setTexture(foodTexture);
	foodSprite.setOrigin(foodTexture.getSize().x / 2, foodTexture.getSize().y / 2);
	foodSprite.setPosition(sf::Vector2f(getPosition().x, getPosition().y - 10));
	foodSprite.scale(.25, .25);
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
	distanceToPlayer = sqrtf((((pos.x - playerPos.x)*(pos.x - playerPos.x)) + ((pos.y - playerPos.y)*(pos.y - playerPos.y))));
	
	//show the interaction hint sprite
	//if(distanceToPlayer < 50)
	//	interactHintSprite.setColor(sf::Color::White);
	//else interactHintSprite.setColor(sf::Color::Transparent);

	if (interactable == true)//if the npc is interactable
	{
		if (showHint)//and we are to show the hint
			interactHintSprite.setColor(sf::Color::White);
		else interactHintSprite.setColor(sf::Color::Transparent);
	}

	npcMinimapIcon.setPosition(getPosition());

	if (idle == false)
	{
		if (animationClock.getElapsedTime().asSeconds() > 0.2)
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

	if (!timeForBed)
	{
		if (currentBehaviour == "patrol")
		{
			Patrol();
		}
		else if (currentBehaviour == "forge")
		{
			Forge();
		}
		else if (currentBehaviour == "steal")
		{
			if(itemStolen == false)
				Follow(playerPos, true);
			else
			{
				//evade when player is in range
				AvoidPlayer(playerPos);
			}
		}
		else if (currentBehaviour == "pickApples")
		{
			if(reachedAppleStart == true)
				PickApples();
			else Follow(applePoints.at(currentApplePoint), true);
		}
		else if (currentBehaviour == "eating")
		{
			Eat();
		}
		else if (currentBehaviour == "wander")
		{
			Wander();
		}
		else if (currentBehaviour == "walkPattern")
		{
			walkPattern();
		}
		else if (currentBehaviour == "follow")
		{
			if (distanceToPlayer < 300 && colliding == false)
			{
				Follow(playerPos, true);
			}
			else
			{
				idle = true;
				if (colliding == true)
				{
					setPosition(sf::Vector2f(getPosition().x - direction.x, getPosition().y - direction.y));
				}
			}
		}
	}
	else
	{
		if(!inBed)
			GoToBed(bedPos);
		else
		{
			setPosition(sf::Vector2f(bedPos.x + 5, bedPos.y - 10));
			bedSprite.setPosition(sf::Vector2f(bedPos.x, bedPos.y + 15));
			//currentDirection = DOWN;
		}
	}

	footprintEmitter->setPosition(sf::Vector2f(getPosition().x, getPosition().y));
	if (!idle)
	{
		if(currentDirection == RIGHT)
			footprintEmitter->SetDirection(LEFT);
		else if(currentDirection == LEFT)
			footprintEmitter->SetDirection(RIGHT);
		else footprintEmitter->SetDirection(currentDirection);
	}
	else
	{
		footprintEmitter->SetDirection(4);
	}
	footprintEmitter->Update();
}

/*Wander to random points within 100 pixels on either the x or y and then stand there for up to 7 seconds. 
If we collide with something, move out of collision and choose a new place to wander to*/
void Npc::Wander()
{
	if (wanderClock.getElapsedTime().asSeconds() > timeBetweenWander)
	{
		idle = false;

		//get the distance between current position and position we are to wander to
		float distance = sqrtf((((getPosition().x - wanderPos.x)*(getPosition().x - wanderPos.x)) + ((getPosition().y - wanderPos.y)*(getPosition().y - wanderPos.y))));
		//get the direction
		sf::Vector2f dir = sf::Vector2f((wanderPos.x - getPosition().x) / distance, (wanderPos.y - getPosition().y) / distance);
		
		if (distance > 0.5)//.5 because we are dealing with floats so will never get to the exact right position
		{

			//if we are colliding with something then restart the clock and wander back to the previous place we were
			if(colliding)
			{
				std::cout << "Resetting wander pos due to collision." << std::endl;
				wanderClock.restart();

				wanderPos = prevWanderPos;//go to the previous position

				sf::Vector2f unstickDir = sf::Vector2f(prevWanderPos.x - getPosition().x, prevWanderPos.y - getPosition().y);
				float magnitudeOfDir = sqrtf((unstickDir.x*unstickDir.x) + (unstickDir.y*unstickDir.y));
				unstickDir.x /= magnitudeOfDir;
				unstickDir.y /= magnitudeOfDir;

				setPosition(sf::Vector2f(getPosition().x + unstickDir.x*3, getPosition().y + unstickDir.y*3));
			}
			else if (!colliding)
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
				prevWanderPos = wanderPos;
				//set the next position to wander to
				wanderPos = sf::Vector2f(getPosition().x + xChange, getPosition().y + yChange);

				
			}

			else wanderPos = prevPos;//go to the previous position

			//set the time between each movement
			timeBetweenWander = rand() % 7 + 2;

			//restart the clock
			wanderClock.restart();

			wanderCount += 1;
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

		frameSize = sf::Vector2i(getTexture()->getSize().x / numberOfFrames, getTexture()->getSize().y);//numberOfFrames is the number of frames in the spritesheet
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
void Npc::Follow(sf::Vector2f positionToFollow, bool follow)
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
		if (!colliding)
		{
			if(follow)
				setPosition(sf::Vector2f(getPosition().x + direction.x, getPosition().y));
			else setPosition(sf::Vector2f(getPosition().x - direction.x, getPosition().y));
			direction.y = 0;
		}
	}
	//move up or down
	else if (getPosition().y > positionToFollow.y + 10 || getPosition().y < positionToFollow.y - 10)//let them get roughly close because we are dealing with floats so will never be exact
	{
		if (!colliding)
		{
			if(follow)
				setPosition(sf::Vector2f(getPosition().x, getPosition().y + direction.y));
			else setPosition(sf::Vector2f(getPosition().x, getPosition().y - direction.y));
			direction.x = 0;
		}
	}
	else
	{
		direction = sf::Vector2f(0, 0);
	}

	//sort out orientation here
	if (direction.x > 0)
	{
		idle = false;
		if (follow)
		{
			currentDirection = RIGHT;
			setTexture(rightWalkTexture);
		}
		else
		{
			currentDirection = LEFT;
			setTexture(leftWalkTexture);
		}
		if (prevDirection != currentDirection)
		{
			framePosition.x = 0;
			prevDirection = currentDirection;
		}
	}
	else if (direction.x < 0)
	{
		idle = false;
		if (follow)
		{
			currentDirection = LEFT;
			setTexture(leftWalkTexture);
		}
		else
		{
			currentDirection = RIGHT;
			setTexture(rightWalkTexture);
		}
		if (prevDirection != currentDirection)
		{
			framePosition.x = 0;
			prevDirection = currentDirection;
		}
	}
	if (direction.y > 0)
	{
		idle = false;
		if (follow)
		{
			currentDirection = DOWN;
			setTexture(downWalkTexture);
		}
		else
		{
			currentDirection = UP;
			setTexture(upWalkTexture);
		}
		if (prevDirection != currentDirection)
		{
			framePosition.x = 0;
			prevDirection = currentDirection;
		}
	}
	else if (direction.y < 0)
	{
		idle = false;
		if (follow)
		{
			currentDirection = UP;
			setTexture(upWalkTexture);
		}
		else
		{
			currentDirection = DOWN;
			setTexture(downWalkTexture);
		}
		if (prevDirection != currentDirection)
		{
			framePosition.x = 0;
			prevDirection = currentDirection;
		}
	}

	frameSize = sf::Vector2i(getTexture()->getSize().x / numberOfFrames, getTexture()->getSize().y);
	frame = sf::IntRect(framePosition, frameSize);
	setTextureRect(frame);

	if (direction.x > -0.5 && direction.x < 0.5)
		direction.x = 0;
	if (direction.y > -0.5 && direction.y < 0.5)
		direction.y = 0;

	//if we are no longer moving (i.e. we caught up to what we are following)
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

		if (currentBehaviour == "patrol")
		{
			patrolPointReached = true;
			patrolWanderClock.restart();
			//behaviourClock.restart();
		}
		else if (currentBehaviour == "forge")
		{
			
			if (workPoint == 0)//anvil
			{
				workPoint = 1;
				atAnvil = true;
				//framePosition.x = 0;
				//setTexture(workAnimTexture);
				//numberOfFrames = 2;
				//frameSize = sf::Vector2i(getTexture()->getSize().x / numberOfFrames, getTexture()->getSize().y);
				//frame = sf::IntRect(framePosition, frameSize);
				//setTextureRect(frame);
				//workClock.restart();
			}
			else if (workPoint == 1)//forge
			{
				workPoint = 0;
				atForge = true;
				//framePosition.x = 0;
				//setTexture(workAnimTexture);
				//numberOfFrames = 2;
				//frameSize = sf::Vector2i(getTexture()->getSize().x / numberOfFrames, getTexture()->getSize().y);
				//frame = sf::IntRect(framePosition, frameSize);
				//setTextureRect(frame);
				//workClock.restart();
			}
		}

		else if (currentBehaviour == "pickApples")
		{
			reachedAppleStart = true;
			
		}
	}
}

void Npc::SetBehaviour(int behaviourNum)
{
	if (behaviourNum == 1)
		currentBehaviour = behaviour1;
	else if (behaviourNum == 2)
		currentBehaviour = behaviour2;
	else if (behaviourNum == 3)
		currentBehaviour = behaviour3;
	else if (behaviourNum == 4)
		currentBehaviour = behaviour4;
}

void Npc::GoToBed(sf::Vector2f bedPos)
{
	Follow(bedPos, true);
}

//npcs with the forge behaviour will work at the blacksmiths forge and anvil
void Npc::Forge()
{
	if (atAnvil)
	{
		if (behaviourClock.getElapsedTime().asSeconds() < 30)
		{
			//forge(play animation)
			if (workClock.getElapsedTime().asSeconds() > anvilAnimTime)
			{
			//	if (framePosition.x < getTexture()->getSize().x - frameSize.x)
			//		framePosition.x += frameSize.x;

			//	else framePosition.x = 0;

				animationClock.restart();
			}
			currentDirection = LEFT;
		}
		else
		{
			//go to forge
			behaviourClock.restart();
			atAnvil = false;
		}
	}
	else if ((!atAnvil && !atForge))//not working at anvil or forge
	{
		if(workPoint == 0)
			Follow(sf::Vector2f(425, 920), true);//go to anvil
		else if(workPoint == 1)
			Follow(sf::Vector2f(425, 980), true);//go to forge
	}
	else if (atForge)
	{
		if (workClock.getElapsedTime().asSeconds() < 30)
		{
			//work(play animation)
			if (animationClock.getElapsedTime().asSeconds() > forgeAnimTime)
			{
				//if (framePosition.x < getTexture()->getSize().x - frameSize.x)
				//	framePosition.x += frameSize.x;

				//else framePosition.x = 0;

				animationClock.restart();
			}
			currentDirection = DOWN;
		}
		else
		{
			//go back to anvil
			behaviourClock.restart();
			atForge = false;
		}
	}
}

void Npc::Patrol()
{
	if (patrolPointsPicked == true)
	{
		if (patrolPointReached == false)
		{
			if (currentPatrolPoint == 1)
			{
				//seek to point
				Follow(patrolPoint1, true);
			}
			else if (currentPatrolPoint == 2)
			{
				//seek to point
				Follow(patrolPoint2, true);
			}
			else if (currentPatrolPoint == 3)
			{
				//seek to point
				Follow(patrolPoint3, true);
			}
			else if (currentPatrolPoint == 4)
			{
				//seek to point
				Follow(patrolPoint4, true);
			}
		}
		else
		{
			if (patrolWanderClock.getElapsedTime().asSeconds() < 10)//2 mins
			{
				//wander
				//std::cout << "Patrol is wandering." << std::endl;

				/*
				Come back to this. Bugs out the wander behaviour for some reason.
				Doesn't make it into the section of code that limits movement direction
				*/
				//Wander();
			}
			else
			{
				if (currentPatrolPoint < 4)
				{
					currentPatrolPoint += 1;
					patrolPointReached = false;
				}
				else
				{
					//pick new patrol points
					patrolPoint1 = sf::Vector2f(rand() % 1000 + 400, 400);
					patrolPoint2 = sf::Vector2f(rand() % 1000 + 400, 400);
					patrolPoint3 = sf::Vector2f(rand() % 1000 + 400, 800);
					patrolPoint4 = sf::Vector2f(rand() % 1000 + 400, 800);
					patrolPointsPicked = true;
					currentPatrolPoint = 1;
					patrolWanderClock.restart();
				}
			}
		}
	}
	else
	{
		//pick 4 patrol points
		patrolPoint1 = sf::Vector2f(rand() % 1000 + 400, 400);
		patrolPoint2 = sf::Vector2f(rand() % 1000 + 400, 400);
		patrolPoint3 = sf::Vector2f(rand() % 1000 + 400, 800);
		patrolPoint4 = sf::Vector2f(rand() % 1000 + 400, 800);
		patrolPointsPicked = true;
		currentPatrolPoint = 1;
		patrolWanderClock.restart();
	}


}

/*walk between apple trees*/
void Npc::PickApples()
{
	if (behaviourClock.getElapsedTime().asSeconds() > 5 && spotPicked == false)
	{
		int flip = rand() % 1;
		if (flip == 0)
		{
			prevDirection = currentDirection;
			currentDirection = LEFT;
		}
		else if (flip == 1)
		{
			prevDirection = currentDirection;
			currentDirection = RIGHT;
		}
		spotPicked = true;
		behaviourClock.restart();
		//play sound
		
	}
	else if (behaviourClock.getElapsedTime().asSeconds() > 10 && spotPicked == true)
	{
		//Follow(sf::Vector2f(appleStartPoint.x, appleStartPoint.y+50), true);
		if(currentApplePoint < 4)
			currentApplePoint += 1;
		else currentApplePoint = 0;
		spotPicked = false;
		reachedAppleStart = false;
		behaviourClock.restart();
	}
}

void Npc::Eat()
{
	if (eatClock.getElapsedTime().asSeconds() < 5)//eating/drinking
	{
		if (eatClock.getElapsedTime().asSeconds() > 1 && eatClock.getElapsedTime().asSeconds() < 1.5)
		{
			foodSprite.setRotation(15);
			foodSprite.setColor(sf::Color(foodSprite.getColor().r, foodSprite.getColor().g, foodSprite.getColor().b, 227));
		}
		else if (eatClock.getElapsedTime().asSeconds() > 1.5 && eatClock.getElapsedTime().asSeconds() < 2)
		{
			foodSprite.setRotation(-15);
			foodSprite.setColor(sf::Color(foodSprite.getColor().r, foodSprite.getColor().g, foodSprite.getColor().b, 199));
		}
		else if (eatClock.getElapsedTime().asSeconds() > 2 && eatClock.getElapsedTime().asSeconds() < 2.5)
		{
			foodSprite.setRotation(15);
			foodSprite.setColor(sf::Color(foodSprite.getColor().r, foodSprite.getColor().g, foodSprite.getColor().b, 171));
		}
		else if (eatClock.getElapsedTime().asSeconds() > 2.5 && eatClock.getElapsedTime().asSeconds() < 3)
		{
			foodSprite.setRotation(-15);
			foodSprite.setColor(sf::Color(foodSprite.getColor().r, foodSprite.getColor().g, foodSprite.getColor().b, 143));
		}
		else if (eatClock.getElapsedTime().asSeconds() > 3 && eatClock.getElapsedTime().asSeconds() < 3.5)
		{
			foodSprite.setRotation(15);
			foodSprite.setColor(sf::Color(foodSprite.getColor().r, foodSprite.getColor().g, foodSprite.getColor().b, 115));
		}
		else if (eatClock.getElapsedTime().asSeconds() > 3.5 && eatClock.getElapsedTime().asSeconds() < 4)
		{
			foodSprite.setRotation(-15);
			foodSprite.setColor(sf::Color(foodSprite.getColor().r, foodSprite.getColor().g, foodSprite.getColor().b, 87));
		}
		else if (eatClock.getElapsedTime().asSeconds() > 4 && eatClock.getElapsedTime().asSeconds() < 4.5)
		{
			foodSprite.setRotation(15);
			foodSprite.setColor(sf::Color(foodSprite.getColor().r, foodSprite.getColor().g, foodSprite.getColor().b, 59));
		}
		else if (eatClock.getElapsedTime().asSeconds() > 4.5 && eatClock.getElapsedTime().asSeconds() < 5)
		{
			foodSprite.setColor(sf::Color(foodSprite.getColor().r, foodSprite.getColor().g, foodSprite.getColor().b, 31));
			foodSprite.setRotation(0);
		}
	}
	else if (eatClock.getElapsedTime().asSeconds() > 5 && eatClock.getElapsedTime().asSeconds() < 15)
	{
		foodSprite.setPosition(sf::Vector2f(getPosition().x, getPosition().y +5));
	}
	else
	{
		eatClock.restart();
		foodSprite.setPosition(sf::Vector2f(getPosition().x, getPosition().y -3));
		foodSprite.setColor(sf::Color(foodSprite.getColor().r, foodSprite.getColor().g, foodSprite.getColor().b, 255));
	}
}

//actively avoid the player if they are close enough
void Npc::AvoidPlayer(sf::Vector2f playerPos)
{
	//get the euclidean distance between this npc and the player
	float distance = sqrtf(((getPosition().x - playerPos.x) * (getPosition().x - playerPos.x)) + ((getPosition().y - playerPos.y) * (getPosition().y - playerPos.y)));

	if (distance < 150)//if distance < 300 then evade
	{
		Follow(playerPos, false);
	}
	else
	{
		//do nothing
		//AudioManager::GetInstance()->pla
	}
}

//load greetings based on player race and gender
void Npc::LoadGreetings(int pRace, int pGender)
{
	greetingFilePath = "Assets/Greetings/to";

	if (pRace == 0)//human
		greetingFilePath += "Human";
	else if (pRace == 1)//elf
		greetingFilePath += "Elf";
	else if (pRace == 2)//dwarf
		greetingFilePath += "Dwarf";

	if (pGender == 0)//male
		greetingFilePath += "Male";
	else if (pGender == 1)//female
		greetingFilePath += "Female";

	greetingFilePath += ".txt";

	//load in the correct greetings file
	std::string line;
	std::ifstream myfile(greetingFilePath);
	if (myfile.is_open())
	{
		while (getline(myfile, line))
		{
			greetings.push_back(line);
		}
		myfile.close();
	}
	else std::cout << "Unable to open greetings file: " << "'" << greetingFilePath << "'" << std::endl;;
}

/*Draw the interaction hint sprite*/
void Npc::draw(sf::RenderTarget& window)
{
	if(interactable)
		window.draw(interactHintSprite);
	footprintEmitter->DrawParticles(window);
	if (currentBehaviour == "eating")
	{
		window.draw(foodSprite);
	}
}

//choose a greeting to display
void Npc::ChooseMessage()
{
	if (displayGreeting == false)//if not already showing a greeting
	{
		//int max = greetings.size() - 1;
		int index = rand() % 3;
		greetingText.setString(greetings.at(index));
		displayGreeting = true;
		greetingClock.restart();
	}
}

//draw a greeting if the npc is interacted with
void Npc::DrawMessage(sf::RenderTarget & window)
{
	if (displayGreeting == true)
	{
		if (greetingClock.getElapsedTime().asSeconds() < 2)
		{
			greetingText.setPosition(sf::Vector2f(getPosition().x + 20, getPosition().y - 50));
			speechBubbleSprite.setPosition(sf::Vector2f(getPosition().x + 10, getPosition().y - 40));
			window.draw(speechBubbleSprite);
			window.draw(greetingText);
		}
		else displayGreeting = false;
	}
}

void Npc::DrawBedCovers(sf::RenderTarget & window)
{
	if (inBed)
		window.draw(bedSprite);
}

/*Draw the npc on the minimap as an icon*/
void Npc::MinimapDraw(sf::RenderTarget& window)
{
	window.draw(npcMinimapIcon);
	interactHintSprite.setPosition(sf::Vector2f(getPosition().x, getPosition().y + 50));
}

void Npc::DrawBoundingBox(sf::RenderTarget& window)
{
	boundingBox.setPosition(sf::Vector2f(getGlobalBounds().left, getGlobalBounds().top));
	boundingBox.setSize(sf::Vector2f(getGlobalBounds().width, getGlobalBounds().height));
	boundingBox.setRotation(getRotation());
	window.draw(boundingBox);
}

void Npc::DrawFood(sf::RenderTarget & window)
{
	if (currentBehaviour == "eating")
	{
		window.draw(foodSprite);
	}
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

std::string Npc::getCurrentBehaviour()
{
	return currentBehaviour;
}

bool Npc::IsColliding()
{
	return colliding;
}

void Npc::setColliding(bool c)
{
	colliding = c;
}

float Npc::CheckDistanceToPlayer()
{
	return distanceToPlayer;
}

void Npc::setShowHint(bool s)
{
	showHint = s;
}

void Npc::SetBedId(int id)
{
	bedId = id;
}

int Npc::GetBedId()
{
	return bedId;
}

void Npc::SetBedtimeH(int h)
{
	bedtimeH = h;
}

int Npc::GetBedtimeH()
{
	return bedtimeH;
}

void Npc::SetBedtimeM(int m)
{
	bedtimeM = m;
}

int Npc::GetBedtimeM()
{
	return bedtimeM;
}

void Npc::SetBedtimeS(int s)
{
	bedtimeS = s;
}

int Npc::GetBedtimeS()
{
	return bedtimeS;
}

bool Npc::IsTimeForBed()
{
	return timeForBed;
}

void Npc::SetIsTimeForBed(bool b)
{
	timeForBed = b;
}

void Npc::SetBedPos(sf::Vector2f bpos)
{
	bedPos = bpos;
}

bool Npc::IsInBed()
{
	return inBed;
}

void Npc::SetInBed(bool b)
{
	inBed = b;
}

int Npc::GetWakeTH()
{
	return wakeTimeH;
}

void Npc::SetWakeTH(int h)
{
	wakeTimeH = h;
}

void Npc::SetWakeTM(int m)
{
	wakeTimeM = m;
}

int Npc::GetWakeTM()
{
	return wakeTimeM;
}

void Npc::SetWakeTS(int s)
{
	wakeTimeS = s;
}

int Npc::GetWakeTS()
{
	return wakeTimeS;
}

bool Npc::IsInteractable()
{
	return interactable;
}

bool Npc::HasStolenItem()
{
	return itemStolen;
}

void Npc::SetHasStolenItem(bool h)
{
	itemStolen = h;
}

void Npc::SetPreCollisionPos(sf::Vector2f p)
{
	preCollisionPos = p;
}

sf::Vector2f Npc::GetPreCollisionPos()
{
	return preCollisionPos;
}
