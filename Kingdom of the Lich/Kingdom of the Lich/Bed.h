#ifndef BED_H
#define BED_H

class Bed : public sf::Sprite
{
private:
	int id;//bed id
	sf::Texture texture;
public:
	/*constructor. params are an id and a position*/
	Bed(int i, sf::Vector2f pos);

	//destructor
	~Bed();

	/*Retrieve this beds id*/
	int GetId();
};

#endif
