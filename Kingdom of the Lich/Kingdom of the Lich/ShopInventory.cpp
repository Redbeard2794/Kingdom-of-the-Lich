#include "stdafx.h"
#include "ShopInventory.h"

ShopInventory::ShopInventory(int niStock, std::string oName, int availGems, std::string sfp)
{
	numItemsInStock = niStock;
	ownersName = oName;
	availableGems = availGems;
	stockFilePath = sfp;
	currentSelected = 0;

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

		/*Create the item*/
		Item* i = new Item(key, texturePath);
		stock.push_back(std::make_pair(i, quantity));

		/*Move onto the next item object tag*/
		item = item->next_sibling("Item");
	}
}

void ShopInventory::Draw(sf::RenderTarget & window)
{
	for (int i = 0; i < numItemsInStock; i++)
	{
		window.draw(*stock.at(i).first);
	}
}
