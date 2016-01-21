#ifndef INVENTORY_H
#define INVENTORY_H

class Inventory
{
private:
	int screenW;
	int screenH;

	int currentlySelectedItem;
	bool canMove;

	//map containg items with their quantity
	std::map<std::string, int> inventoryItems;
	//background stuff for UI
	sf::Sprite backgroundSprite;
	sf::Texture backgroundTexture;

	sf::Text headerText;
	sf::Font font;
	//all the item keys
	std::vector<std::string> itemKeys;

	//struct DrawableItem
	//{
	//	std::string key;
	//	sf::Vector2f position;
	//};

	std::vector<std::string> drawableItems;

	//item icon stuff
	sf::Texture healthPotTexture;
	sf::Sprite healthPotSprite;

	sf::Texture aleBottleTexture;
	sf::Sprite aleBottleSprite;

	sf::Texture loafOfBreadTexture;
	sf::Sprite loafOfBreadSprite;

	sf::Texture baracksKeyTexture;
	sf::Sprite baracksKeySprite;

	sf::Texture parchmentTexture;
	sf::Sprite parchmentSprite;

	sf::Texture inkBottleTexture;
	sf::Sprite inkBottleSprite;

	sf::Texture gemTexture;
	sf::Sprite gemSprite;

	sf::Texture appleTexture;
	sf::Sprite appleSprite;

	sf::Texture quillTexture;
	sf::Sprite quillSprite;

	sf::Text itemTexts[9];

	//hint stuff
	bool showControllerHints;
	sf::Sprite exitHintSprite;
	sf::Texture exitHintTexture;
public:
	//these need to be visible in other classes....Is there a better way of doing this?
	struct items
	{
		std::string key;
	}i_healthPotion, i_ale, i_bread, i_apple, i_gems, i_baracksKey, i_parchment, i_inkBottle, i_quill;

	/*Constructor*/
	Inventory(sf::Font f, bool controller, int sw, int sh);

	/*Destructor*/
	~Inventory();

	/*Initialise all item in inventory to have '0' quantity*/
	void InitialiseInventoryItems();

	/*
	Prints out the contents of the inventory(all items+quantities)
	For debugging mostly.
	*/
	void PrintAllInventory();

	/*
	Checks the quantity of an item
	parameter is the item name
	*/
	int CheckQuantity(std::string itemToCheck, bool output);

	/*
	Adds an item to the inventory
	parameter 1 is the name of the item you want to add
	parameter 2 is the amount of that item that you want to add
	*/
	void AddItemToInventory(std::string itemToAddTo, int quantityToAdd);

	/*
	Remove an item from the inventory
	parameter 1 is the name of the item you want to remove
	parameter 2 is the amount of that item that you want to remove
	*/
	void RemoveItemFromInventory(std::string itemToRemoveFrom, int quantityToRemove);

	/*
	Use an item from the inventory
	parameter is the itme to use
	*/
	void UseItem(int itemToUseIndex, Player& p);

	//check items that should be drawn i.e. items that have a quantity > 0
	void CheckItemsToShow();

	void NavigateUp();

	void NavigateDown();

	void PositionText();

	void UpdateDrawableVector();

	/*Draw items that have a quantity > 0*/
	void Draw(sf::RenderTarget& window);

	bool getCanMove();

	void setCanMove(bool b);

	int getCurrentlySelectedItem();

};

#endif
