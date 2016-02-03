#ifndef ENEMY_H
#define ENEMY_H

//rapidxml stuff
#include "rapidxml_utils.hpp"
using namespace rapidxml;
#include <sstream> // std::stringstream

#include "Attack.h"

class Enemy : public sf::Sprite
{
private:
	sf::Texture texture;

	float health;

	float rarity;

	enum EnemyTypes
	{
		TRAINING,
		MELEE,
		RANGED
	};

	int type;

	sf::RectangleShape boundingBox;

	//for representing the enemy on the minimap
	sf::Texture minimapTexture;
	sf::Sprite minimapSprite;

	enum State
	{
		Healthy,
		Hurt,
		HurtBadly
	};
	int currentState;

	std::vector<Attack*> attacks;

	int numHealingItems;

public:
	/*Constructor, params are assetPath, health, how rare the enemy is, the enemy type*/
	Enemy(std::string assetPath, float h, float r, int t, sf::Vector2f pos);

	~Enemy();

	void Update();

	std::string TakeTurn(Player* p);

	void DrawBoundingBox(sf::RenderTarget& window);

	/*draw the enemy on the minimap*/
	void MinimapDraw(sf::RenderTarget& window);

	float GetHealth() { return health; }

	void setHealth(float h) { health = h; }
};

#endif
