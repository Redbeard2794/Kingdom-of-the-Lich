#ifndef SHOPINVENTORY_H
#define SHOPINVENTORY_H

#include "Item.h"
#include "Inventory.h"
#include "Player.h"

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

	std::vector<std::pair<Item*, int>> playerInvItems;

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

	enum States
	{
		CHOICE,
		BUY,
		SELL
	};
	int currentState;

	sf::Text shopGreetText;
	sf::Text choices[2];//choices, choices, choices

	sf::Texture choiceBackgroundTexture;
	sf::Sprite choiceBackgroundSprite;

	bool canBackOut;

public:
	//constructor. params: number of items in stock, owners name, gems owned by shop, path to stock file, screen width, screen height, font
	ShopInventory(int niStock, std::string oName, int availGems, std::string sfp, int sw, int sh, sf::Font f);

	//destructor
	~ShopInventory();

	//load the shops stock from an xml file
	void LoadStock();

	//nav right in the menus
	void NavRight();
	//nav left in menus
	void NavLeft();

	//Update. param: players gems
	void Update(int playerG);

	//draw. param is a render target
	void Draw(sf::RenderTarget& window);

	//choose BUY or SELL. param in a pointer to the players inventory(only used for selling as we need to grab items)
	void MakeChoice(Inventory* inv);

	//buy an item. params are the player's gems and a pointer to the players inventory
	void PurchaseItem(int playerGems, Inventory* playerInv, Player* p);

	//sell an item. params are the player's gems and a pointer to the player's inventory
	void SellItem(int playerGems, Inventory* playerInv, Player* p);

	//grab the player's inventory in order to display items for them to sell. param is a pointer to the player's inventory
	void SetPlayerSellableItems(Inventory* playerInv);

	std::string GetKeyOfCurrentItem();
	int GetPriceOfCurrentItem();

	void SetChoiceTexture(int pRace, int pGender);

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

	int GetCurrentState();
	void SetCurrentState(int s);

	bool GetCanBackOut();
	void SetCanBackOut(bool c);
};

#endif
