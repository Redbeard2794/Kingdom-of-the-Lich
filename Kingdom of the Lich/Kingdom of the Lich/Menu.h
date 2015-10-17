#ifndef MENU_H
#define MENU_H

#define MAX_MAIN_MENU_ITEMS 5

class Menu
{
public:
	Menu(sf::Font f);
	~Menu();

	void MoveUp();
	void MoveDown();
	void CheckMouse(sf::Vector2i mousePos);

	void Draw(sf::RenderWindow &window);
private:
	sf::Sprite background;
	sf::Texture backgroundTexture;
	sf::Text menuItems[MAX_MAIN_MENU_ITEMS];
	sf::Font font;
};

#endif
