#include "stdafx.h"
#include "AchievementTracker.h"

AchievementTracker::AchievementTracker(Player* p) : player(p)
{
	player->addObserver(this);
}

AchievementTracker::~AchievementTracker()
{
}

void AchievementTracker::Update()
{
	//if p->openedChests > 0 and open chest achievement is in the locked achievements vector
	//popup the achievement
	//push it to the unlocked vector
	//pop it from the locked vector
	if (player->GetOpenedChests() == 1)
	{
		std::cout << "Player unlocked 'Open the Chest!'" << std::endl;
	}
}
