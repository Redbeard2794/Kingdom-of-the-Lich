#ifndef NPC_H
#define NPC_H

class Npc : public sf::Sprite
{
private:
	std::string name;
	int id;
	sf::Texture m_texture;

	sf::Sprite interactHintSprite;
	sf::Texture interactHintTexture;

	bool hasQuest;

public: 
	Npc(std::string n, int i, sf::Vector2f pos);

	//Load the correct texture for the interact hint
	void LoadInteractHintTexture(bool controllerHint);

	~Npc();

	void Update(sf::Vector2f playerPos);

	void draw(sf::RenderTarget& window);
};

#endif
