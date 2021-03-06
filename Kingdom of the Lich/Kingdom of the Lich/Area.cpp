#include "stdafx.h"
#include "Area.h"

/*Constructor. params: area file path, minimap file path, npc list file path, collidable objects file path, door file path, bed file path, camp fire file path*/
Area::Area(std::string afp, std::string amfp, std::string anlfp, std::string cofp, std::string doorPath, std::string bedsp, std::string firePath)
{
	areaFilePath = afp;
	areaMinimapFilePath = amfp;
	areaNpcListFilePath = anlfp;
	areaDoorListFilePath = doorPath;
	collidableObjectsFilePath = cofp;
	bedPath = bedsp;
	campFirePath = firePath;

	LoadNpcs();
	LoadCollidableObjects();

	LoadDoors();
	LoadBeds();
	LoadFires();
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
		behaviour = npc->first_node("behaviour1")->value();

		std::string behaviour2 = npc->first_node("behaviour2")->value();
		std::string behaviour3 = npc->first_node("behaviour3")->value();
		std::string behaviour4 = npc->first_node("behaviour4")->value();

		int bedId = std::atoi(npc->first_node("bedId")->value());

		int bedtimeH = std::atoi(npc->first_node("bedtimeH")->value());

		int bedtimeM = std::atoi(npc->first_node("bedtimeM")->value());

		int bedtimeS = std::atoi(npc->first_node("bedtimeS")->value());

		int wakeTimeH = std::atoi(npc->first_node("wakeTimeH")->value());

		int wakeTimeM = std::atoi(npc->first_node("wakeTimeM")->value());

		int wakeTimeS = std::atoi(npc->first_node("wakeTimeS")->value());

		int behaviour1H = std::atoi(npc->first_node("behaviour1TimeH")->value());
		int behaviour1M = std::atoi(npc->first_node("behaviour1TimeM")->value());
		int behaviour1S = std::atoi(npc->first_node("behaviour1TimeS")->value());
		int behaviour2H = std::atoi(npc->first_node("behaviour2TimeH")->value());
		int behaviour2M = std::atoi(npc->first_node("behaviour2TimeM")->value());
		int behaviour2S = std::atoi(npc->first_node("behaviour2TimeS")->value());
		int behaviour3H = std::atoi(npc->first_node("behaviour3TimeH")->value());
		int behaviour3M = std::atoi(npc->first_node("behaviour3TimeM")->value());
		int behaviour3S = std::atoi(npc->first_node("behaviour3TimeS")->value());
		int behaviour4H = std::atoi(npc->first_node("behaviour4TimeH")->value());
		int behaviour4M = std::atoi(npc->first_node("behaviour4TimeM")->value());
		int behaviour4S = std::atoi(npc->first_node("behaviour4TimeS")->value());

		/*Create the npc*/
		Npc* n = new Npc(name, id, idleUpPath, idleDownPath, idleLeftPath, idleRightPath, numberOfFrames, walkUpPath, walkDownPath, walkLeftPath, walkRightPath, mapIconTexturePath, sf::Vector2f(x, y), hasQuest, interactable, behaviour, true);

		n->SetBedId(bedId);
		n->SetBedtimeH(bedtimeH);
		n->SetBedtimeM(bedtimeM);
		n->SetBedtimeS(bedtimeS);
		n->SetWakeTH(wakeTimeH);
		n->SetWakeTM(wakeTimeM);
		n->SetWakeTS(wakeTimeS);

		n->behvaiour1H = behaviour1H;
		n->behvaiour1M = behaviour1M;
		n->behvaiour1S = behaviour1S;
		n->behvaiour2H = behaviour2H;
		n->behvaiour2M = behaviour2M;
		n->behvaiour2S = behaviour2S;
		n->behvaiour3H = behaviour3H;
		n->behvaiour3M = behaviour3M;
		n->behvaiour3S = behaviour3S;
		n->behvaiour4H = behaviour4H;
		n->behvaiour4M = behaviour4M;
		n->behvaiour4S = behaviour4S;

		n->behaviour1 = behaviour;
		n->behaviour2 = behaviour2;
		n->behaviour3 = behaviour3;
		n->behaviour4 = behaviour4;

		npcs.push_back(n);
		//std::cout << "Size of npcVector: " << npcs.size() << std::endl;

		//std::cout << "------------------------------------------------------------" << std::endl;
		/*Move onto the next npc tag*/
		npc = npc->next_sibling("npc");
	}
}

/*Load the collidable objects from an xml file*/
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

/*Load the door objects from an xml file*/
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

/*Load the camp files from an xml file*/
void Area::LoadFires()
{
	if (campFirePath != "")
	{
		xml_document<> doc;
		std::ifstream file(campFirePath);
		std::stringstream buffer;
		buffer << file.rdbuf();
		file.close();
		std::string content(buffer.str());
		doc.parse<0>(&content[0]);

		xml_node<>* fireList = doc.first_node("FireList");
		xml_node<>* fireObject = fireList->first_node("fire");

		//load in each fires information and then create them
		while (fireObject != NULL)
		{
			int id = std::atoi(fireObject->first_node("id")->value());

			int x = std::atoi(fireObject->first_node("x")->value());

			int y = std::atoi(fireObject->first_node("y")->value());

			/*Create the camp fire*/
			CampFire * f = new CampFire(sf::Vector2f(x, y), id);
			campFires.push_back(f);

			/*Move onto the next bed object tag*/
			fireObject = fireObject->next_sibling("fire");
		}
	}
}

/*Update the map, minimap and npcs*/
void Area::Update(sf::Vector2f playerPos, int currentHours, int currentMinutes, int currentSeconds)
{
	for (int i = 0; i < campFires.size(); i++)
	{
		campFires.at(i)->Update();
	}

	for (int i = 0; i < npcs.size(); i++)
	{


		if (npcs.at(i)->GetBedtimeH() == currentHours && npcs.at(i)->GetBedtimeM() == currentMinutes && npcs.at(i)->GetBedtimeS() == currentSeconds)
		{
			
			for (int j = 0; j < beds.size(); j++)
			{
				if (beds.at(j)->GetId() == npcs.at(i)->GetBedId())
				{
					if (npcs.at(i)->IsTimeForBed() == false)
					{
						npcs.at(i)->SetIsTimeForBed(true);
						npcs.at(i)->SetBedPos(beds.at(j)->getPosition());
					}



				}
			}
		}

		for (int j = 0; j < beds.size(); j++)
		{
			if (npcs.at(i)->getGlobalBounds().intersects(beds.at(j)->getGlobalBounds()) && npcs.at(i)->IsTimeForBed() && beds.at(j)->GetId() == npcs.at(i)->GetBedId())
			{
				npcs.at(i)->SetInBed(true);
			}
		}

		if (npcs.at(i)->GetWakeTH() == currentHours && npcs.at(i)->GetWakeTM() == currentMinutes && npcs.at(i)->GetWakeTS() == currentSeconds)
		{
			//if (npcs.at(i)->IsInBed())
			//	npcs.at(i)->setPosition(sf::Vector2f(npcs.at(i)->getPosition().x + 50, npcs.at(i)->getPosition().y));
			npcs.at(i)->SetIsTimeForBed(false);
			npcs.at(i)->SetInBed(false);
		}

		//sort out which behaviour to do based on the current time and time the bahaviours should be carried out at
		if (currentHours >= npcs.at(i)->behvaiour1H && currentHours < npcs.at(i)->behvaiour2H)
		{
			npcs.at(i)->SetBehaviour(1);
		}
		else if (currentHours >= npcs.at(i)->behvaiour2H && currentHours < npcs.at(i)->behvaiour3H)
		{
			npcs.at(i)->SetBehaviour(2);
		}
		else if (currentHours >= npcs.at(i)->behvaiour3H && currentHours < npcs.at(i)->behvaiour4H)
		{
			npcs.at(i)->SetBehaviour(3);
		}
		else
		{
			npcs.at(i)->SetBehaviour(4);
		}


		if (npcs.at(i)->HasStolenItem())
		{
			AudioManager::GetInstance()->PlaySpatializedSoundEffect(true, 27, false, 10, 1, npcs.at(i)->getPosition().x, npcs.at(i)->getPosition().y);
		}

		npcs.at(i)->Update(playerPos);

		if (npcs.at(i)->CheckDistanceToPlayer() < 50)
			npcs.at(i)->setShowHint(true);
		else npcs.at(i)->setShowHint(false);

	}

	HandleNpcCollidableObjectsCollisions();
}

/*check if the player and an npc collides. Params are: player pointer, inventory pointer, stolen goods chest poiner, whether a is pressed or not. return true/false and a number based on what the npc does*/
std::pair<bool, int> Area::CheckNpcPlayerCollisions(Player* p, Inventory* playerInv, Chest* stolenGoodsChest, bool aPressed)
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
			if (npcs.at(i)->getCurrentBehaviour() == "follow")
				return std::make_pair(true, 2);
			else if (npcs.at(i)->getCurrentBehaviour() == "steal")
			{
				if (npcs.at(i)->HasStolenItem() == false)
				{
					npcs.at(i)->SetHasStolenItem(true);
					playerInv->SetItemToSteal();
					playerInv->SetItemToStealQuantity(playerInv->CheckQuantity(playerInv->GetItemToSteal(), false));
					playerInv->RemoveItemFromInventory(playerInv->GetItemToSteal(), playerInv->GetItemToStealQuantity());
					stolenGoodsChest->SetKeyForStoredItem(playerInv->GetItemToSteal());
					stolenGoodsChest->SetQuantityForStoredItem(playerInv->GetItemToStealQuantity());
					stolenGoodsChest->SetOpened(false);
					AudioManager::GetInstance()->PlaySoundEffectById(24, false);
				}
				return std::make_pair(true, 2);
			}
			else if (npcs.at(i)->doesNpcHaveQuest())
			{
				return std::make_pair(true, 0);
			}

			else if (npcs.at(i)->getCurrentBehaviour() == "shopkeeper")
			{
				return std::make_pair(true, 3);
			}
			else if (!npcs.at(i)->doesNpcHaveQuest() && npcs.at(i)->IsInteractable() 
				&& npcs.at(i)->getCurrentBehaviour() != "shopkeeper" && aPressed)//if npcs doesn't have a quest, is interactable, is not a shopkeeper and 'A' was pressed
			{
				npcs.at(i)->ChooseMessage();
				return std::make_pair(true, 1);
			}
			else return std::make_pair(true, 1);

			
		}
	}
	return std::make_pair(false,5);
}

/*deal with npc and collidable objects collisions*/
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
				npcs.at(i)->setPosition(npcs.at(i)->GetPreCollisionPos());//move the npc back to where it was before the collision
				break;
			}
			else
			{
				npcs.at(i)->setColliding(false);
				npcs.at(i)->SetPreCollisionPos(npcs.at(i)->getPosition());
			}
		}
	}

}

/*Check if the player collides with a collidable object. param is the players bounding box*/
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

/*load beds from xml file*/
void Area::LoadBeds()
{
	if (bedPath != "")
	{
		xml_document<> doc;
		std::ifstream file(bedPath);
		std::stringstream buffer;
		buffer << file.rdbuf();
		file.close();
		std::string content(buffer.str());
		doc.parse<0>(&content[0]);

		xml_node<>* bedList = doc.first_node("BedList");
		xml_node<>* bedObject = bedList->first_node("bed");

		//load in each beds information and then create them
		while (bedObject != NULL)
		{
			int id = std::atoi(bedObject->first_node("id")->value());

			int x = std::atoi(bedObject->first_node("x")->value());

			int y = std::atoi(bedObject->first_node("y")->value());

			/*Create the bed*/
			Bed * b = new Bed(id, sf::Vector2f(x, y));
			beds.push_back(b);

			/*Move onto the next bed object tag*/
			bedObject = bedObject->next_sibling("bed");
		}
	}
}

/*Load greetings for the npcs. params: players race, players gender*/
void Area::LoadNpcGreetings(int pRace, int pGender)
{
	for (int i = 0; i < npcs.size(); i++)
	{
		npcs.at(i)->LoadGreetings(pRace, pGender);
	}
}

/*Draw the npcs and collidable objects*/
void Area::Draw(sf::RenderTarget & window, bool debugMode)
{
	for (int i = 0; i < doors.size(); i++)
	{
		window.draw(*doors.at(i));
	}

	for (int i = 0; i < beds.size(); i++)
	{
		window.draw(*beds.at(i));
	}

	for (int i = 0; i < campFires.size(); i++)
	{
		window.draw(*campFires.at(i));
	}

	for (int i = 0; i < npcs.size(); i++)
	{
		npcs.at(i)->draw(window);
		window.draw(*npcs.at(i));
		if (debugMode)
			npcs.at(i)->DrawBoundingBox(window);
		npcs.at(i)->DrawBedCovers(window);
		npcs.at(i)->DrawMessage(window);
		npcs.at(i)->DrawFood(window);
	}

	for (int i = 0; i < collidableObjects.size(); i++)
	{
		if (debugMode)
			window.draw(*collidableObjects.at(i));
	}
}

void Area::MinimapDraw(sf::RenderTarget & window)
{
	for (int i = 0; i < npcs.size(); i++)
	{
		npcs.at(i)->MinimapDraw(window);
	}
}

/*Check if the player collides with a door. Params: player position, player bounding box. returns area door leads to*/
int Area::CheckDoorPlayerCollision(sf::Vector2f playerPos, sf::FloatRect playerBounds)
{
	//if within a certain distance of door check collision,
	//if colliding return the area the area manager should set its current area to
	for (int i = 0; i < doors.size(); i++)
	{
		float distanceToPlayer = sqrtf((((playerPos.x - doors.at(i)->getPosition().x)*(playerPos.x - doors.at(i)->getPosition().x)) + ((playerPos.y - doors.at(i)->getPosition().y)*(playerPos.y - doors.at(i)->getPosition().y))));

		if (distanceToPlayer < 300)//so don't bother checking for a collision unless we are reasonably close to the door in the first place
		{
			if (doors.at(i)->IsPlayerInDoorway(playerPos) && doors.at(i)->IsOpen())
			{
				return doors.at(i)->GetArea();
				break;
			}
		}
	}

	return -100;
}

void Area::ResetStealingNpc()
{
	for (int i = 0; i < npcs.size(); i++)
	{
		npcs.at(i)->SetHasStolenItem(false);
	}
}

/*unlock a door based on its id. param: id of door to unlock*/
void Area::UnlockDoorById(int doorId)
{
	for (int i = 0; i < doors.size(); i++)
	{
		if (doors.at(i)->GetId() == doorId)
			doors.at(i)->SetOpen(true);
	}
}
