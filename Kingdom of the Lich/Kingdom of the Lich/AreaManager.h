#ifndef AREAMANAGER_H
#define AREAMANAGER_H


class AreaManager
{
private:
	std::vector<Area*> areas;//all areas in game

	enum Areas
	{
		TUTORIAL,
		SEWER,
		LellesQualityMerchandise,
		House1,
		House2,
		TheDrunkenDragonInn,
		NONE
	};
	int currentArea;

	int areaToChangeTo;//area to change to next
	bool readyToChangeArea;//are we ready to change area

	sf::Font font;
	sf::Text currentAreaText;

	int screenW;
	int screenH;

public:
	/*constructor. params: font, screen width, screen height*/
	AreaManager(sf::Font f, int sw, int sh);

	/*destructor*/
	~AreaManager();

	/*Update the current area and the current area text. params: player position, current time in hours, minutes and seconds*/
	void Update(sf::Vector2f playerPos, int currentHours, int currentMinutes, int currentSeconds);

	/*change the current area. param: index of area to change to*/
	void ChangeArea(int areaToChangeTo);

	/*check if the player and an npc collides. Params are: player pointer, inventory pointer, stolen goods chest poiner, whether a is pressed or not. return true/false and a number based on what the npc does*/
	std::pair<bool, int> CheckCollisionPlayerNpcs(Player* p, Inventory* playerInv, Chest* stolenGoodsChest, bool aPressed);

	/*deal with npc and collidable objects collisions*/
	bool CheckPlayerCollidableObjectsCollisions(sf::FloatRect playerBounds);

	/*Draw the current area. params area a render target and whether to draw debug mde stuff*/
	void Draw(sf::RenderTarget& window, bool debugMode);

	//draw the name of the current area
	void DrawCurrentAreaText(sf::RenderTarget& window);

	void MinimapDraw(sf::RenderTarget& window);

	void ResetAreaStealingNpcs();

	//unlock a door in the current area. param: id of door to unlock
	void UnlockDoorInCurrentArea(int id);

	int GetCurrentArea();

	//only used when loading a game
	void SetCurrentArea(int a);

	/*check for a collision with a door and get ready to change area*/
	void CheckDoors(sf::Vector2f playerPos, sf::FloatRect playerBounds);

	void LoadGreetings(int pRace, int pGender);

	int GetAreaToChangeTo();
	void SetAreaToChangeTo(int atc);

	bool IsReadyToChangeArea();
	void SetReadyToChangeArea(int r);
};

#endif