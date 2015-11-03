#include "stdafx.h"
#include "Quest.h"

Quest::Quest(int id, std::string qName, sf::Vector2f startPos, std::string giverName, std::string objective, sf::Vector2f objectivePos, bool combat, int gems, int xp)
	: questId(id), questName(qName), questStartingPosition(startPos), questGiverName(giverName), questObjective(objective),
	objectiveLocation(objectivePos), isCombatBased(combat),questGemReward(gems), xpReward(xp)
{

}

Quest::~Quest()
{

}