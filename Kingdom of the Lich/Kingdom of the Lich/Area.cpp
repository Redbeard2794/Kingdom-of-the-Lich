#include "stdafx.h"
#include "Area.h"

/*Constructor. params: area file path, minimap file path, npc list file path and collidable objects file path*/
Area::Area(std::string afp, std::string amfp, std::string anlfp, std::string cofp, std::string doorPath)
{
	areaFilePath = afp;
	areaMinimapFilePath = amfp;
	areaNpcListFilePath = anlfp;
	areaDoorListFilePath = doorPath;
	collidableObjectsFilePath = cofp;

	LoadNpcs();
	LoadCollidableObjects();

	LoadDoors();
}

/*Destructor*/
Area::~Area()
{

}

/*Load the area's npcs from the xml file*/
void Area::LoadNpcs()
{
	xml_document<> doc;
	std::ifstream file(areaNpcListFilePath);
	std::stringstream buffer;
	buffer << file.rdbuf();
	file.close();
	std::string content(buffer.str());
	doc.parse<0>(&content[0]);

	xml_node<> *pRoot = doc.first_node();
	//std::cout << "Name of root node is: " << doc.first_node()->name() << "\n" << std::endl;

	xml_node<>* npcList = doc.first_node("npcList");
	xml_node<>* npc = npcList->first_node("npc");

	//load in each npc's information and then create them
	while (npc != NULL)
	{
		//name, id, race, gender, texturePath, mapIconTexturePath, x, y, hasQuest, behaviour
		std::string name = "";
		int id = 0;
		std::string race = "";
		std::string gender = "";
		std::string texturePath = "";

		std::string idleUpPath = "";
		std::string idleDownPath = "";
		std::string idleLeftPath = "";
		std::string idleRightPath = "";

		int numberOfFrames = 0;

		std::string walkUpPath = "";
		std::string walkDownPath = "";
		std::string walkLeftPath = "";
		std::string walkRightPath = "";

		std::string mapIconTexturePath = "";
		float x = 0;
		float y = 0;
		std::string hasQuest = "";
		std::string interactable = "";
		std::string behaviour = "";

		/*Get the npc's name*/
		//std::cout << "Name: " << npc->first_attribute("name")->value() << std::endl;
		name = npc->first_attribute("name")->value();

		/*Get the npc's id*/
		//std::cout << "I.D: " << npc->first_node("id")->value() << std::endl;
		id = atoi(npc->first_node("id")->value());

		/*Get the npc's race*/
		//std::cout << "Race: " << npc->first_node("race")->value() << std::endl;
		race = npc->first_node("race")->value();

		/*Get the npc's gender*/
		//std::cout << "Gender: " << npc->first_node("gender")->value() << std::endl;
		gender = npc->first_node("gender")->value();

		/*get paths for idle sprites*/
		//std::cout << "Idle up path: " << npc->first_node("idleUpPath")->value() << std::endl;
		idleUpPath = npc->first_node("idleUpPath")->value();

		//std::cout << "Idle down path: " << npc->first_node("idleDownPath")->value() << std::endl;
		idleDownPath = npc->first_node("idleDownPath")->value();

		//std::cout << "Idle left path: " << npc->first_node("idleLeftPath")->value() << std::endl;
		idleLeftPath = npc->first_node("idleLeftPath")->value();

		//std::cout << "Idle right path: " << npc->first_node("idleRightPath")->value() << std::endl;
		idleRightPath = npc->first_node("idleRightPath")->value();

		/*Get the number of frames*/
		//std::cout << "Number of frames: " << npc->first_node("numberOfFrames")->value() << std::endl;
		numberOfFrames = atoi(npc->first_node("numberOfFrames")->value());

		/*get paths for walking sprites*/
		//std::cout << "Walk up path: " << npc->first_node("walkUpPath")->value() << std::endl;
		walkUpPath = npc->first_node("walkUpPath")->value();

		//std::cout << "Walk down path: " << npc->first_node("walkDownPath")->value() << std::endl;
		walkDownPath = npc->first_node("walkDownPath")->value();

		//std::cout << "Walk left path: " << npc->first_node("walkLeftPath")->value() << std::endl;
		walkLeftPath = npc->first_node("walkLeftPath")->value();

		//std::cout << "Walk right path: " << npc->first_node("walkRightPath")->value() << std::endl;
		walkRightPath = npc->first_node("walkRightPath")->value();

		/*minimap icon path*/
		//std::cout << "Map icon texture path: " << npc->first_node("mapIconTexturePath")->value() << std::endl;
		mapIconTexturePath = npc->first_node("mapIconTexturePath")->value();

		/*x position*/
		//std::cout << "X: " << npc->first_node("x")->value() << std::endl;
		x = atof(npc->first_node("x")->value());

		/*y position*/
		//std::cout << "Y: " << npc->first_node("y")->value() << std::endl;
		y = atof(npc->first_node("y")->value());

		/*Does the npc have a quest for the player*/
		//std::cout << "Has quest: " << npc->first_node("hasQuest")->value() << std::endl;
		hasQuest = npc->first_node("hasQuest")->value();

		/*Can the npc be interacted with?*/
		//std::cout << "Interactable: " << npc->first_node("interact")->value() << std::endl;
		interactable = npc->first_node("interact")->value();

		/*What behaviour do they have? e.g: wander, stand etc*/
		//std::cout << "Behaviour: " << npc->first_node("behaviour")->value() << std::endl;
		behaviour = npc->first_node("behaviour")->value();

		/*Create the npc*/
		Npc* n = new Npc(name, id, idleUpPath, idleDownPath, idleLeftPath, idleRightPath, numberOfFrames, walkUpPath, walkDownPath, walkLeftPath, walkRightPath, mapIconTexturePath, sf::Vector2f(x, y), hasQuest, interactable, behaviour, true);
		npcs.push_back(n);
		//std::cout << "Size of npcVector: " << npcs.size() << std::endl;

		//std::cout << "------------------------------------------------------------" << std::endl;
		/*Move onto the next npc tag*/
		npc = npc->next_sibling("npc");
	}
}

void Area::LoadCollidableObjects()
{
	xml_document<> doc;
	std::ifstream file(collidableObjectsFilePath);
	std::stringstream buffer;
	buffer << file.rdbuf();
	file.close();
	std::string content(buffer.str());
	doc.parse<0>(&content[0]);

	xml_node<> *pRoot = doc.first_node();
	//std::cout << "Name of root node is: " << doc.first_node()->name() << "\n" << std::endl;

	xml_node<>* collidableList = doc.first_node("collidableObjectsList");
	xml_node<>* collidableObject = collidableList->first_node("collidableObject");

	//load in each collidable object's information and then create them
	while (collidableObject != NULL)
	{
		int id = 0;
		int x = 0;
		int y = 0;
		int w = 0;
		int h = 0;

		/*Get the collidable objects id*/
		//std::cout << "ID: " << collidableObject->first_node("id")->value() << std::endl;
		id = std::atoi(collidableObject->first_node("id")->value());

		/*Get the collidable objects x co-ordinate*/
		//std::cout << "X: " << collidableObject->first_node("x")->value() << std::endl;
		x = std::atoi(collidableObject->first_node("x")->value());

		/*Get the collidable objects y co-ordinate*/
		//std::cout << "ID: " << collidableObject->first_node("y")->value() << std::endl;
		y = std::atoi(collidableObject->first_node("y")->value());

		/*Get the collidable objects width*/
		//std::cout << "ID: " << collidableObject->first_node("w")->value() << std::endl;
		w = std::atoi(collidableObject->first_node("w")->value());

		/*Get the collidable objects height*/
		//std::cout << "ID: " << collidableObject->first_node("h")->value() << std::endl;
		h = std::atoi(collidableObject->first_node("h")->value());



		/*Create the collidableObject*/
		CollidableObject* c = new CollidableObject(x, y, w, h, true, false);
		collidableObjects.push_back(c);

		//std::cout << "Size of collidable objects vector: " << collidableObjects.size() << std::endl;

		//std::cout << "------------------------------------------------------------" << std::endl;
		/*Move onto the next collidable object tag*/
		collidableObject = collidableObject->next_sibling("collidableObject");
	}
}

void Area::LoadDoors()
{
	xml_document<> doc;
	std::ifstream file(areaDoorListFilePath);
	std::stringstream buffer;
	buffer << file.rdbuf();
	file.close();
	std::string content(buffer.str());
	doc.parse<0>(&content[0]);

	xml_node<> *pRoot = doc.first_node();
	//std::cout << "Name of root node is: " << doc.first_node()->name() << "\n" << std::endl;

	xml_node<>* doorList = doc.first_node("DoorList");
	xml_node<>* doorObject = doorList->first_node("door");

	//load in each collidable object's information and then create them
	while (doorObject != NULL)
	{
		//int id = 0;
		//int x = 0;
		//int y = 0;
		//bool open = false;
		//int type = 0;
		//int area = 0;

		int id = std::atoi(doorObject->first_node("id")->value());

		int x = std::atoi(doorObject->first_node("x")->value());

		int y = std::atoi(doorObject->first_node("y")->value());

		bool open = std::atoi(doorObject->first_node("open")->value());

		int type = std::atoi(doorObject->first_node("type")->value());

		int area = std::atoi(doorObject->first_node("area")->value());

		/*Create the door*/
		Door * d = new Door(type, sf::Vector2f(x, y), open, area, id);
		doors.push_back(d);

		/*Move onto the next door object tag*/
		doorObject = doorObject->next_sibling("door");
	}
}

/*Update the map, minimap and npcs*/
void Area::Update(sf::Vector2f playerPos)
{
	for (int i = 0; i < npcs.size(); i++)
	{
		npcs.at(i)->Update(playerPos);

		if (npcs.at(i)->CheckDistanceToPlayer() < 50)
			npcs.at(i)->setShowHint(true);
		else npcs.at(i)->setShowHint(false);

	}

	HandleNpcCollidableObjectsCollisions();
}

std::pair<bool, int> Area::CheckNpcPlayerCollisions(Player* p)
{
	for (int i = 0; i < npcs.size(); i++)
	{
		if (p->getGlobalBounds().intersects(npcs.at(i)->getGlobalBounds()))
		{
			npcs.at(i)->setColliding(true);

			//should the player be able to push the npc out of the way?
			//if (p->getCurrentDirection() == 0)//up
			//{
			//	npcs.at(i)->setPosition(npcs.at(i)->getPosition().x, npcs.at(i)->getPosition().y - 2);//2
			//}
			//else if (p->getCurrentDirection() == 1)//down
			//{
			//	npcs.at(i)->setPosition(npcs.at(i)->getPosition().x, npcs.at(i)->getPosition().y + 2);//2
			//}
			//else if (p->getCurrentDirection() == 2)//right
			//{
			//	npcs.at(i)->setPosition(npcs.at(i)->getPosition().x + 2, npcs.at(i)->getPosition().y);//2
			//}
			//else if (p->getCurrentDirection() == 3)//left
			//{
			//	npcs.at(i)->setPosition(npcs.at(i)->getPosition().x - 2, npcs.at(i)->getPosition().y);//2
			//}

			npcs.at(i)->setColliding(false);
			if (npcs.at(i)->getBehaviour() == "follow")
				return std::make_pair(true, 2);
			if (npcs.at(i)->doesNpcHaveQuest())
			{
				return std::make_pair(true, 0);
			}
			else return std::make_pair(true, 1);

			
		}
	}
	return std::make_pair(false,5);
}

void Area::HandleNpcCollidableObjectsCollisions()
{
	for (int i = 0; i < npcs.size(); i++)
	{
		for (int j = 0; j < collidableObjects.size(); j++)
		{
			if (collidableObjects.at(j)->CheckIntersectionRectangle(npcs.at(i)->getGlobalBounds()))
			{
				npcs.at(i)->setColliding(true);
				//std::cout << npcVector.at(i)->getNpcName() << "Collided with object " << j << std::endl;
				break;
			}
			else npcs.at(i)->setColliding(false);
		}
	}

}

bool Area::CheckPlayerCollidableObjectsCollision(sf::FloatRect playerBounds)
{
	for (int i = 0; i < collidableObjects.size(); i++)
	{
		if (collidableObjects.at(i)->CheckIntersectionRectangle(playerBounds))
		{
			return true;
		}
	}
	return false;
}

/*Draw the npcs and collidable objects*/
void Area::Draw(sf::RenderTarget & window, bool debugMode)
{
	for (int i = 0; i < npcs.size(); i++)
	{
		window.draw(*npcs.at(i));
		if (debugMode)
			npcs.at(i)->DrawBoundingBox(window);
	}

	for (int i = 0; i < collidableObjects.size(); i++)
	{
		if (debugMode)
			window.draw(*collidableObjects.at(i));
	}

	for (int i = 0; i < doors.size(); i++)
	{
		window.draw(*doors.at(i));
	}
}

void Area::MinimapDraw(sf::RenderTarget & window)
{
	for (int i = 0; i < npcs.size(); i++)
	{
		npcs.at(i)->MinimapDraw(window);
	}
}

int Area::CheckDoorPlayerCollision(sf::Vector2f playerPos, sf::FloatRect playerBounds)
{
	//if within a certain distance of door check collision,
	//if colliding return the area the area manager should set its current area to
	for (int i = 0; i < doors.size(); i++)
	{
		float distanceToPlayer = sqrtf((((playerPos.x - doors.at(i)->getPosition().x)*(playerPos.x - doors.at(i)->getPosition().x)) + ((playerPos.y - doors.at(i)->getPosition().y)*(playerPos.y - doors.at(i)->getPosition().y))));

		if (distanceToPlayer < 300)//so don't bother checking for a collision unless we are reasonably close to the door in the first place
		{
			if (doors.at(i)->IsPlayerInDoorway(playerPos))
			{
				return doors.at(i)->GetArea();
				break;
			}
		}
	}

	return -100;
}
