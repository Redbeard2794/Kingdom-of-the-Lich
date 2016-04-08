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
public:
	PauseMenu(sf::Font f, int sw, int sh);
	~PauseMenu();

	void NavUp();
	void NavDown();

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
