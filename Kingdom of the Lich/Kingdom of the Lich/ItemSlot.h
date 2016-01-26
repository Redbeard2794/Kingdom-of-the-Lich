#ifndef ITEMSLOT_H
#define ITEMSLOT_H

class ItemSlot
{
private:
	std::string currentItemKey;

	int slotNumber;

	bool open;

	sf::Text text;
	sf::Font font;

	bool selected;

public:

	//constructor. param is slotNumber
	ItemSlot(std::string key, int number, sf::Font f);

	//destructor
	~ItemSlot();

	//Fill an empty slot. param is key of item to store in slot
	void FillSlot(std::string key);

	//Empty a filled slot
	void EmptySlot();

	//Get the key of the currently stored item
	std::string GetCurrentItemKey();

	//get the slot number
	int GetSlotNumber();

	//is the slot open?
	bool IsOpen();

	//reset the slot number and its position
	void ResetSlotNumAndPos(int number);

	void Draw(sf::RenderTarget& window, int quantity, sf::Color col, bool sel);
};

#endif
