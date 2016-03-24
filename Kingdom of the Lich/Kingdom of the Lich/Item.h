#ifndef ITEM_H
#define ITEM_H

class Item : public sf::Sprite
{
private:
	std::string itemKey;
	std::string texPath;
	sf::Texture texture;
	int value;
public:
	Item(std::string key, std::string texturePath, int val);
	~Item();

	std::string RetrieveKey();
	int GetValue();
	std::string GetTextPath();
};

#endif
