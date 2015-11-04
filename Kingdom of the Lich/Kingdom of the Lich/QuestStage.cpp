#include "stdafx.h"
#include "QuestStage.h"

QuestStage::QuestStage(std::string obj, int num, sf::Vector2f pos) : objective(obj), stageNumber(num), objectiveLocation(pos)
{
	completed = false;
}

QuestStage::~QuestStage()
{

}

/*Gets the objective assigned to this stage*/
std::string QuestStage::getObjective()
{
	return objective;
}

/*Get this stages identifying number*/
int QuestStage::getStageNumber()
{
	return stageNumber;
}

/*Get the objectives location*/
sf::Vector2f QuestStage::getObjectiveLocation()
{
	return objectiveLocation;
}

/*Get the completion status of this stage.
False means not completed and True means completed*/
bool QuestStage::getCompletionStatus()
{
	return completed;
}


