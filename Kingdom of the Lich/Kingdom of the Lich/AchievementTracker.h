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
public:
	AchievementTracker(Player* p);
	~AchievementTracker();
	void Update();
};

#endif
