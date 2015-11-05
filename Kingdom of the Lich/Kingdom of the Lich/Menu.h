#ifndef MENU_H
#define MENU_H

#define MAX_MAIN_MENU_ITEMS 5

class Menu
{
public:
	//constructor(params are font and whether to show controller hints or keyboard hints)
	Menu(sf::Font f, bool controller);
	//destructor
	~Menu();

	//load all text items(menu options)
	void LoadText();
	//load all sprites and textures needed for the menu
	void LoadTexturesAndSprites();

	//for moving up and down in the menu with a controller
	void MoveUp();
	void MoveDown();
	//check the mouse against the menu items
	void CheckMouse(sf::Vector2i mousePos);

	void Draw(sf::RenderWindow &window);

	//gets
	int getSelectedOption() { return selectedOption; }
	bool getCanMove() { return canMove; }
	void setCanMove(bool cm) { canMove = cm; }
	//end gets
private:
	sf::Sprite background;
	sf::Texture backgroundTexture;
	sf::Text menuItems[MAX_MAIN_MENU_ITEMS];
	sf::Font font;
	int currentSelectedOption;
	int selectedOption;

	bool canMove;

	//controller hint stuff
	sf::Sprite controllerSelectHintSprite;
	sf::Texture controllerSelectHintTexture;

	sf::Sprite controllerMoveHintSprite;
	sf::Texture controllerMoveHintTexture;

	sf::Text controllerMoveHintText;
	sf::Text controllerSelectHintText;

	//mouse hint stuff
	sf::Sprite mouseMoveHintSprite;
	sf::Texture mouseMoveHintTexture;

	sf::Sprite mouseSelectHintSprite;
	sf::Texture mouseSelectHintTexture;

	sf::Text mouseMoveHintText;
	sf::Text mouseSelectHintText;

	bool showControllerHints;

};

#endif
