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

/*Set the objective for this stage*/
void QuestStage::setObjective(std::string obj)
{
	objective = obj;
}

/*Set this stage's identifying number*/
void QuestStage::setStageNumber(int n)
{
	stageNumber = n;
}

/*Set the location of the objective*/
void QuestStage::setObjectiveLocation(sf::Vector2f pos)
{
	objectiveLocation = pos;
}

/*Set this stages completion status*/
void QuestStage::setCompletionStatus(bool c)
{
	completed = c;
}


