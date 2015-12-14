#ifndef CHEST_H
#define CHEST_H

class Chest : public sf::Sprite
{
private:
	sf::Sprite sprite;

	sf::Texture texture;

	std::string keyForStoredItem;

	bool opened;

	int quantityOfStoredItem;

	sf::Sprite interactHintSprite;
	sf::Texture interactHintTexture;

	sf::RectangleShape boundingBox;

	bool showHint;

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

	//draw hint
	void DrawHint(sf::RenderTarget& window);

	void DrawBoundingBox(sf::RenderTarget& window);

	//gets
	std::string getKeyForStoredItem() { return keyForStoredItem; }
	sf::Sprite getSprite() { return sprite; }
	bool getOpened() { return opened; }
	void setShowHint(bool s) { showHint = s; }
};

#endif
