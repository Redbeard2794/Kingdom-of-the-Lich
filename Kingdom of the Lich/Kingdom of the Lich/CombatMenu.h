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

	//player representation
	sf::Texture playerRepTexture;
	sf::Sprite playerRepSprite;

	//player health
	sf::Text playerHealthText;

	sf::Texture enemyTexture;
	sf::Sprite enemySprite;

	//possible menu states
	enum MenuStates
	{
		SelectAction,
		SelectAttack,
		SelectItem,
		FleeAttempt
	};

	int currentState = SelectAction;

	bool combatOver;//is combat finished as a result of winning/losing or fleeing

public:
	/*constructor*/
	CombatMenu(sf::Font f, std::string ePath);

	/*destructor*/
	~CombatMenu();

	//move right through the menu(for choosing action)
	void MoveSelectionRight();

	//move left through the menu(for choosing action)
	void MoveSelectionLeft();

	//move up through the menu(for choosing attack/item)
	void MoveSelectionUp();

	//move down through the menu(for choosing attack/item)
	void MoveSelectionDown();

	/*Draw all elements of the menu*/
	void Draw(sf::RenderTarget& window, int playerHealth);

	/*gets & sets start*/

	int getCurrentOption();

	bool getCanMove();

	void setCanMove(bool cm);

	int GetCurrentMenuState();

	void SetCurrentMenuState(int newState);

	void SetSelectorPosition(sf::Vector2f pos);

	sf::Vector2f GetSelectorPosition();

	bool IsCombatOver();

	void setCombatOver(bool co);

	/*gets & sets end*/
};

#endif
