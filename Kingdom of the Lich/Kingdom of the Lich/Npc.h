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
	sf::Vector2f wanderPos;

public: 
	//name, id, race, gender, texturePath, mapIconTexturePath, x, y, hasQuest, behaviour, show keyboard or controller hint
	Npc(std::string n, int i, std::string texturePath, std::string mapIconTexturePath, sf::Vector2f pos, bool quest, std::string beh, bool controller);

	//Load the correct texture for the interact hint
	void LoadInteractHintTexture(bool controllerHint);

	~Npc();

	void Update(sf::Vector2f playerPos);

	void Wander();

	void draw(sf::RenderTarget& window);

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
