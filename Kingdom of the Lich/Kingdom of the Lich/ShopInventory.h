#ifndef SHOPINVENTORY_H
#define SHOPINVENTORY_H

#include "Item.h"

class ShopInventory
{
private:
	//how many items are in stock(maybe display this when the player is choosing to buy or sell
	int numItemsInStock;//load all possible items in but only show up to this index
	//the name of the shops owner
	std::string ownersName;
	//how many gems the shop has
	int availableGems;
	//the currently selected item
	int currentSelected;
	//vector of pairs: item and quantity? when zero show out of stock
	std::vector<std::pair<Item*, int>> stock;

	std::string stockFilePath;
public:
	ShopInventory(int niStock, std::string oName, int availGems, std::string sfp);
	~ShopInventory();

	void LoadStock();

	void NavRight();
	void NavLeft();

	void Draw(sf::RenderTarget& window);
};

#endif
