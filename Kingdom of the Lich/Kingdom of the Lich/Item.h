#ifndef ITEM_H
#define ITEM_H

class Item : public sf::Sprite
{
private:
	std::string itemKey;
	sf::Texture texture;
public:
	Item(std::string key, std::string texturePath);
	~Item();
};

#endif
