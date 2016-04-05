#ifndef SAVEMANAGER_H
#define SAVEMANAGER_H

//rapidxml stuff
#include "rapidxml.hpp"
#include "rapidxml_print.hpp"
#include "rapidxml_utils.hpp"
using namespace rapidxml;
#include <sstream> // std::stringstream
#include <fstream>

//for setting the values after loading a save
#include "Player.h"
#include "AchievementTracker.h"
#include "AreaManager.h"
#include "Inventory.h"

class SaveManager
{
private:
	std::string savePath;

	enum States
	{
		NONE,
		SAVE,
		ChooseSaveSlot,
		LOAD,
		ChooseLoadSlot,
		EXIT
	};
	int currentState;

	sf::Font font;
	sf::Text saveHeading;
	int screenW;
	int screenH;

	sf::Text menuItems[2];
	int currentSelected;
	sf::Text saveSlots[3];

	sf::Texture emptySlotTexture;
	sf::RectangleShape slotImages[3];

	sf::Texture slotOneTexture;
	sf::Texture slotTwoTexture;
	sf::Texture slotThreeTexture;

	bool canMove;
	bool canSelect;
	bool saving;

public:
	//constructor. params: save file path, font
	SaveManager(sf::Font f, int sw, int sh);

	//destructor
	~SaveManager();

	//save game
	void SaveGame(int raceVal, int genderVal, int healthVal, int numChestsVal, int numPotionsVal, bool pubFirstVal, bool sewerFirstVal,
		int combatsCompleteVal, sf::Vector2f pos, int areaVal, Inventory* playerInv);

	//load a game. return true if the save is not empty. if it is then load a new game
	bool LoadGame(Player* player, AchievementTracker* achievementTracker, AreaManager* areaManager, Inventory* playerInv);

	//update
	void UpdateState();

	void NavUp();

	void NavDown();

	//draw. param: render target
	void Draw(sf::RenderTarget& window);

	int GetCurrentState();
	void SetCurrentState(int s);
	bool GetCanMove();
	void SetCanMove(bool cm);
	bool GetCanSelect();
	void SetCanSelect(bool cs);
	bool IsSaving();
	int GetCurrentSelected();
	void SetCurrentSelected(int sel);
};

#endif
