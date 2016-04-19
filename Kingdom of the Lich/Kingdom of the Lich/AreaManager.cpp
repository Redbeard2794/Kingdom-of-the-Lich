#include "stdafx.h"
#include "AreaManager.h"

AreaManager::AreaManager(sf::Font f, int sw, int sh) : font(f), screenW(sw), screenH(sh)
{
	Area* tutorialArea = new Area("Assets/tutorialArea.tmx", "Assets/lowPolyTutorialArea.tmx", "Assets/AreaXmlFiles/npcList.xml", "Assets/AreaXmlFiles/TutorialAreaCollidableObjects.xml", "Assets/AreaXmlFiles/TutorialAreaDoors.xml", "Assets/AreaXmlFiles/tutorialAreaBeds.xml");
	areas.push_back(tutorialArea);
	Area* sewerArea = new Area("Assets/50x50SewerArea.tmx", "", "Assets/AreaXmlFiles/sewerAreaNpcList.xml", "Assets/AreaXmlFiles/SewerAreaCollidableObjects.xml", "Assets/AreaXmlFiles/sewerAreaDoorList.xml", "");
	areas.push_back(sewerArea);
	Area* generalStore1Area = new Area("Assets/generalStore1.tmx", "", "Assets/AreaXmlFiles/generalStore1NpcList.xml", "Assets/AreaXmlFiles/generalStore1CollidableObjects.xml", "Assets/AreaXmlFiles/generalStore1DoorList.xml", "");
	areas.push_back(generalStore1Area);

	Area* house1 = new Area("Assets/house1.tmx", "", "Assets/AreaXmlFiles/house1NpcList.xml", "Assets/AreaXmlFiles/house1CollidableObjects.xml", "Assets/AreaXmlFiles/house1DoorList.xml", "");
	areas.push_back(house1);

	Area* house2 = new Area("Assets/house2.tmx", "", "Assets/AreaXmlFiles/house2NpcList.xml", "Assets/AreaXmlFiles/house2CollidableObjects.xml", "Assets/AreaXmlFiles/house2DoorList.xml", "");
	areas.push_back(house2);

	Area* pub1 = new Area("Assets/pub1.tmx", "", "Assets/AreaXmlFiles/TheDrunkenDragonInnNpcList.xml", "Assets/AreaXmlFiles/TheDrunkenDragonInnCollidableObjects.xml", "Assets/AreaXmlFiles/TheDrunkenDragonInnDoorList.xml", "");
	areas.push_back(pub1);

	currentArea = TUTORIAL;

	areaToChangeTo = NONE;
	readyToChangeArea = false;

	currentAreaText.setFont(font);
	currentAreaText.setColor(sf::Color::Cyan);
	currentAreaText.setCharacterSize(20);
	currentAreaText.setPosition(screenW-400, 15);
}

AreaManager::~AreaManager()
{

}

void AreaManager::Update(sf::Vector2f playerPos, int currentHours, int currentMinutes, int currentSeconds)
{
	areas.at(currentArea)->Update(playerPos, currentHours, currentMinutes, currentSeconds);
	if (currentArea == TUTORIAL)
		currentAreaText.setString("Current Area: Trainton Castle");
	else if(currentArea == SEWER)
		currentAreaText.setString("Current Area: Trainton Sewers");
	else if(currentArea == LellesQualityMerchandise)
		currentAreaText.setString("Current Area: Lelles Quality Merchandise");
	else if (currentArea == House1)
		currentAreaText.setString("Current Area: House 1");
	else if (currentArea == House2)
		currentAreaText.setString("Current Area: House 2");
	else if (currentArea == TheDrunkenDragonInn)
		currentAreaText.setString("Current Area: The Drunken Dragon Inn");
}

void AreaManager::ChangeArea(int areaToChangeTo)
{
	if(currentArea!=areaToChangeTo)
		currentArea = areaToChangeTo;
}

std::pair<bool, int> AreaManager::CheckCollisionPlayerNpcs(Player * p, Inventory* playerInv, Chest* stolenGoodsChest, bool aPressed)
{
	return areas.at(currentArea)->CheckNpcPlayerCollisions(p, playerInv, stolenGoodsChest, aPressed);
}

bool AreaManager::CheckPlayerCollidableObjectsCollisions(sf::FloatRect playerBounds)
{
	return areas.at(currentArea)->CheckPlayerCollidableObjectsCollision(playerBounds);
}

void AreaManager::Draw(sf::RenderTarget & window, bool debugMode)
{
	areas.at(currentArea)->Draw(window, debugMode);
}

void AreaManager::DrawCurrentAreaText(sf::RenderTarget & window)
{
	window.draw(currentAreaText);
}

void AreaManager::MinimapDraw(sf::RenderTarget & window)
{
	areas.at(currentArea)->MinimapDraw(window);
}

void AreaManager::ResetAreaStealingNpcs()
{
	areas.at(currentArea)->ResetStealingNpc();
}

void AreaManager::UnlockDoorInCurrentArea(int id)
{
	areas.at(currentArea)->UnlockDoorById(id);
}

int AreaManager::GetCurrentArea()
{
	return currentArea;
}

void AreaManager::SetCurrentArea(int a)
{
	currentArea = a;
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

void AreaManager::LoadGreetings(int pRace, int pGender)
{
	for (int i = 0; i < areas.size(); i++)
	{
		areas.at(i)->LoadNpcGreetings(pRace, pGender);
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
