#ifndef CONFIRMATIONDIALOGBOX
#define CONFIRMATIONDIALOGBOX

class ConfirmationDialogBox
{
private:
	static bool instanceFlag;
	static ConfirmationDialogBox* instance;

	sf::Sprite backgroundSprite;
	sf::Texture backgroundTexture;
	sf::Text dialogText;
	sf::Font font;

	sf::Text* confirmationOptions[2];

	bool visible;
	bool optionConfirmed;
	bool canMoveSelection;

	int currentOption;
	int prevOption;

	bool mouseClicked;

	enum Options
	{
		YES,
		NO
	};

	//constructor is private as it is a singleton
	ConfirmationDialogBox()
	{
		if (backgroundTexture.loadFromFile("Assets/dialogBoxBackground.png")) {}
		else backgroundTexture.loadFromFile("Assets/Debug.png");	//if it fails load placeholder
		backgroundSprite.setOrigin(sf::Vector2f(backgroundTexture.getSize().x / 2, backgroundTexture.getSize().y / 2));
		backgroundSprite.setTexture(backgroundTexture);
		backgroundSprite.setPosition(SCREENWIDTH/2, SCREENHEIGHT/2);

		visible = false;

		font.loadFromFile("Assets/Kelt Caps Freehand.TTF");

		dialogText.setFont(font);
		dialogText.setPosition((SCREENWIDTH / 3)-40, SCREENHEIGHT / 3);
		dialogText.setColor(sf::Color(127, 0, 0, 255));

		confirmationOptions[0] = new sf::Text();
		confirmationOptions[0]->setFont(font);
		confirmationOptions[0]->setString("YES");
		confirmationOptions[0]->setColor(sf::Color::Red);
		confirmationOptions[0]->setPosition(sf::Vector2f(backgroundSprite.getPosition().x - 30, backgroundSprite.getPosition().y - 40));

		confirmationOptions[1] = new sf::Text();
		confirmationOptions[1]->setFont(font);
		confirmationOptions[1]->setString("NO");
		confirmationOptions[1]->setColor(sf::Color(80, 0, 0, 255));
		confirmationOptions[1]->setPosition(sf::Vector2f(backgroundSprite.getPosition().x - 25, backgroundSprite.getPosition().y + 20));

		canMoveSelection = true;
		currentOption = YES;
		prevOption = currentOption;

		mouseClicked = false;
	}

public:
	static ConfirmationDialogBox* GetInstance();
	~ConfirmationDialogBox();

	void Update();

	//for moving through options with a controller
	void MoveUp();
	void MoveDown();
	//for selecting different options with the mouse
	void CheckMouseToOptions(sf::Vector2i mousePos);

	void setDialogText(sf::String dialog, int textSize);

	void setVisible(bool v) { visible = v; }
	bool getVisible() { return visible; }

	void setOptionConfirmed(bool oc) { optionConfirmed = oc; }
	bool getOptionConfirmed() { return optionConfirmed; }

	void setConfirmPosition(sf::Vector2f conPos);
	void setNegativePosition(sf::Vector2f negPos);

	void setCanMoveSelection(bool cms) { canMoveSelection = cms; }
	bool getCanMoveSelection() { return canMoveSelection; }

	int getCurrentOption() { return currentOption; }

	void Draw(sf::RenderTarget& window);
};

#endif
