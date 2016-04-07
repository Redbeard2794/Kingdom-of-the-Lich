#ifndef AREAMANAGER_H
#define AREAMANAGER_H

class AreaManager
{
private:
	std::vector<Area*> areas;

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

	int areaToChangeTo;
	bool readyToChangeArea;

	sf::Font font;
	sf::Text currentAreaText;

	int screenW;
	int screenH;

public:
	AreaManager(sf::Font f, int sw, int sh);
	~AreaManager();

	void Update(sf::Vector2f playerPos);

	void ChangeArea(int areaToChangeTo);

	std::pair<bool, int> CheckCollisionPlayerNpcs(Player* p);

	bool CheckPlayerCollidableObjectsCollisions(sf::FloatRect playerBounds);

	void Draw(sf::RenderTarget& window, bool debugMode);

	void DrawCurrentAreaText(sf::RenderTarget& window);

	void MinimapDraw(sf::RenderTarget& window);

	int GetCurrentArea();
	//only used when loading a game
	void SetCurrentArea(int a);

	void CheckDoors(sf::Vector2f playerPos, sf::FloatRect playerBounds);

	int GetAreaToChangeTo();
	void SetAreaToChangeTo(int atc);

	bool IsReadyToChangeArea();
	void SetReadyToChangeArea(int r);
};

#endif