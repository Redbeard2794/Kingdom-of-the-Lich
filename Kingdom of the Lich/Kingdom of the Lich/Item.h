#ifndef ITEM_H
#define ITEM_H

class Item : public sf::Sprite
{
private:
	std::string itemKey;//item key
	std::string texPath;//texture path
	sf::Texture texture;
	int value;//how much is it worth?
public:
	//constructor. params: item key, texture path, value of the item
	Item(std::string key, std::string texturePath, int val);

	//destructor
	~Item();

	std::string RetrieveKey();
	int GetValue();
	std::string GetTextPath();
};

#endif
