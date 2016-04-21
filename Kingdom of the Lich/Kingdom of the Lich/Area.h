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

	/*Constructor. params: area file path, minimap file path, npc list file path, collidable objects file path, door file path, bed file path, camp fire file path*/
	Area(std::string afp, std::string amfp, std::string anlfp, std::string cofp, std::string doorPath, std::string bedsp, std::string firePath);

	/*Destructor*/
	~Area();

	/*Load the area's npcs from the xml file*/
	void LoadNpcs();

	/*Load the collidable objects from an xml file*/
	void LoadCollidableObjects();

	/*Load the door objects from an xml file*/
	void LoadDoors();

	/*Load the camp files from an xml file*/
	void LoadFires();

	/*Update the map, minimap and npcs*/
	void Update(sf::Vector2f playerPos, int currentHours, int currentMinutes, int currentSeconds);

	/*check if the player and an npc collides. Params are: player pointer, inventory pointer, stolen goods chest poiner, whether a is pressed or not. return true/false and a number based on what the npc does*/
	std::pair<bool, int> CheckNpcPlayerCollisions(Player* p, Inventory* playerInv, Chest* stolenGoodsChest, bool aPressed);

	/*deal with npc and collidable objects collisions*/
	void HandleNpcCollidableObjectsCollisions();

	/*Check if the player collides with a collidable object. param is the players bounding box*/
	bool CheckPlayerCollidableObjectsCollision(sf::FloatRect playerBounds);

	/*load beds from xml file*/
	void LoadBeds();

	/*Load greetings for the npcs. params: players race, players gender*/
	void LoadNpcGreetings(int pRace, int pGender);

	/*Draw the npcs*/
	void Draw(sf::RenderTarget& window, bool debugMode);

	void MinimapDraw(sf::RenderTarget& window);

	/*Check if the player collides with a door. Params: player position, player bounding box. returns area door leads to*/
	int CheckDoorPlayerCollision(sf::Vector2f playerPos, sf::FloatRect playerBounds);

	void ResetStealingNpc();

	/*unlock a door based on its id. param: id of door to unlock*/
	void UnlockDoorById(int doorId);
};

#endif
