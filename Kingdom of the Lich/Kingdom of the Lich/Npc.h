#ifndef NPC_H
#define NPC_H

class Npc : public sf::Drawable, public sf::Transformable
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

	//inherited draw functions(from sf::Drawable and sf::Transformable
	void draw(sf::RenderTarget& window, sf::RenderStates state) const;
	void draw(sf::RenderTarget& window);

	//gets and sets
	sf::Sprite getSprite() { return m_sprite; }
};

#endif
