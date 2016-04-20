#ifndef ACHIEVEMENTTRACKER_H
#define ACHIEVEMENTTRACKER_H

#include "Achievement.h"
#include "Player.h"
#include "Observer.h"
#include "AudioManager.h"

class AchievementTracker : public Observer
{
private:
	std::vector<Achievement*> lockedAchievements;//all locked achievements
	std::vector<Achievement*> unlockedAchievements;//achievements unlocked by the player

	Player* player;

	sf::Clock displayClock;//clock for timing how long to display newly unlocked achievement

	sf::Text unlockText;//text for unlocking achievement
	sf::Font font;

	int screenW;
	int screenH;

	AudioManager* audioManager;

	sf::RectangleShape messageBackground;

public:
	/*Constructor. params: player pointer, font, scren width, screen height, audiomanager pointer*/
	AchievementTracker(Player* p, sf::Font f, int sw, int sh, AudioManager* am);

	/*destructor*/
	~AchievementTracker();

	/*Load achievements from xml*/
	void LoadAchievements();

	/*update the unlocked achievements list by checking if the player has the pre requisites to unlock them*/
	void Update();

	/*display a newly unlocked achievement*/
	void DisplayAchievement(sf::RenderTarget& window);

	//make achievements unlocked in a saved game not pop up again when the game is loaded
	void LoadPrevUnlockedAchievements();
};

#endif
