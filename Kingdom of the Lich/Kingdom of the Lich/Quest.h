#ifndef QUEST_H	
#define QUEST_H
#include "QuestStage.h"
class Quest
{
public:
	Quest(int numStages, std::string qName, std::string qGiverName, sf::Vector2f startPos, int id, int gReward, int xReward);

	~Quest();

	/*Get a pointer to the current stage*/
	QuestStage* getCurrentStage();

	/*Get the total number of stages*/
	int getNumberOfStages();
	/*Set the total number of stages*/
	void setNumberOfStages(int numStages);

	/*Get the index of the current stage*/
	int getCurrentStageIndex();
	/*Set the index of the current stage*/
	void setCurrentStageIndex(int cs);

	/*Get the name of the quest*/
	std::string getQuestName();

	/*Get the name of the npc that gives the player this quest*/
	std::string getQuestGiverName();

	/*Get the position of where the quest begins*/
	sf::Vector2f getStartingPosition();

	/*Get the identifying number for this quest*/
	int getQuestId();

	/*Get the number of gems to reward the player with when they complete the quest.*/
	int getGemReward();

	/*Get the number of xp to reward the player with when they complete the quest.*/
	int getXpReward();

	/*Get the completion status of this quest*/
	bool getCompletionStatus();

	/*Set the completion status of this quest*/
	void setCompletionStatus(bool com);

private:
	std::vector<QuestStage*> stages;//stages involved in the quest

	int numberOfStages;//the amount of stages in this quest

	int currentStage;//stage of quest that player is currently doing

	std::string questName;//name of quest

	std::string questGiverName;//name of npc that gives the quest

	int questId;//identifying number for the quest

	sf::Vector2f questStartingPosition;//starting point for the quest

	int gemReward;//amount of gems to give to the player when completed. If you do not want to reward the player with gems set it to 0

	int xpReward;//amount of xp to give to the player when completed. If you do not want to reward the player with xp set it to 0

	bool completed;//is the question completed?

};

#endif
