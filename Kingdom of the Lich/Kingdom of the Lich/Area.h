#ifndef AREA_H
#define AREA_H

//rapidxml stuff
#include "rapidxml_utils.hpp"
using namespace rapidxml;
#include <sstream> // std::stringstream

#include "Door.h"
#include "Bed.h"
#include "Inventory.h"
#include "CampFire.h"

class Area
{
private:

	std::string areaFilePath;

	std::string areaMinimapFilePath;

	std::string areaNpcListFilePath;

	std::string areaDoorListFilePath;

	std::string collidableObjectsFilePath;

	std::vector<Npc*> npcs;

	std::vector<CollidableObject*> collidableObjects;

	std::vector<Door*> doors;

	std::string bedPath;
	std::vector<Bed*> beds;

	std::string campFirePath;
	std::vector<CampFire*> campFires;

public:

	/*Constructor. params: area file path, minimap file path, npc list file path and collidable objects file path*/
	Area(std::string afp, std::string amfp, std::string anlfp, std::string cofp, std::string doorPath, std::string bedsp, std::string firePath);

	/*Destructor*/
	~Area();

	/*Load the area's npcs from the xml file*/
	void LoadNpcs();

	void LoadCollidableObjects();

	void LoadDoors();

	void LoadFires();

	/*Update the map, minimap and npcs*/
	void Update(sf::Vector2f playerPos, int currentHours, int currentMinutes, int currentSeconds);

	std::pair<bool, int> CheckNpcPlayerCollisions(Player* p, Inventory* playerInv, Chest* stolenGoodsChest, bool aPressed);

	void HandleNpcCollidableObjectsCollisions();

	bool CheckPlayerCollidableObjectsCollision(sf::FloatRect playerBounds);

	void LoadBeds();

	void LoadNpcGreetings(int pRace, int pGender);

	/*Draw the npcs*/
	void Draw(sf::RenderTarget& window, bool debugMode);

	void MinimapDraw(sf::RenderTarget& window);

	/*door stuff*/
	int CheckDoorPlayerCollision(sf::Vector2f playerPos, sf::FloatRect playerBounds);

	void ResetStealingNpc();

	/*unlock a door based on its id. param: id of door to unlock*/
	void UnlockDoorById(int doorId);
};

#endif
