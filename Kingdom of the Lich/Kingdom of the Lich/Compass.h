#ifndef COMPASS_H
#define COMPASS_H

class Compass : public sf::Drawable, public sf::Transformable
{
public:
	//constructor
	Compass(int sW, int sH, float yPos);
	//destructor
	~Compass();

	//update the direction the compass needle is pointing in
	void UpdateNeedle(sf::Vector2f playerPos, sf::Vector2f objectivePos);

	void draw(sf::RenderTarget& window, sf::RenderStates state) const;
	//draw the compass and needle
	void Compass::draw(sf::RenderTarget& window);

private:
	//sprite and texture for compass body
	sf::Texture bodyTexture;
	sf::Sprite compassBody;
	//sprite and texture for compass needle
	sf::Sprite needle;
	sf::Texture needleTexture;

	int screenW;
	int screenH;

};


#endif
