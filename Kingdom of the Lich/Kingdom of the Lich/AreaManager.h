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
		GENERALSTORE1
	};
	int currentArea;

public:
	AreaManager();
	~AreaManager();

	void Update(sf::Vector2f playerPos);

	void ChangeArea(int areaToChangeTo);

	std::pair<bool, int> CheckCollisionPlayerNpcs(Player* p);

	bool CheckPlayerCollidableObjectsCollisions(sf::FloatRect playerBounds);

	void Draw(sf::RenderTarget& window, bool debugMode);

	void MinimapDraw(sf::RenderTarget& window);

	int GetCurrentArea();
};

#endif