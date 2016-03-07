#include "stdafx.h"
#include "AreaManager.h"

AreaManager::AreaManager()
{
	Area* tutorialArea = new Area("Assets/tutorialArea.tmx", "Assets/lowPolyTutorialArea.tmx", "Assets/npcList.xml", "Assets/TutorialAreaCollidableObjects.xml", "Assets/TutorialAreaDoors.xml");
	areas.push_back(tutorialArea);
	Area* sewerArea = new Area("Assets/50x50SewerArea.tmx", "", "Assets/sewerAreaNpcList.xml", "Assets/SewerAreaCollidableObjects.xml", "Assets/TutorialAreaDoors.xml");
	areas.push_back(sewerArea);
	Area* generalStore1Area = new Area("Assets/generalStore1.tmx", "", "Assets/generalStore1NpcList.xml", "Assets/generalStore1CollidableObjects.xml", "Assets/TutorialAreaDoors.xml");
	areas.push_back(generalStore1Area);

	currentArea = TUTORIAL;

	areaToChangeTo = TUTORIAL;
	readyToChangeArea = false;
}

AreaManager::~AreaManager()
{

}

void AreaManager::Update(sf::Vector2f playerPos)
{
	areas.at(currentArea)->Update(playerPos);
}

void AreaManager::ChangeArea(int areaToChangeTo)
{
	if(currentArea!=areaToChangeTo)
		currentArea = areaToChangeTo;
}

std::pair<bool, int> AreaManager::CheckCollisionPlayerNpcs(Player * p)
{
	return areas.at(currentArea)->CheckNpcPlayerCollisions(p);
}

bool AreaManager::CheckPlayerCollidableObjectsCollisions(sf::FloatRect playerBounds)
{
	return areas.at(currentArea)->CheckPlayerCollidableObjectsCollision(playerBounds);
}

void AreaManager::Draw(sf::RenderTarget & window, bool debugMode)
{
	areas.at(currentArea)->Draw(window, debugMode);
}

void AreaManager::MinimapDraw(sf::RenderTarget & window)
{
	areas.at(currentArea)->MinimapDraw(window);
}

int AreaManager::GetCurrentArea()
{
	return currentArea;
}

void AreaManager::CheckDoors(sf::Vector2f playerPos, sf::FloatRect playerBounds)
{
	int a = areas.at(currentArea)->CheckDoorPlayerCollision(playerPos, playerBounds);
	if (a != -100)
	{
		areaToChangeTo = a;
		readyToChangeArea = true;
	}
}

int AreaManager::GetAreaToChangeTo()
{
	return areaToChangeTo;
}

void AreaManager::SetAreaToChangeTo(int atc)
{
	areaToChangeTo = atc;
}

bool AreaManager::IsReadyToChangeArea()
{
	return readyToChangeArea;
}

void AreaManager::SetReadyToChangeArea(int r)
{
	readyToChangeArea = r;
}
