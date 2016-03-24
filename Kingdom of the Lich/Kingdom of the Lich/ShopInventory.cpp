#include "stdafx.h"
#include "ShopInventory.h"

ShopInventory::ShopInventory(int niStock, std::string oName, int availGems, std::string sfp, int sw, int sh, sf::Font f) : screenW(sw), screenH(sh), font(f)
{
	numItemsInStock = niStock;
	ownersName = oName;
	availableGems = availGems;
	stockFilePath = sfp;
	currentSelected = 0;
	canMove = true;

	LoadStock();

	if (tableTexture.loadFromFile("Assets/CharacterCreation/table/table" + std::to_string(screenW) + "x" + std::to_string(screenH) + ".png")) {}
	else tableTexture.loadFromFile("Assets/CharacterCreation/table/table1.png");	//if it fails load placeholder
	tableSprite.setTexture(tableTexture);
	tableSprite.setPosition(0, 5);

	shopMoneyText.setFont(font);
	shopMoneyText.setColor(sf::Color::White);
	shopMoneyText.setString("Shop Gems: " + std::to_string(availableGems));
	shopMoneyText.setPosition(screenW / 5, screenH - 50);

	playersMoney = 0;
	playerMoneyText.setFont(font);
	playerMoneyText.setColor(sf::Color::White);
	playerMoneyText.setString("Your Gems: " + std::to_string(playersMoney));
	playerMoneyText.setPosition(screenW / 1.3, screenH - 50);
}

ShopInventory::~ShopInventory()
{
	stock.clear();//redo this so its proper
	itemQuantityTexts.clear();
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
		stock.at(i).first->setPosition(sf::Vector2f(100 * ((i + 1)), 100));
	}
	stock.at(currentSelected).first->setColor(sf::Color::Blue);

	for (int i = 0; i < numItemsInStock; i++)
	{
		sf::Text* text = new sf::Text();
		text->setFont(font);
		text->setColor(sf::Color::White);
		text->setString(std::to_string(stock.at(i).second));
		text->setPosition(stock.at(i).first->getPosition().x + 30, stock.at(i).first->getPosition().y - 45);
		text->setCharacterSize(20);
		itemQuantityTexts.push_back(text);

		sf::Text* text2 = new sf::Text();
		text2->setFont(font);
		text2->setColor(sf::Color::White);
		text2->setString("Gems: "+std::to_string(stock.at(i).first->GetValue()));
		text2->setPosition(stock.at(i).first->getPosition().x-15, stock.at(i).first->getPosition().y+45);
		text2->setCharacterSize(20);
		itemPriceTexts.push_back(text2);
	}
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

void ShopInventory::Update(int playerG)
{
	if (playersMoney != playerG)
		playersMoney = playerG;
	shopMoneyText.setString("Shop Gems: " + std::to_string(availableGems));
	playerMoneyText.setString("Your Gems: " + std::to_string(playersMoney));
	for (int i = 0; i < numItemsInStock; i++)
	{
		itemQuantityTexts.at(i)->setString("x"+std::to_string(stock.at(i).second));
		itemPriceTexts.at(i)->setString("Gems: " + std::to_string(stock.at(i).first->GetValue()));
	}
}

void ShopInventory::Draw(sf::RenderTarget & window)
{
	window.draw(tableSprite);
	window.draw(shopMoneyText);
	window.draw(playerMoneyText);
	for (int i = 0; i < numItemsInStock; i++)
	{
		window.draw(*stock.at(i).first);
		window.draw(*itemQuantityTexts.at(i));
		window.draw(*itemPriceTexts.at(i));
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
			availableGems += cost;
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
