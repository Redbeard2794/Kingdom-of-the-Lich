#ifndef COMBATMENU_H
#define COMBATMENU_H

class CombatMenu
{
private:
	//background/hud like thing
	sf::Texture backgroundTexture;
	sf::Sprite backgroundSprite;

	sf::Text menuItems[3];//attack, items, flee
	sf::Font font;

	int currentOption;

	bool canMove;

	//arrow for showing current selection
	sf::Texture selectorTexture;
	sf::Sprite selectorSprite;

	//attack panel
	sf::Texture attackPanelTexture;
	sf::Sprite attackPanelSprite;

	//items panel
	sf::Texture itemPanelTexture;
	sf::Sprite itemPanelSprite;

	//possible menu states
	enum MenuStates
	{
		SelectAction,
		SelectAttack,
		SelectItem,
		FleeAttempt
	};

	int currentState = SelectAction;

public:
	/*constructor*/
	CombatMenu(sf::Font f);

	/*destructor*/
	~CombatMenu();

	void MoveSelectionRight();

	void MoveSelectionLeft();

	/*Draw all elements of the menu*/
	void Draw(sf::RenderTarget& window);

	int getCurrentOption();

	bool getCanMove();

	void setCanMove(bool cm);

	int GetCurrentMenuState();

	void SetCurrentMenuState(int newState);
};

#endif
