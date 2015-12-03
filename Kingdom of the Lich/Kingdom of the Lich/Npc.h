#ifndef NPC_H
#define NPC_H

class Npc : public sf::Sprite
{
private:
	std::string name;

	int id;

	sf::Texture m_texture;

	sf::Texture npcMinimapIconTexture;

	sf::Sprite npcMinimapIcon;

	bool hasQuest;

	std::string behaviour;


	sf::Sprite interactHintSprite;
	sf::Texture interactHintTexture;

	sf::Clock behaviourClock;

	//for wandering
	sf::Vector2f wanderPos;
	sf::Vector2f prevPos;
	int timeBetweenWander;

	//for walkPattern
	std::vector<sf::Vector2f> patternPoints;
	int currentPointIndex;
	int prevPointIndex;
	sf::Vector2f direction;

public: 
	//name, id, race, gender, texturePath, mapIconTexturePath, x, y, hasQuest, behaviour, show keyboard or controller hint
	Npc(std::string n, int i, std::string texturePath, std::string mapIconTexturePath, sf::Vector2f pos, bool quest, std::string beh, bool controller);

	//Load the correct texture for the interact hint
	void LoadInteractHintTexture(bool controllerHint);

	~Npc();

	void Update(sf::Vector2f playerPos);
	
	/*Wander to random points within 100 pixels on either the x or y and then stand there for up to 7 seconds*/
	void Wander();

	/*Walk around in a rectangle from the points set in the constructor*/
	void walkPattern();

	/*Follow the position that is passed in. This is the Seek algorithm*/
	void Follow(sf::Vector2f positionToFollow);

	/*Draw the interaction hint sprite*/
	void draw(sf::RenderTarget& window);
	
	/*Draw the npc on the minimap as an icon*/
	void MinimapDraw(sf::RenderTarget& window);

	//gets

	//name
	std::string getNpcName();
	//id
	int getNpcId();
	//hasQuest
	bool doesNpcHaveQuest();
	//behaviour
	std::string getBehaviour();
};

#endif
