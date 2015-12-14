#include "stdafx.h"
#include "Chest.h"

/*Constructor*/
Chest::Chest(std::string itemKey, int quantity) : keyForStoredItem(itemKey), quantityOfStoredItem(quantity)
{
	//set up the texture and sprite
	texture.loadFromFile("Assets/Chests/plainChest.png");
	setTexture(texture);
	setOrigin(texture.getSize().x / 2, texture.getSize().y / 2);
	setPosition(sf::Vector2f(SCREENWIDTH/2, SCREENHEIGHT/2));//setPosition rather than sprite.setPosition?

	opened = false;//The chest is not open yet

	boundingBox.setOutlineThickness(2);
	boundingBox.setOutlineColor(sf::Color::Yellow);
	boundingBox.setFillColor(sf::Color::Transparent);

	showHint = false;
}

/*Destructor*/
Chest::~Chest()
{

}

//Load the correct texture for the interact hint
void Chest::LoadInteractHintTexture(bool controllerHint)
{
	std::cout << "Loading chest hints" << std::endl;
	if (controllerHint == true)
	{
		if (interactHintTexture.loadFromFile("Assets/ControllerHints/pressAtoOpenHint.png")) {}
		else interactHintTexture.loadFromFile("Assets/Debug.png");	//if it fails load placeholder
	}
	else
	{
		if (interactHintTexture.loadFromFile("Assets/KeyboardAndMouseHints/pressEtoOpenHint.png")) {}
		else interactHintTexture.loadFromFile("Assets/Debug.png");	//if it fails load placeholder
	}
	interactHintSprite.setTexture(interactHintTexture);
	interactHintSprite.setOrigin(interactHintTexture.getSize().x / 2, interactHintTexture.getSize().y / 2);
	interactHintSprite.setPosition(sf::Vector2f(getPosition().x, getPosition().y+30));
}

/*Add the items contained in the chest to the inventory and open the chest*/
void Chest::OpenChest(Inventory* inv)
{
	inv->AddItemToInventory(keyForStoredItem, quantityOfStoredItem);
	opened = true;
}

void Chest::Update(sf::Vector2f playerPos)
{
	sf::Vector2f pos = getPosition();
	float distance = sqrtf((((pos.x - playerPos.x)*(pos.x - playerPos.x)) + ((pos.y - playerPos.y)*(pos.y - playerPos.y))));

	if (distance < 50)
		showHint = true;
	else showHint = false;


	if (showHint)
		interactHintSprite.setColor(sf::Color::White);
	else interactHintSprite.setColor(sf::Color::Transparent);

	//change the colour based in whether the chest is open or not
	if (opened == true)
	{
		setColor(sf::Color(255, 255, 255, 127));
	}
	else
	{
		setColor(sf::Color(255, 255, 255, 255));
	}
}

//draw hint
void Chest::DrawHint(sf::RenderTarget& window)
{
	if (interactHintSprite.getColor() == sf::Color::White)
		window.draw(interactHintSprite);
}

void Chest::DrawBoundingBox(sf::RenderTarget & window)
{
	boundingBox.setPosition(sf::Vector2f(getGlobalBounds().left, getGlobalBounds().top));
	boundingBox.setSize(sf::Vector2f(getGlobalBounds().width, getGlobalBounds().height));
	boundingBox.setRotation(getRotation());
	window.draw(boundingBox);
}
