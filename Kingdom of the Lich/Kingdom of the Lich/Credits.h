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
	/*constructor. params: screen width and screen height*/
	Credits(int sw, int sh);

	//destructor
	~Credits();

	//update
	void Update();


	//draw. param: render target
	void Draw(sf::RenderTarget& window);
};

#endif
