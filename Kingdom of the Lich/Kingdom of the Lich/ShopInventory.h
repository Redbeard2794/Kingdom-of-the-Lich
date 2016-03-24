#ifndef SHOPINVENTORY_H
#define SHOPINVENTORY_H

#include "Item.h"
#include "Inventory.h"

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
	bool canMove;
	bool canSelect;
	//vector of pairs: item and quantity? when zero show out of stock
	std::vector<std::pair<Item*, int>> stock;

	std::string stockFilePath;

	sf::Texture tableTexture;
	sf::Sprite tableSprite;

	int screenW;
	int screenH;

	int playersMoney;

	sf::Font font;

	sf::Text playerMoneyText;
	sf::Text shopMoneyText;

	std::vector<sf::Text*> itemQuantityTexts;
	std::vector<sf::Text*> itemPriceTexts;

public:
	ShopInventory(int niStock, std::string oName, int availGems, std::string sfp, int sw, int sh, sf::Font f);
	~ShopInventory();

	void LoadStock();

	void NavRight();
	void NavLeft();

	void Update(int playerG);

	void Draw(sf::RenderTarget& window);

	void PurchaseItem(int playerGems, Inventory* playerInv);

	std::string GetKeyOfCurrentItem();
	int GetPriceOfCurrentItem();

	//check how many items the shop has in stock
	int CheckNumItemsInStock();
	//set the number of items in stock to be the number passed in
	void SetNumItemsInStock(int i);
	//retrieve the name of the shop's owner
	std::string GetOwnersName();
	//Check how many gems the shop has to barter with
	int GetAvailableGems();
	//set the number of gems the shop has to barter with
	void SetAvalailableGems(int g);

	bool GetCanMove();
	void SetCanMove(bool sel);
	bool GetCanSelect();
	void SetCanSelect(bool sel);
};

#endif
