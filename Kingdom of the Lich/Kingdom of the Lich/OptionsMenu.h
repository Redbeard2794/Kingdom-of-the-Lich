#ifndef OPTIONSMENU_H
#define OPTIONSMENU_H

#include "AudioManager.h"

class OptionsMenu
{
private:
	sf::Text menuItems[3];

	int musicVol;
	int sfxVol;

	sf::Font font;

	int screenW;
	int screenH;

	int currentHighlighted;
	int currentSelected;

	bool canMove;

	enum State
	{
		NAV,
		MUSIC,
		SFX,
		QUIT
	};
	int currentMenuState;

	sf::RectangleShape musicBar;
	sf::RectangleShape sfxBar;

	bool canSelect;

	sf::Texture audioWaveTexture;

public:
	OptionsMenu(sf::Font f, int sw, int sh);

	~OptionsMenu();

	void Update(AudioManager* audioManager);

	void MoveUp();

	void MoveDown();

	void IncreaseMusicVol();

	void DecreaseMusicVol();

	void IncreaseSFXVol();

	void DecreaseSFXVol();

	void Draw(sf::RenderTarget& window);

	bool GetCanMove();
	void SetCanMove(bool cm);

	int GetCurrentHighlighted();
	void SetCurrentHighlighted(int ch);

	int GetCurrentSelected();
	void SetCurrentSelected(int cs);

	int GetState();
	void SetState(int s);

	bool GetCanSelect();
	void SetCanSelect(bool cse);
};

#endif
