#ifndef CHEST_H
#define CHEST_H

class Chest : public sf::Drawable, public sf::Transformable
{
private:
	sf::Sprite sprite;

	sf::Texture texture;

	std::string keyForStoredItem;

	bool opened;

	int quantityOfStoredItem;

public:
	/*Constructor*/
	Chest(std::string itemKey, int quantity);

	/*Destructor*/
	~Chest();

	/**/
	void OpenChest(Inventory* inv);

	void draw(sf::RenderTarget& window, sf::RenderStates state) const;
	
	/*Draw*/
	void draw(sf::RenderTarget& window);

	//gets
	std::string getKeyForStoredItem() { return keyForStoredItem; }
	sf::Sprite getSprite() { return sprite; }
	bool getOpened() { return opened; }
};

#endif
