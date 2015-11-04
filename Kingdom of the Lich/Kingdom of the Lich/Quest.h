#ifndef QUEST_H	
#define QUEST_H
#include "QuestStage.h"
class Quest
{
public:
	//Quest(int id, std::string qName, sf::Vector2f startPos, std::string giverName, std::string objective, sf::Vector2f objectivePos, bool combat, int gems, int xp);
	//~Quest();

	////start gets
	//int getQuestId() { return questId; }
	//std::string getQuestName(){return questName;}
	//sf::Vector2f getQuestStartingPosition(){ return questStartingPosition; }
	//std::string getQuestGiverName() { return questGiverName; }
	//std::string getQuestObjective() { return questObjective; }
	//sf::Vector2f getObjectiveLocation() { return objectiveLocation; }
	//bool getIsCombatBased() { return isCombatBased; }
	//int getQuestGemReward() { return questGemReward; }
	////Item getRewardItem(){return rewardItem;}
	//int getXpReward() { return xpReward; }
	//bool getIsCompleted() { return completed; }
	////end gets

	////start sets
	//void setQuestId(int id) { questId = id; }
	//void setQuestName(std::string qName) { questName = qName; }
	//void setQuestStartingPosition(sf::Vector2f qsp) { questStartingPosition = qsp; }
	//void setQuestGiverName(std::string qgn) { questGiverName = qgn; }
	//void setQuestObjective(std::string qo) { questObjective = qo; }
	//void setObjectiveLocation(sf::Vector2f ol) { objectiveLocation = ol; }
	//void setIsCombatBased(bool cb) { isCombatBased = cb; }
	//void setQuestGemReward(int qgr) { questGemReward = qgr; }
	////void setRewardItem(Item i){rewardItem = i;}
	//void setXpReward(int xpr) { xpReward = xpr; }
	//void setIsCompleted(bool c) { completed = c; }
	////end sets

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

	//int questId;//id for the quest

	//std::string questName;

	//sf::Vector2f questStartingPosition;//where does the quest start(the quest givers position)

	//std::string questGiverName;//who gives the quest

	//struct Objective
	//{
	//	std::string objectiveDescription;
	//	sf::Vector2f objectiveLocation;
	//	bool completed;
	//};
	//std::vector<Objective> objectives;

	//std::string questObjective;//what the player needs to do

	//sf::Vector2f objectiveLocation;//the location where the objective will be carried out

	//bool isCombatBased;//is there combat involved?

	//int questGemReward;//number of gems to be awarded for completing the quest(if no gems are to be awarded then pass 0)

	////Item rewardItem;//the item to be awarded

	//int xpReward;//amount of xp to be awarded.(if no xp is to be awarded then pass 0)

	//bool completed;//is the quest completed?

};

#endif
