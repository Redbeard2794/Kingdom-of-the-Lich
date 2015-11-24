#ifndef HUD_H
#define HUD_H

class Hud
{
private:
	sf::Font font;

	sf::Texture overlayTexture;
	sf::Sprite overlaySprite;

	sf::Texture gemIconTexture;
	sf::Sprite gemIconSprite;
	sf::Text gemBalance;

	sf::Text currentQuestText;

	Compass* compass;
public:
	/*Constructor, params: sf::Font for text*/
	Hud(sf::Font f);

	/*Destructor*/
	~Hud();

	/*Load all textures and set up text*/
	void LoadAssets();

	/*Update the various elements that make up the Hud such as number of gems and current objective,
	params are questName, number of gems the player has, objectives location and player's position
	*/
	void Update(sf::String objText, int numGems, sf::Vector2f objectivePos, sf::Vector2f playerPos);

	/*Draw all the elements that make up the Hud*/
	void Draw(sf::RenderTarget& window);
};

#endif
