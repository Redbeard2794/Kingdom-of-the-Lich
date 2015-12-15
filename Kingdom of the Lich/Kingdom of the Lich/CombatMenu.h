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

	//possible attacks
	std::vector<sf::Text*> attackOptions;//going with a vector here as more attacks will be added when the player learns them(in future of course!)

	//items panel
	sf::Texture itemPanelTexture;
	sf::Sprite itemPanelSprite;

	//possible items
	std::vector<sf::Text*> itemOptions;//These are only items that are useful in combat. using a vector as I want to pull items in from the player's inventory in the future.

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

	void MoveSelectionUp();

	void MoveSelectionDown();

	/*Draw all elements of the menu*/
	void Draw(sf::RenderTarget& window);

	int getCurrentOption();

	bool getCanMove();

	void setCanMove(bool cm);

	int GetCurrentMenuState();

	void SetCurrentMenuState(int newState);

	void SetSelectorPosition(sf::Vector2f pos);

	sf::Vector2f GetSelectorPosition();
};

#endif
