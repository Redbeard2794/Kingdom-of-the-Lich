#ifndef AREA_H
#define AREA_H

//rapidxml stuff
#include "rapidxml_utils.hpp"
using namespace rapidxml;
#include <sstream> // std::stringstream

class Area
{
private:

	std::string areaFilePath;

	std::string areaMinimapFilePath;

	std::string areaNpcListFilePath;

	std::string collidableObjectsFilePath;

	std::vector<Npc*> npcs;

	std::vector<CollidableObject*> collidableObjects;

public:

	/*Constructor. params: area file path, minimap file path, npc list file path and collidable objects file path*/
	Area(std::string afp, std::string amfp, std::string anlfp, std::string cofp);

	/*Destructor*/
	~Area();

	/*Load the area's npcs from the xml file*/
	void LoadNpcs();

	void LoadCollidableObjects();

	/*Update the map, minimap and npcs*/
	void Update(sf::Vector2f playerPos);

	std::pair<bool, int> CheckNpcPlayerCollisions(Player* p);

	void HandleNpcCollidableObjectsCollisions();

	bool CheckPlayerCollidableObjectsCollision(sf::FloatRect playerBounds);

	/*Draw the npcs*/
	void Draw(sf::RenderTarget& window, bool debugMode);

	void MinimapDraw(sf::RenderTarget& window);

};

#endif
