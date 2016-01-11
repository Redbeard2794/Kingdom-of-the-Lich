#ifndef CHOOSERACEANDGENDERMENU_H
#define CHOOSERACEANDGENDERMENU_H

class ChooseRaceAndGenderMenu
{
public:
	//Constructor(params are font and whether to show controller hints or keyboard hints)
	ChooseRaceAndGenderMenu(sf::Font f, bool controller, int screenW, int screenH);

	//destructor
	~ChooseRaceAndGenderMenu();

	//update the state of the menu(choosing race, gender and class)
	void Update(sf::Vector2i mousePos);

	//check the mouse against the different options for choosing the race of the character
	void CheckMouseAgainstRaces(sf::Vector2i mousePos);

	//check the mouse against the different options for choosing the gender of the character
	void CheckMouseAgainstGenders(sf::Vector2i mousePos);

	//check the mouse against the different options for choosing the class of the character
	void CheckMouseAgainstClasses(sf::Vector2i mousePos);

	//draw the menu
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
	//background textures and sprites
	sf::Sprite table;
	sf::Texture tableTexture;
	sf::Sprite parchment;
	sf::Texture parchmentTexture;

	//menu textures,sprites and text
	sf::Texture maleButtonTexture;
	sf::Texture femaleButtonTexture;

	sf::Texture maleButtonSelectedTexture;
	sf::Texture femaleButtonSelectedTexture;

	sf::Sprite genders[2];

	sf::Text ChooseRace;
	sf::Text ChooseGender;
	sf::Text ChooseClass;

	sf::Text races[3];
	sf::Text classes[3];

	sf::Sprite raceIcons[3];
	sf::Texture raceIconTextures[3];
	sf::Texture raceIconSelectedTexture[3];

	//descriptions
	sf::Texture humanDescriptionTexture;
	sf::Sprite humanDescription;

	sf::Texture elfDescriptionTexture;
	sf::Sprite elfDescription;

	sf::Texture dwarfDescriptionTexture;
	sf::Sprite dwarfDescription;

	sf::Font font;
	bool mouseClicked;

	//possible races
	enum Race
	{
		HUMAN,
		ELF,
		DWARF
	};

	//possible genders
	enum Gender
	{
		MALE,
		FEMALE
	};

	//possible classes
	enum Class
	{
		ARCHER,
		KNIGHT,
		SPELLBLADE
	};

	//current thing that we are choosing
	enum SelectionState
	{
		CHOOSERACE,
		CHOOSEGENDER,
		CHOOSECLASS
	};

	//current selections
	int currentlySelectedRace;
	int currentlySelectedGender;
	int currentlySelectedClass;
	//current state
	int currentState;

	//can we move 
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

	//which set of hints should be shown
	bool showControllerHints;
};

#endif