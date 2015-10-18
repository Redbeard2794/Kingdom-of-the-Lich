#ifndef CHOOSERACEANDGENDERMENU_H
#define CHOOSERACEANDGENDERMENU_H

class ChooseRaceAndGenderMenu
{
public:
	ChooseRaceAndGenderMenu(sf::Font f);
	~ChooseRaceAndGenderMenu();

	void CheckMouseAgainstRaces(sf::Vector2i mousePos);
	void CheckMouseAgainstGenders(sf::Vector2i mousePos);

	void Draw(sf::RenderWindow &window);

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

	int currentlySelectedRace;
	int currentlySelectedGender;

};

#endif