#ifndef MENU_H
#define MENU_H

#define MAX_MAIN_MENU_ITEMS 5

class Menu
{
public:
	Menu(sf::Font f, bool controller);
	~Menu();

	void LoadText();
	void LoadTexturesAndSprites();

	void MoveUp();
	void MoveDown();
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
