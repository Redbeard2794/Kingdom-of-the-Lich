#include "stdafx.h"
#include "Quest.h"
//
//Quest::Quest(int id, std::string qName, sf::Vector2f startPos, std::string giverName, std::string objective, sf::Vector2f objectivePos, bool combat, int gems, int xp)
//	: questId(id), questName(qName), questStartingPosition(startPos), questGiverName(giverName), questObjective(objective),
//	objectiveLocation(objectivePos), isCombatBased(combat),questGemReward(gems), xpReward(xp)
//{
//	completed = false;
//}
//
//Quest::~Quest()
//{
//
//}

Quest::Quest(int numStages, std::string qName, std::string qGiverName, sf::Vector2f startPos, int id, int gReward, int xReward)
	: numberOfStages(numStages), questName(qName), questGiverName(qGiverName),
	questStartingPosition(startPos), questId(id), gemReward(gReward),
	xpReward(xReward)
{
	currentStage = 0;
	completed = false;

	//set up the stages vector
	stages.reserve(numberOfStages);
	/*In future the quest and quest stages info will be loaded from some sort of file(eg: xml).
	For now we are going to deal with just one quest
	*/
	QuestStage* stageZero = new QuestStage("Talk to Commander Iron-Arm", 0, sf::Vector2f(1000, 1000));
	stages.push_back(stageZero);
	QuestStage* stageOne = new QuestStage("Retreive items from chest", 1, sf::Vector2f(SCREENWIDTH/2, SCREENHEIGHT/2));
	stages.push_back(stageOne);
}

Quest::~Quest()
{

}

/*Get a pointer to the current stage*/
QuestStage * Quest::getCurrentStage()
{
	return stages.at(currentStage);
}

/*Get the total number of stages*/
int Quest::getNumberOfStages()
{
	return numberOfStages;
}

/*Set the total number of stages*/
void Quest::setNumberOfStages(int numStages)
{
	numberOfStages = numStages;
}

/*Get the index of the current stage*/
int Quest::getCurrentStageIndex()
{
	return currentStage;
}

/*Set the index of the current stage*/
void Quest::setCurrentStageIndex(int cs)
{
	currentStage = cs;
}

/*Get the name of the quest*/
std::string Quest::getQuestName()
{
	return questName;
}

/*Get the name of the npc that gives the player this quest*/
std::string Quest::getQuestGiverName()
{
	return questGiverName;
}

/*Get the position of where the quest begins*/
sf::Vector2f Quest::getStartingPosition()
{
	return questStartingPosition;
}

/*Get the identifying number for this quest*/
int Quest::getQuestId()
{
	return questId;
}

/*Get the number of gems to reward the player with when they complete the quest*/
int Quest::getGemReward()
{
	return gemReward;
}

/*Get the number of xp to reward the player with when they complete the quest.*/
int Quest::getXpReward()
{
	return xpReward;
}

/*Get the completion status of this quest*/
bool Quest::getCompletionStatus()
{
	return completed;
}

/*Set the completion status of this quest*/
void Quest::setCompletionStatus(bool com)
{
	completed = com;
}
