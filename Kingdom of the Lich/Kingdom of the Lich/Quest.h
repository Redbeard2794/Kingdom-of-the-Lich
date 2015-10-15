#ifndef QUEST_H	
#define QUEST_H

class Quest
{
public:
	Quest();
	~Quest();

	//gets

	//sets

private:
	sf::Vector2f questStartingPosition;
	sf::String questGiverName;
	sf::String questObjective;
	sf::Vector2f objectiveLocation;
	bool isCombatBased;
};

#endif
