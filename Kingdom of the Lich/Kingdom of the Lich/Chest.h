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

	sf::Sprite interactHintSprite;
	sf::Texture interactHintTexture;

public:
	/*Constructor*/
	Chest(std::string itemKey, int quantity);

	/*Destructor*/
	~Chest();

	//Load the correct texture for the interact hint
	void LoadInteractHintTexture(bool controllerHint);

	/*Add the items contained in the chest to the inventory and open the chest*/
	void OpenChest(Inventory* inv);

	void Update(sf::Vector2f playerPos);

	void draw(sf::RenderTarget& window, sf::RenderStates state) const;
	
	/*Draw*/
	void draw(sf::RenderTarget& window);

	//gets
	std::string getKeyForStoredItem() { return keyForStoredItem; }
	sf::Sprite getSprite() { return sprite; }
	bool getOpened() { return opened; }
};

#endif
