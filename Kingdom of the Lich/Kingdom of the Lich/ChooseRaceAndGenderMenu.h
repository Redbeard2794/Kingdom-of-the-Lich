#ifndef CHOOSERACEANDGENDERMENU_H
#define CHOOSERACEANDGENDERMENU_H

class ChooseRaceAndGenderMenu
{
public:
	ChooseRaceAndGenderMenu(sf::Font f);
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

private:
	sf::Sprite table;
	sf::Texture tableTexture;
	sf::Sprite parchment;
	sf::Texture parchmentTexture;

	sf::Sprite maleButton;
	sf::Texture maleButtonTexture;
	sf::Sprite femaleButton;
	sf::Texture femaleButtonTexture;

	sf::Text ChooseRace;
	sf::Text ChooseGender;

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
		CHOOSERACEGENDER,
		CHOOSECLASS
	};

	int currentlySelectedRace;
	int currentlySelectedGender;
	int currentlySelectedClass;
	
	int currentState;

};

#endif