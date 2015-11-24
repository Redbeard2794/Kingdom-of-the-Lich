#include "stdafx.h"
#include "Hud.h"

/*Constructor, params: sf::Font for text*/
Hud::Hud(sf::Font f) : font(f)
{
	//load all assets and text
	LoadAssets();
	//intialise the compass
	compass = new Compass();
}

/*Destructor*/
Hud::~Hud()
{

}

/*Load all textures and set up text*/
void Hud::LoadAssets()
{
	//basic overlay
	overlayTexture.loadFromFile("Assets/HudBackground.png");
	overlaySprite.setTexture(overlayTexture);
	overlaySprite.setPosition(0, 500);

	//the current quest
	currentQuestText.setFont(font);
	currentQuestText.setColor(sf::Color::Black);
	currentQuestText.setString("Current Quest Name: ");
	currentQuestText.setPosition(540, 500);
	currentQuestText.setCharacterSize(12);

	//an icon for the player's gems
	if (gemIconTexture.loadFromFile("Assets/Icons/Items/gemsIcon.png")) {}
	else gemIconTexture.loadFromFile("Assets/Debug.png");	//if it fails load placeholder
	gemIconSprite.setTexture(gemIconTexture);
	gemIconSprite.setOrigin(sf::Vector2f(gemIconTexture.getSize().x / 2, gemIconTexture.getSize().y / 2));
	gemIconSprite.setPosition(sf::Vector2f(20, 525));

	//the amount of gems the player has
	gemBalance.setFont(font);
	gemBalance.setColor(sf::Color::Black);
	gemBalance.setString("0");
	gemBalance.setPosition(40, 517);
	gemBalance.setCharacterSize(12);
}

/*Update the various elements that make up the Hud such as number of gems and current objective, 
params are questName, number of gems the player has, objectives location and player's position
*/
void Hud::Update(sf::String objTxt, int numGems, sf::Vector2f objectivePos, sf::Vector2f playerPos)
{
	//update the text for the current quest
	currentQuestText.setString("Current Quest Name: " + objTxt);
	//update the direction the compass needle is pointing
	compass->UpdateNeedle(playerPos, objectivePos);
	//update the value of gems
	gemBalance.setString(std::to_string(numGems));
}

/*Draw all the elements that make up the Hud*/
void Hud::Draw(sf::RenderTarget& window)
{
	window.draw(overlaySprite);
	window.draw(currentQuestText);
	window.draw(gemIconSprite);
	window.draw(gemBalance);
	compass->draw(window);
}