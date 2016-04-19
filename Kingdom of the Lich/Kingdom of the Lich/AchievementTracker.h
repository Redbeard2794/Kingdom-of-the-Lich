#ifndef ACHIEVEMENTTRACKER_H
#define ACHIEVEMENTTRACKER_H

#include "Achievement.h"
#include "Player.h"
#include "Observer.h"
#include "AudioManager.h"

class AchievementTracker : public Observer
{
private:
	std::vector<Achievement*> lockedAchievements;
	std::vector<Achievement*> unlockedAchievements;

	Player* player;

	sf::Clock displayClock;

	sf::Text unlockText;
	sf::Font font;

	int screenW;
	int screenH;

	AudioManager* audioManager;

	sf::RectangleShape messageBackground;

public:
	AchievementTracker(Player* p, sf::Font f, int sw, int sh, AudioManager* am);
	~AchievementTracker();

	void LoadAchievements();

	void Update();

	void DisplayAchievement(sf::RenderTarget& window);

	//make achievements unlocked in a saved game not pop up again when the game is loaded
	void LoadPrevUnlockedAchievements();
};

#endif
