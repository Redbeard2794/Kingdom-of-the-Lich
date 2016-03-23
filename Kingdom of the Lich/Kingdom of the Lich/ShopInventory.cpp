#include "stdafx.h"
#include "ShopInventory.h"

ShopInventory::ShopInventory(int niStock, std::string oName, int availGems, std::string sfp)
{
	numItemsInStock = niStock;
	ownersName = oName;
	availableGems = availGems;
	stockFilePath = sfp;
	currentSelected = 0;
	canMove = true;

	LoadStock();
}

ShopInventory::~ShopInventory()
{
}

void ShopInventory::LoadStock()
{
	xml_document<> doc;
	std::ifstream file(stockFilePath);
	std::stringstream buffer;
	buffer << file.rdbuf();
	file.close();
	std::string content(buffer.str());
	doc.parse<0>(&content[0]);

	xml_node<>* stockList = doc.first_node("StockList");
	xml_node<>* item = stockList->first_node("Item");

	while (item != NULL)
	{
		std::string key = item->first_node("key")->value();
		std::string texturePath = item->first_node("texturePath")->value();
		int quantity = std::atoi(item->first_node("quantity")->value());
		int value = std::atoi(item->first_node("value")->value());

		/*Create the item*/
		Item* i = new Item(key, texturePath, value);
		stock.push_back(std::make_pair(i, quantity));

		/*Move onto the next item object tag*/
		item = item->next_sibling("Item");
	}

	for (int i = 0; i < numItemsInStock; i++)
	{
		stock.at(i).first->setPosition(sf::Vector2f(50 * ((i + 1)*2), 100));
	}
	stock.at(currentSelected).first->setColor(sf::Color::Blue);
}

void ShopInventory::NavRight()
{
	if (canMove == true)
	{
		if (currentSelected == numItemsInStock-1)
			currentSelected = 0;
		else currentSelected += 1;

		for (int i = 0; i < numItemsInStock; i++)
		{
			stock.at(i).first->setColor(sf::Color::White);
		}
		stock.at(currentSelected).first->setColor(sf::Color::Blue);
	}
}

void ShopInventory::NavLeft()
{
	if (canMove == true)
	{
		if (currentSelected == 0)
			currentSelected = numItemsInStock - 1;
		else currentSelected -= 1;

		for (int i = 0; i < numItemsInStock; i++)
		{
			stock.at(i).first->setColor(sf::Color::White);
		}
		stock.at(currentSelected).first->setColor(sf::Color::Blue);
	}
}

void ShopInventory::Draw(sf::RenderTarget & window)
{
	for (int i = 0; i < numItemsInStock; i++)
	{
		window.draw(*stock.at(i).first);
	}
}

void ShopInventory::PurchaseItem(int playerGems, Inventory * playerInv)
{
	std::string purchaseKey = GetKeyOfCurrentItem();
	int cost = GetPriceOfCurrentItem();

	if (playerGems >= cost)
	{
		if (stock.at(currentSelected).second > 0)
		{
			playerInv->AddItemToInventory(purchaseKey, 1);
			stock.at(currentSelected).second -= 1;
			playerInv->RemoveItemFromInventory("Gems", cost);
		}
		else std::cout << purchaseKey << " is out of stock at the moment." << std::endl;
	}
	else std::cout << "You do not possess enough gems to buy " << purchaseKey << std::endl;
}

std::string ShopInventory::GetKeyOfCurrentItem()
{
	return stock.at(currentSelected).first->RetrieveKey();
}

int ShopInventory::GetPriceOfCurrentItem()
{
	return stock.at(currentSelected).first->GetValue();
}

//check how many items the shop has in stock
int ShopInventory::CheckNumItemsInStock()
{
	return numItemsInStock;
}

//set the number of items in stock to be the number passed in
void ShopInventory::SetNumItemsInStock(int i)
{
	numItemsInStock = i;
}

//retrieve the name of the shop's owner
std::string ShopInventory::GetOwnersName()
{
	return ownersName;
}

//Check how many gems the shop has to barter with
int ShopInventory::GetAvailableGems()
{
	return availableGems;
}

//set the number of gems the shop has to barter with
void ShopInventory::SetAvalailableGems(int g)
{
	availableGems = g;
}

bool ShopInventory::GetCanMove()
{
	return canMove;
}

void ShopInventory::SetCanMove(bool sel)
{
	canMove = sel;
}

bool ShopInventory::GetCanSelect()
{
	return canSelect;
}

void ShopInventory::SetCanSelect(bool sel)
{
	canSelect = sel;
}
