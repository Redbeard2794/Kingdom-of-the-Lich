#ifndef CREDITS_H
#define CREDITS_H

class Credits
{
private:
	sf::Texture summoningCircleTexture;
	sf::Sprite summoningCircleSprite;

	int screenW;
	int screenH;
public:
	Credits(int sw, int sh);

	~Credits();

	void Update();

	void Draw(sf::RenderTarget& window);
};

#endif
