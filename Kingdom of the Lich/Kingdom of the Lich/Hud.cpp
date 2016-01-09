#include "stdafx.h"
#include "Hud.h"

/*Constructor, params: sf::Font for text*/
Hud::Hud(sf::Font f, int sw, int sh, sf::Vector2f framePos, sf::Vector2f frameSize) : font(f)
{
	screenW = sw;
	screenH = sh;
	//load all assets and text
	LoadAssets();
	//intialise the compass
	compass = new Compass(screenW, screenH, screenH - overlayTexture.getSize().y/2);

	mapFrameTexture.loadFromFile("Assets/Hud/background/window_red2mod.png");
	mapFrame.setTexture(&mapFrameTexture);
	mapFrame.setPosition(framePos);
	mapFrame.setSize(frameSize);
}

/*Destructor*/
Hud::~Hud()
{

}

/*Load all textures and set up text*/
void Hud::LoadAssets()
{
	//basic overlay
	overlayTexture.loadFromFile("Assets/Hud/background/window_red2mod" + std::to_string(screenW) + "x" + std::to_string(screenH) + ".png");
	overlaySprite.setTexture(overlayTexture);
	overlaySprite.setPosition(0, screenH - overlayTexture.getSize().y);

	//the current quest
	currentQuestText.setFont(font);
	currentQuestText.setColor(sf::Color::White);
	currentQuestText.setString("Current Quest Name: ");
	currentQuestText.setPosition(screenW/1.35, overlaySprite.getPosition().y+20);
	currentQuestText.setCharacterSize(13);

	//an icon for the player's gems
	if (gemIconTexture.loadFromFile("Assets/Icons/Items/gemsIcon.png")) {}
	else gemIconTexture.loadFromFile("Assets/Debug.png");	//if it fails load placeholder
	gemIconSprite.setTexture(gemIconTexture);
	gemIconSprite.setOrigin(sf::Vector2f(gemIconTexture.getSize().x / 2, gemIconTexture.getSize().y / 2));
	gemIconSprite.setPosition(sf::Vector2f(screenW / 13, overlaySprite.getPosition().y + 25));

	//the amount of gems the player has
	gemBalance.setFont(font);
	gemBalance.setColor(sf::Color::White);
	gemBalance.setString("0");
	gemBalance.setPosition(screenW / 10, overlaySprite.getPosition().y + 17);
	gemBalance.setCharacterSize(13);
}

/*Update the various elements that make up the Hud such as number of gems and current objective, 
params are questName, number of gems the player has, objectives location and player's position
*/
void Hud::Update(sf::String objTxt, int numGems, sf::Vector2f objectivePos, sf::Vector2f playerPos, bool showMinimap)
{
	//update the text for the current quest
	currentQuestText.setString("Current Quest Name: " + objTxt);
	//update the direction the compass needle is pointing
	compass->UpdateNeedle(playerPos, objectivePos);
	//update the value of gems
	gemBalance.setString(std::to_string(numGems));

	drawMinimapFrame = showMinimap;
}

/*Draw all the elements that make up the Hud*/
void Hud::Draw(sf::RenderTarget& window)
{
	window.draw(overlaySprite);
	window.draw(currentQuestText);
	window.draw(gemIconSprite);
	window.draw(gemBalance);
	if(drawMinimapFrame)
		window.draw(mapFrame);
	compass->draw(window);
}