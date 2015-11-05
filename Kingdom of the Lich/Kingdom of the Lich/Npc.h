#ifndef NPC_H
#define NPC_H

class Npc : public sf::Sprite
{
private:
	std::string name;
	int id;
	sf::Texture m_texture;
	sf::Sprite m_sprite;

	bool hasQuest;

public: 
	Npc(std::string n, int i, sf::Vector2f pos);

	~Npc();

	void Update();

	//gets and sets
	sf::Sprite getSprite() { return m_sprite; }
};

#endif
