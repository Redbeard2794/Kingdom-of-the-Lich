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
	int currentAction;

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
	sf::Vector2i framePosition;
	sf::Vector2i frameSize;
	sf::IntRect frame;
	int numFrames;
	float animationTime;
	sf::Clock animationClock;
	bool finishedAttackAnim;

	//player health
	sf::Text playerHealthText;

	sf::Texture enemyTexture;
	sf::Sprite enemySprite;
	sf::Vector2i enemyFramePosition;
	sf::Vector2i enemyFrameSize;
	sf::IntRect enemyFrame;
	int enemyNumFrames;
	float enemyAnimationTime;
	sf::Clock enemyAnimationClock;
	bool enemyFinishedAttackAnim;

	//enemy health
	sf::Text enemyHealthText;

	int playerCurrentHealth;
	int enemyCurrentHealth;

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

	sf::Texture combatBackgroundTexture;
	sf::Sprite combatBackgroundSprite;

	sf::Texture moveSelectionHintTexture;
	sf::Sprite moveSelectionHintSprite;

	sf::Texture selectHintTexture;
	sf::Sprite selectHintSprite;

	sf::Texture goBackHintTexture;
	sf::Sprite goBackHintSprite;

	bool canSelect;

	int screenW;
	int screenH;

	bool playersTurn;

	int turnCount;
	sf::Text turnText;

public:
	/*constructor*/
	CombatMenu(sf::Font f, std::string ePath, int sw, int sh);

	/*destructor*/
	~CombatMenu();

	void SetPlayerRepSprite(int race, int gender);

	//move right through the menu(for choosing action)
	void MoveSelectionRight();

	//move left through the menu(for choosing action)
	void MoveSelectionLeft();

	//move up through the menu(for choosing attack/item)
	void MoveSelectionUp();

	//move down through the menu(for choosing attack/item)
	void MoveSelectionDown();

	void Update(int playerHealth, int enemyHealth);

	/*Draw all elements of the menu*/
	void Draw(sf::RenderTarget& window);

	void MovePlayerToAttack();

	void SetUpAttackAnimations(bool player);

	void PlayerAttackAnimation();

	void EnemyAttackAnimation();

	/*gets & sets start*/

	int getCurrentAction();

	int getCurrentOption();

	void setCurrentOption(int o);

	bool getCanMove();

	void setCanMove(bool cm);

	int GetCurrentMenuState();

	void SetCurrentMenuState(int newState);

	void SetSelectorPosition(sf::Vector2f pos);

	sf::Vector2f GetSelectorPosition();

	bool IsCombatOver();

	void setCombatOver(bool co);

	bool getCanSelect() { return canSelect; }

	void setCanSelect(bool cas) { canSelect = cas; }

	bool IsPlayersTurn();

	void SetPlayersTurn(bool t);

	int GetTurnCount();

	void IncrementTurnCount();

	/*gets & sets end*/
};

#endif
