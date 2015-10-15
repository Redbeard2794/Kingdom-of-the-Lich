#ifndef COMPASS_H
#define COMPASS_H

class Compass : public sf::Drawable, public sf::Transformable
{
public:
	Compass();
	~Compass();

	void UpdateNeedle(sf::Vector2f playerPos, sf::Vector2f objectivePos);

	void draw(sf::RenderTarget& window, sf::RenderStates state) const;
	void Compass::draw(sf::RenderTarget& window);

private:
	sf::Texture bodyTexture;
	sf::Sprite compassBody;

	sf::Sprite needle;
	sf::Texture needleTexture;

};


#endif
