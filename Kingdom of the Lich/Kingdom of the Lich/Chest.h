#ifndef CHEST_H
#define CHEST_H

class Chest : public sf::Drawable, public sf::Transformable
{
private:
	sf::Sprite sprite;

	sf::Texture texture;

	std::string keyForStoredItem;
public:
	/*Constructor*/
	Chest(std::string itemKey);

	/*Destructor*/
	~Chest();

	void draw(sf::RenderTarget& window, sf::RenderStates state) const;
	
	/*Draw*/
	void draw(sf::RenderTarget& window);

	//gets
	std::string getKeyForStoredItem() { return keyForStoredItem; }
};

#endif
