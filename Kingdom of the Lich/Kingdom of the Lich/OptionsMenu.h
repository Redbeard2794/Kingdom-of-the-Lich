#ifndef OPTIONSMENU_H
#define OPTIONSMENU_H

#include "AudioManager.h"

class OptionsMenu
{
private:
	sf::Text menuItems[2];

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
	bool canBackOut;

	sf::Texture audioWaveTexture;

public:
	/*constructor. params: font, screen width, screen height*/
	OptionsMenu(sf::Font f, int sw, int sh);

	/*destructor*/
	~OptionsMenu();

	/*Update volume levels and change colour of selected item. param is a pointer to an audiomanager*/
	void Update(AudioManager* audioManager);

	/*navigate up*/
	void MoveUp();

	/*navigate down*/
	void MoveDown();

	/*increase the music volume if not already maxed out*/
	void IncreaseMusicVol();

	/*decrease the music volume if not already at 0*/
	void DecreaseMusicVol();

	/*increase the sfx volume if not already maxed out*/
	void IncreaseSFXVol();

	/*decrease the sfx volume if not already at 0*/
	void DecreaseSFXVol();

	/*Draw. param is a render target*/
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

	bool GetCanBackOut();
	void SetCanBackOut(bool cbo);
};

#endif
