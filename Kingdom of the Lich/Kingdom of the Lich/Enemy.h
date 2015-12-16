#ifndef ENEMY_H
#define ENEMY_H

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

public:
	/*Constructor, params are assetPath, health, how rare the enemy is, the enemy type*/
	Enemy(std::string assetPath, float h, float r, int t, sf::Vector2f pos);

	~Enemy();

	void DrawBoundingBox(sf::RenderTarget& window);

};

#endif
