#ifndef PAUSEMENU_H
#define PAUSEMENU_H

class PauseMenu
{
private:
	sf::Font font;
	sf::Text heading;
	sf::Clock flashClock;

	int screenW;
	int screenH;

	sf::Text menuItems[3];
	int currentSelected;

	bool canMove;
	bool canSelect;

	//for spritesheet handling
	sf::Vector2i framePosition;
	sf::Vector2i frameSize;
	sf::IntRect frame;

	sf::Texture punchAnimTexture;
	sf::Sprite punchAnimSprite;

	/*The total number of frames in the sheet*/
	int numFrames;

	/*How long does it take to move through each frame*/
	float animationTime;

	/*clock for moving through the sheet*/
	sf::Clock animationClock;

	sf::Texture backgroundTexture;
	sf::Sprite backgroundSprite;

public:
	PauseMenu(sf::Font f, int sw, int sh);
	~PauseMenu();

	/*Load the correct texture to represent the player waiting in the pause menu*/
	void SetPunchTexture(int race, int gender);

	//move up through the menu
	void NavUp();
	//Move down through the menu
	void NavDown();

	//update animation and colour change
	void Update();

	//draw. param: render target
	void Draw(sf::RenderTarget& window);

	bool GetCanMove();
	void SetCanMove(bool cm);
	bool GetCanSelect();
	void SetCanSelect(bool cs);
	int GetCurrentSelected();
};

#endif
