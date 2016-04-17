#ifndef BED_H
#define BED_H

class Bed : public sf::Sprite
{
private:
	int id;
	sf::Texture texture;
public:
	Bed(int i, sf::Vector2f pos);
	~Bed();

	int GetId();
};

#endif
