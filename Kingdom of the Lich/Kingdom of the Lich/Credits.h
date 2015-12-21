#ifndef CREDITS_H
#define CREDITS_H

class Credits
{
private:
	sf::Texture summoningCircleTexture;
	sf::Sprite summoningCircleSprite;
public:
	Credits();

	~Credits();

	void Update();

	void Draw(sf::RenderTarget& window);
};

#endif
