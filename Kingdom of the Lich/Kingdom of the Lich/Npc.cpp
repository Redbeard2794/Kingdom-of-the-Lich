#include "stdafx.h"
#include "Npc.h"

//name, id, race, gender, texturePath, mapIconTexturePath, x, y, hasQuest, behaviour, show keyboard or controller hint
Npc::Npc(std::string n, int i, std::string texturePath, std::string mapIconTexturePath, sf::Vector2f pos, bool quest, std::string beh, bool controller)
	: name(n), id(i), hasQuest(quest), behaviour(beh)
{
	m_texture.loadFromFile(texturePath);
	setTexture(m_texture);
	setOrigin(m_texture.getSize().x / 2, m_texture.getSize().y / 2);
	setPosition(pos);

	if (npcMinimapIconTexture.loadFromFile(mapIconTexturePath)) {}
	else npcMinimapIconTexture.loadFromFile("Assets/Debug.png");	//if it fails load placeholder
	npcMinimapIcon.setTexture(npcMinimapIconTexture);
	npcMinimapIcon.setOrigin(npcMinimapIconTexture.getSize().x / 2, npcMinimapIconTexture.getSize().y / 2);
	npcMinimapIcon.setPosition(pos);

	LoadInteractHintTexture(controller);

	if (behaviour == "wander")
	{
		wanderPos = sf::Vector2f(getPosition().x + (rand() % 100 + 10), getPosition().y);
		std::cout << name << " is wandering to " << wanderPos.x << ", " << wanderPos.y << std::endl;
		timeBetweenWander = rand() % 7 + 2;
	}
	else if (behaviour == "walkPattern")
	{
		patternPoints.push_back(getPosition());// = getPosition();
		patternPoints.push_back(sf::Vector2f(patternPoints.at(0).x, patternPoints.at(0).y + 400));
		patternPoints.push_back(sf::Vector2f(patternPoints.at(1).x-400, patternPoints.at(1).y));
		patternPoints.push_back(sf::Vector2f(patternPoints.at(2).x, patternPoints.at(2).y - 400));
		currentPointIndex = 0;
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
	
	if(distance < 25)
		interactHintSprite.setColor(sf::Color::White);
	else interactHintSprite.setColor(sf::Color::Transparent);

	npcMinimapIcon.setPosition(getPosition());

	if (behaviour == "wander")
	{
		Wander();
	}
	else if (behaviour == "walkPattern")
	{
		walkPattern();
	}

}

void Npc::Wander()
{
	if (behaviourClock.getElapsedTime().asSeconds() > timeBetweenWander)
	{
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
			std::cout << "Coin flip: " << coin << std::endl;

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
			std::cout << "Time between wander: " << timeBetweenWander << std::endl;
			std::cout << name << " is wandering to " << wanderPos.x << ", " << wanderPos.y << std::endl;

			//restart the clock
			behaviourClock.restart();
		}

	}
	else prevPos = getPosition();
}

void Npc::walkPattern()
{
	//go from point to point
	if (currentPointIndex < 3)
	{
		//get the distance between current position and position we are to wander to
		float distance = sqrtf((((getPosition().x - patternPoints.at(currentPointIndex+1).x)*(getPosition().x - patternPoints.at(currentPointIndex + 1).x))
			+ ((getPosition().y - patternPoints.at(currentPointIndex + 1).y)*(getPosition().y - patternPoints.at(currentPointIndex + 1).y))));
		//get the direction
		sf::Vector2f dir = sf::Vector2f((patternPoints.at(currentPointIndex + 1).x - patternPoints.at(currentPointIndex).x) / distance, (patternPoints.at(currentPointIndex + 1).y - patternPoints.at(currentPointIndex).y) / distance);



		if ((int)distance > 10)//.5 because we are dealing with floats so will never get to the exact right position
		{
			setPosition(sf::Vector2f(getPosition().x + dir.x, getPosition().y + dir.y));
			std::cout << "Position: " << getPosition().x << ", " << getPosition().y << std::endl;
			//std::cout << "Distance: " << distance << std::endl;
		}
		else
		{
			currentPointIndex += 1;
			setPosition(patternPoints.at(currentPointIndex));
		}
	}

	else
	{
		//get the distance between current position and position we are to wander to
		float distance = sqrtf((((getPosition().x - patternPoints.at(0).x)*(getPosition().x - patternPoints.at(0).x))
			+ ((getPosition().y - patternPoints.at(0).y)*(getPosition().y - patternPoints.at(0).y))));
		//get the direction
		sf::Vector2f dir = sf::Vector2f((patternPoints.at(0).x - patternPoints.at(currentPointIndex).x) / distance, (patternPoints.at(0).y - patternPoints.at(currentPointIndex).y) / distance);



		if ((int)distance > 5)//.5 because we are dealing with floats so will never get to the exact right position
		{
			setPosition(sf::Vector2f(getPosition().x + dir.x, getPosition().y + dir.y));
			std::cout << "Position: " << getPosition().x << ", " << getPosition().y << std::endl;
			//std::cout << "Distance: " << distance << std::endl;
		}
		else 
		{
			currentPointIndex = 0;
			setPosition(patternPoints.at(currentPointIndex));
		}
	}

	std::cout << "Current point: " << currentPointIndex << std::endl;
}

void Npc::draw(sf::RenderTarget& window)
{
	window.draw(interactHintSprite);
}

void Npc::MinimapDraw(sf::RenderTarget& window)
{
	window.draw(npcMinimapIcon);
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
