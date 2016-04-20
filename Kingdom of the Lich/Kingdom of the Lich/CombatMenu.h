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

	//enemies representation
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

	bool playersTurn;//is it the players turn

	int turnCount;
	sf::Text turnText;

	std::string enemyName;

public:
	/*constructor. params: font, path for enemy texture, screen width, screen height*/
	CombatMenu(sf::Font f, std::string ePath, int sw, int sh);

	/*destructor*/
	~CombatMenu();

	//set the correct texture for the player based on race and gender. params: player race, player gender
	void SetPlayerRepSprite(int race, int gender);

	//move right through the menu(for choosing action)
	void MoveSelectionRight();

	//move left through the menu(for choosing action)
	void MoveSelectionLeft();

	//move up through the menu(for choosing attack/item)
	void MoveSelectionUp();

	//move down through the menu(for choosing attack/item)
	void MoveSelectionDown();

	//set the player and enemy health. params: player health, enemy health
	void Update(int playerHealth, int enemyHealth);

	/*Draw all elements of the menu*/
	void Draw(sf::RenderTarget& window);

	//move th eplayer sprite in front of the enemy so it can attack
	void MovePlayerToAttack();

	//set up attack animation for player or enemy based on parameter passed in. true = player, false = enemy
	void SetUpAttackAnimations(bool player);

	//animate the players attack
	void PlayerAttackAnimation();

	//animate the enemies attack
	void EnemyAttackAnimation();

	//reset textures and turn values etc to be ready for the next combat. params: path to enemy texture, enemy name
	void ResetForNextCombat(std::string ePath, std::string eName);

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

	std::string GetEnemyName();

	/*gets & sets end*/
};

#endif
