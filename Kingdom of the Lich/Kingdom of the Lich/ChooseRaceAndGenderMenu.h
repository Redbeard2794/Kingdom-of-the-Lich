#ifndef CHOOSERACEANDGENDERMENU_H
#define CHOOSERACEANDGENDERMENU_H

class ChooseRaceAndGenderMenu
{
public:
	ChooseRaceAndGenderMenu(sf::Font f, bool controller);
	~ChooseRaceAndGenderMenu();

	void Update(sf::Vector2i mousePos);
	void CheckMouseAgainstRaces(sf::Vector2i mousePos);
	void CheckMouseAgainstGenders(sf::Vector2i mousePos);
	void CheckMouseAgainstClasses(sf::Vector2i mousePos);

	void Draw(sf::RenderWindow &window);

	void setCurrentState(int s) { currentState = s; }
	int getCurrentState() { return currentState; }
	int getCurrentlySelectedRace() { return currentlySelectedRace; }
	int getCurrentlySelectedGender() { return currentlySelectedGender; }
	int getCurrentlySelectedClass() { return currentlySelectedClass; }

	//for moving through the menu with a controller
	//race
	void moveRaceSelectionRight();
	void moveRaceSelectionLeft();
	//gender
	void moveGenderSelectionRight();
	void moveGenderSelectionLeft();
	//class
	void moveClassSelectionRight();
	void moveClassSelectionLeft();

	bool getCanMoveSelection() { return canMoveSelection; }
	void setCanMoveSelection(bool cms) { canMoveSelection = cms; }

	bool getCanSelect() { return canSelect; }
	void setCanSelect(bool cs) { canSelect = cs; }

private:
	sf::Sprite table;
	sf::Texture tableTexture;
	sf::Sprite parchment;
	sf::Texture parchmentTexture;

	sf::Texture maleButtonTexture;
	sf::Texture femaleButtonTexture;

	sf::Sprite genders[2];

	sf::Text ChooseRace;
	sf::Text ChooseGender;
	sf::Text ChooseClass;

	sf::Text races[3];
	sf::Text classes[3];

	sf::Font font;
	bool mouseClicked;

	enum Race
	{
		HUMAN,
		ELF,
		BEASTMAN
	};

	enum Gender
	{
		MALE,
		FEMALE
	};

	enum Class
	{
		ARCHER,
		KNIGHT,
		SPELLBLADE
	};

	enum SelectionState
	{
		CHOOSERACE,
		CHOOSEGENDER,
		CHOOSECLASS
	};

	int currentlySelectedRace;
	int currentlySelectedGender;
	int currentlySelectedClass;
	
	int currentState;

	bool canMoveSelection;
	bool canSelect;

	//hints
	//controller
	sf::Sprite controllerMoveHint;
	sf::Texture controllerMoveHintTexture;
	sf::Text controllerMoveHintText;

	sf::Sprite controllerSelectHint;
	sf::Texture controllerSelectHintTexture;
	sf::Text controllerSelectHintText;
	//keyboard/mouse
	sf::Sprite mouseMoveHint;
	sf::Texture mouseMoveHintTexture;
	sf::Text mouseMoveHintText;

	sf::Sprite keyboardSelectHint;
	sf::Texture keyboardSelectHintTexture;
	sf::Text keyboardSelectHintText;

	bool showControllerHints;
};

#endif