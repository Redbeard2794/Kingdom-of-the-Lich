#ifndef ACHIEVEMENTTRACKER_H
#define ACHIEVEMENTTRACKER_H

#include "Achievement.h"
#include "Player.h"
#include "Observer.h"

class AchievementTracker : public Observer
{
private:
	std::vector<Achievement*> lockedAchievements;
	std::vector<Achievement*> unlockedAchievements;

	Player* player;

	sf::Clock displayClock;

	sf::Text unlockText;
	sf::Font font;

public:
	AchievementTracker(Player* p, sf::Font f);
	~AchievementTracker();

	void LoadAchievements();

	void Update();

	void DisplayAchievement(sf::RenderTarget& window);
};

#endif
